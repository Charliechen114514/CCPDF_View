#include <QGridLayout>
#include <QPdfView>
#include <QPdfPageNavigator>
#include <QPdfPageRenderer>

#include "ccpdf_view.h"
#include "ccpdf_loader.h"
#include "qevent.h"

QPdfView::PageMode transPageViewMode(CCPDF_View::PageViewingMode m)
{
    switch(m)
    {
    case CCPDF_View::PageViewingMode::SinglePage:
        return QPdfView::PageMode::SinglePage;
    case CCPDF_View::PageViewingMode::MutliPage:
        return QPdfView::PageMode::MultiPage;
    }
    return QPdfView::PageMode::SinglePage;
}

CCPDF_View::CCPDF_View(QWidget *parent) : QWidget(parent)
{
    this->coreView = new QPdfView(this);
    this->loader = new CCPDF_Loader(this);
    this->pdfLayOut = new QGridLayout(this);
    this->pdfLayOut->addWidget(this->coreView);
}

void CCPDF_View::setPageMode(PageViewingMode m)
{
    this->coreView->setPageMode(transPageViewMode(m));
}

QString CCPDF_View::getErrorString()
{
    return this->loader->getErrorString();
}

bool CCPDF_View::isViewerAccessible()
{
    return coreView && loader && loader->checkIsLoaded();
}

QString CCPDF_View::currentPDFPath()
{
    if(!isViewerAccessible())
        return "";
    return this->loader->getPDFPath();
}

bool CCPDF_View::loadPDF(CCPDF_View::LoadingMethod m, QString path)
{
    switch (m) {
    case LoadingMethod::BY_GIVEN_STR:
        loader->loadPdf(path);break;
    case LoadingMethod::BY_FILE_DIALOG:
        loader->loadPdfByFileDialog(this, "加载PDF");break;
    }

    if(!loader->checkIsLoaded())
        loader->showErrorUI(this);
    this->coreView->setDocument(loader->coreDocument);
    // this->coreView->setZoomMode(QPdfView::ZoomMode::FitInView);
    return toPage(0);
}

void CCPDF_View::keyPressEvent(QKeyEvent* env){
    env->accept();
}


int CCPDF_View::currentPageCnt(){
    if(!isViewerAccessible())
        return false;
    return this->loader->getPageCount();
}

int CCPDF_View::currentPage(){
    if(!isViewerAccessible())
        return false;
    return this->coreView->pageNavigator()->currentPage();
}

bool CCPDF_View::isPageAccessible(int page)
{
    if(!isViewerAccessible())
        return false;

    if(page >= this->loader->getPageCount() || page < 0)
        return false;
    return true;
}

bool CCPDF_View::toPage(int page)
{
    if(!isPageAccessible(page)){
        return false;
    }
    this->coreView->pageNavigator()->jump(page, {});
    return true;
}

QString CCPDF_View::getCurruntPDFDescriptions()
{
    if(!this->isViewerAccessible())
        return "尚未加载任何内容";
    return QString("当前你在" + QString::number(currentPage()) + "页， 总共有 " + QString::number(currentPageCnt()) + "页");
}


bool CCPDF_View::zoomPage(const qreal pageZoomFactor)
{
    if(pageZoomFactor <= ZOOM_MIN || pageZoomFactor >= ZOOM_MAX)
        return false;
    this->coreView->setZoomFactor(pageZoomFactor);
    return true;
}

qreal CCPDF_View::zoomFactor() const
{
    return this->coreView->zoomFactor();
}

void CCPDF_View::closeView()
{
    if(!this->isViewerAccessible())
        return;
    this->coreView->close();
    this->loader->closeThisDocument();
}

QImage CCPDF_View::getImagedFile()
{
    if(!isPageAccessible(currentPage()))
        return QImage();
    return this->loader->coreDocument->render(currentPage(), QSize(640, 960));
}

CCPDF_View::~CCPDF_View()
{
    delete this->loader;
    delete this->coreView;
    delete this->pdfLayOut;
    this->loader = nullptr;
    this->coreView = nullptr;
}




