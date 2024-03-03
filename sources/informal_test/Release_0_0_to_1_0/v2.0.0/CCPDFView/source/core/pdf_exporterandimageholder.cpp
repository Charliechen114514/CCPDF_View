#include <QPdfDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QMutexLocker>
#include "pdf_exporterandimageholder.h"
#include "PDF_Utils.h"
QMutex m;


RenderWorker::RenderWorker(QPdfDocument* doc, PDF_ExporterAndImageHolder *manager, QObject *parent):QThread(parent)
{
    this->doc = doc;
    this->manager = manager;
    connect(this, &RenderWorker::finished, manager, &PDF_ExporterAndImageHolder::releaseRenderThread);
}

void RenderWorker::renderTaskCore()
{
    if(!this->manager || !this->doc)
    {
        emit errorOccur();
        return;
    }
    int docPgCnt = doc->pageCount();
    PDF_ExportWriterConfig conf;
    emit startRender();
    for(int curPage = 0; curPage < docPgCnt; curPage++)
    {
        m.lock();
        if(shellStop)
        {
            m.unlock();
            return;
        }
        m.unlock();
        if(manager->editedOne->contains(curPage))
        {
            QImage* editedOne = manager->editedOne->value(curPage);
            *editedOne = conf.getA4PrintableImage(*editedOne);
            manager->renderResults.push_back(editedOne);
        }
        else
        {
            QImage* curImage = new QImage(doc->render(curPage, QSize(640, 960)));
            // have to seperate work as it will failed if diirectly point the size
            *curImage = conf.getA4PrintableImage(*curImage);
            manager->renderResults.push_back(curImage);
        }
        emit finishRenderIndex(curPage);
    }
    emit finishRenderAll();
}

void RenderWorker::run()
{
    renderTaskCore();
}

RenderWorker::~RenderWorker()
{
    qDebug() << "handleing the released render thread";
}


ExportWorker::ExportWorker(const QString path,
                           PDF_ExporterAndImageHolder *manager, QObject* parent):QThread(parent)
{
    this->exportPath = path;
    this->manager = manager;
    connect(this, &ExportWorker::finished, manager, &PDF_ExporterAndImageHolder::releaseExporterThread);
}

void ExportWorker::exportTaskCore()
{
    if(this->exportPath.isEmpty())
    {
        emit errorOccur();
        return;
    }
    QPdfWriter pdfWriter(this->exportPath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    emit startExport();
    int pgHandle = 0;
    for(auto eachImage : manager->renderResults)
    {
        m.lock();
        if(shellStop)
        {
            m.unlock();
            return;
        }
        m.unlock();
        painter.drawImage(100, 0, *eachImage);
        if(eachImage != manager->renderResults.last())
        {
            pdfWriter.newPage();
        }
        emit finishExportPg(pgHandle);
        pgHandle++;
    }
    emit finishExport();
}

void ExportWorker::run()
{
    exportTaskCore();
}

ExportWorker::~ExportWorker()
{
    qDebug() << "handling the exporter thread";
}


void PDF_ExporterAndImageHolder::createRenderThread()
{
    qDebug() << "Create render thread";
    this->renderWorker = new RenderWorker(currentHandleDoc, this, this);
}



void PDF_ExporterAndImageHolder::createExporterThread()
{
    this->exportWorker = new ExportWorker(exportPath, this, this);
}


PDF_ExporterAndImageHolder::PDF_ExporterAndImageHolder(QPdfDocument *doc, QObject *parent)
    : QObject{parent}
{
    this->currentHandleDoc = doc;
    createRenderThread();
    initConnectionRender();
}

bool PDF_ExporterAndImageHolder::isExportingCurrent()
{
    return this->exportWorker && this->exportWorker->isRunning();
}


bool PDF_ExporterAndImageHolder::isAcssessbleForRenderWork()
{
    return this->renderWorker && this->currentHandleDoc;
}

bool PDF_ExporterAndImageHolder::isAcssessbleForExportWork()
{
    return this->isExportable && !this->exportPath.isEmpty();
}

void PDF_ExporterAndImageHolder::initConnectionRender()
{
    connect(this->renderWorker, &RenderWorker::finishRenderIndex,
            this, &PDF_ExporterAndImageHolder::handleTheRenderPartialFinish);

    connect(this->renderWorker, &RenderWorker::finishRenderAll,
            this, &PDF_ExporterAndImageHolder::handleTheRenderFinish);
}

void PDF_ExporterAndImageHolder::registerTheEdited(QMap<int, QImage*>* s)
{
    editedOne = s;
}


void PDF_ExporterAndImageHolder::setExportPath(QString path)
{
    this->exportPath = path;
    createExporterThread();
    clearError();
    initConnectionExport();
}

void PDF_ExporterAndImageHolder::initConnectionExport()
{
    connect(this->exportWorker, &ExportWorker::finishExportPg,
            this, &PDF_ExporterAndImageHolder::handleTheExportPartialFinish);

    connect(this->exportWorker, &ExportWorker::finishExport,
            this, &PDF_ExporterAndImageHolder::handleTheExportFinish);
}

void PDF_ExporterAndImageHolder::handleTheRenderPartialFinish(int page)
{
    // qDebug() << "finish render the page" << page;
    emit this->finishRenderIndex(page);
}

void PDF_ExporterAndImageHolder::handleTheRenderFinish()
{
    // qDebug() << "finish render all";
    emit this->finishRenderAll();
    setExportableAfterRender();
    if(shallExportImm)
    {
        this->startExportWork();
    }
}


void PDF_ExporterAndImageHolder::handleTheExportPartialFinish(int page)
{
    // qDebug() << "finish export the page" << page;
    emit this->finishExportPg(page);
}

void PDF_ExporterAndImageHolder::handleTheExportFinish()
{
    // qDebug() << "finish export all";
    emit this->finishExport();
    this->shallExportImm = false;
    releaseRenderSources();
    this->isExportable = false;
}


void PDF_ExporterAndImageHolder::startRenderWork()
{
    if(!isAcssessbleForRenderWork())
    {
        setError(Error::RENDER_UNSET);
        return;
    }

    this->renderWorker->start();
    emit startRender();
}

void PDF_ExporterAndImageHolder::startExportWork()
{
    if(!isAcssessbleForExportWork())
    {
        setError(Error::EXPORT_ERROR);
        return;
    }

    this->exportWorker->start();
    emit startExport();
}

void PDF_ExporterAndImageHolder::restartForRenderWork(QPdfDocument *doc)
{
    this->currentHandleDoc = doc;
    createRenderThread();
    initConnectionRender();
}


void PDF_ExporterAndImageHolder::cancelAll()
{
    this->renderWorker->setStopImm();
    this->exportWorker->setStopImm();
    releaseThreads();
    releaseRenderSources();
    if(!isCancelExportLeaveTheRest)
        PDF_RemoveFile::removeFile(exportPath);
    emit cancelFinish();
}


void PDF_ExporterAndImageHolder::doAllWorkOneByOne()
{
    if(!this->isExportable)
    {
        // 先渲染, 在handle渲染的函数里跑导出
        this->shallExportImm = true;
        this->startRenderWork();
        // 退出
        return;
    }
    this->startExportWork();
}

void PDF_ExporterAndImageHolder::releaseRenderThread()
{
    if(this->renderWorker)
    {
        this->renderWorker->quit();
        this->renderWorker->wait();
    }

}
void PDF_ExporterAndImageHolder::releaseExporterThread()
{
    if(this->exportWorker)
    {
        this->exportWorker->quit();
        this->exportWorker->wait();
    }
}

void PDF_ExporterAndImageHolder::releaseThreads()
{
    releaseRenderThread();
    releaseExporterThread();
}

void PDF_ExporterAndImageHolder::releaseRenderSources()
{
    if(!this->renderResults.isEmpty())
    {
        for(auto& each : this->renderResults)
        {
            delete each;
            each = nullptr;
        }
    }
    this->renderResults.clear();
}

PDF_ExporterAndImageHolder::~PDF_ExporterAndImageHolder()
{
    releaseThreads();
    releaseRenderSources();
}



