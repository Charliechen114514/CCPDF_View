#include <QPdfDocument>
#include "pdf_exportpdfex.h"
#include <QMutexLocker>
#include <QPdfWriter>
#include <QPainter>
#define TRANS_PASS_SIGNAL(thread, threadClass, NAME) \
    connect(thread, &threadClass::NAME, this, &PDF_ExportPDFEx::NAME)
QMutex check_render;
QMutex check_export;
QMutex lock_images;
QMutex release_threads;
PDF_RenderThread::PDF_RenderThread(QPdfDocument* ex, PDF_ExportThread* who,
                                   QMap<int, QImage*>* editedOne):
    handle_doc(ex), editedOne(editedOne), exportWorker(who)
{
    this->exportWorker->setTolPage(ex->pageCount());
}

bool PDF_RenderThread::required_sleep(int pg)
{
    return pg - exportWorker->curHandlePage >= acceptable_pic;
}

void PDF_RenderThread::renderPic(int pg)
{
    QImage* image = nullptr;
    if(editedOne && editedOne->contains(pg))
        image = new QImage(*editedOne->value(pg));
    else
        image = new QImage(handle_doc->render(pg, QSize(640, 960)));
    *image = conf.getA4PrintableImage(*image);
    lock_images.lock();
    exportWorker->required_export.push_back(image);
    lock_images.unlock();
}

void PDF_RenderThread::run()
{
    if(!handle_doc)
        return;
    int docPgCnt = handle_doc->pageCount();
    for(int curPage = 0; curPage < docPgCnt; curPage++)
    {
        // check shell goes on
        check_render.lock();
        if(shellStop)
        {
            check_render.unlock();
            return;
        }
        check_render.unlock();
        while(required_sleep(curPage))
        {
            this->sleep(waiting_sec);
            check_render.lock();
            if(shellStop)
            {
                check_render.unlock();
                return;
            }
            check_render.unlock();
        }
        emit startRenderIndex(curPage);
        renderPic(curPage);
    }
    emit finishRender();
}

PDF_ExportThread::PDF_ExportThread(QString exportPath):exportPath(exportPath)
{}

PDF_ExportThread::~PDF_ExportThread()
{
    this->quit();
    this->wait();
    handleQuit();
}

void PDF_ExportThread::handleQuit()
{
    for(auto unHandle_image : required_export)
    {
        delete unHandle_image;
    }
    required_export.clear();
}

void PDF_ExportThread::exportRequired(QImage* image, bool required_newpage, QPainter& p, QPdfWriter* w)
{
    if(!image)
        return;
    p.drawImage(100, 0, *image);
    if(required_newpage)
        w->newPage();
}


void PDF_ExportThread::run()
{
    QPdfWriter pdfWriter(this->exportPath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    for(int pgHandle = 0; pgHandle < totalPage; pgHandle++)
    {
        check_export.lock();
        if(shellStop)
        {
            check_export.unlock();
            return;
        }
        check_export.unlock();
        while(required_export.empty()){
            qDebug() << "Required_sleep for export!";
            sleep(waiting_second);
            check_export.lock();
            if(shellStop)
            {
                check_export.unlock();
                return;
            }
            check_export.unlock();
        }
        emit startExportIndex(pgHandle);
        QImage* waitingExport = required_export.first();
        exportRequired(waitingExport,
                       pgHandle != totalPage - 1,
                       painter,
                       &pdfWriter);

        curHandlePage = pgHandle;
        lock_images.lock();
        required_export.pop_front();
        delete waitingExport;
        lock_images.unlock();
    }
    emit finishExport();
}



PDF_ExportPDFEx::PDF_ExportPDFEx(QPdfDocument* doc,QString path,
                                 QMap<int, QImage*>* editedOne, QObject *parent)
    : QObject{parent}
{
    configExportThread(path);
    configRenderThread(doc, editedOne);
    initConnections();
}

PDF_ExportPDFEx::~PDF_ExportPDFEx()
{
    release_threads.lock();
    if(this->renderThread)
    {
        this->renderThread->setStopImm();
        delete this->renderThread;
        this->renderThread = nullptr;
    }
    if(this->exportThread)
    {
        this->exportThread->setStopImm();
        delete this->exportThread;
        this->exportThread = nullptr;
    }
    release_threads.unlock();
}

void PDF_ExportPDFEx::initConnections()
{
    TRANS_PASS_SIGNAL(renderThread, PDF_RenderThread, startRender);
    TRANS_PASS_SIGNAL(renderThread, PDF_RenderThread, startRenderIndex);
    TRANS_PASS_SIGNAL(renderThread, PDF_RenderThread, finishRender);
    TRANS_PASS_SIGNAL(exportThread, PDF_ExportThread, startExport);
    TRANS_PASS_SIGNAL(exportThread, PDF_ExportThread, startExportIndex);
    TRANS_PASS_SIGNAL(exportThread, PDF_ExportThread, finishExport);
    connect(this->renderThread, &PDF_RenderThread::finishRender,
            this, &PDF_ExportPDFEx::cleanRenderThread);
}

void PDF_ExportPDFEx::cleanRenderThread()
{
    release_threads.lock();
    delete renderThread;
    renderThread = nullptr;
    release_threads.unlock();
    qDebug() << "render thread cleaned";
}

void PDF_ExportPDFEx::configRenderThread(QPdfDocument* doc,QMap<int, QImage*>* editedOne)
{
    if(!this->renderThread)
        delete renderThread;
    this->renderThread = new PDF_RenderThread(doc, exportThread, editedOne);
}

void PDF_ExportPDFEx::configExportThread(QString path)
{
    if(!this->exportThread)
        delete exportThread;
    this->exportThread = new PDF_ExportThread(path);
}

bool PDF_ExportPDFEx::isWorkingCurrent()
{
    return  (renderThread && renderThread->isRunning()) ||
            (exportThread && exportThread->isRunning());
}

void PDF_ExportPDFEx::startWork()
{
    this->renderThread->start();
    emit startRender();
    this->exportThread->start();
    emit startExport();
}

void PDF_ExportPDFEx::cancelAll()
{
    QString path = this->exportThread->exportPath;
    release_threads.lock();
    if(this->renderThread)
    {
        this->renderThread->setStopImm();
        delete this->renderThread;
        this->renderThread = nullptr;
    }
    if(this->exportThread)
    {
        this->exportThread->setStopImm();
        delete this->exportThread;
        this->exportThread = nullptr;
    }
    release_threads.unlock();
    if(!isCancelExportLeaveTheRest)
        PDF_RemoveFile::removeFile(path);
    emit cancelFinish();
}













