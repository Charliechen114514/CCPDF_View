#include <QPdfPageNavigator>
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "CCPDF_PdfView/ccpdf_mypdfview.h"
#include "ccpdf_mainviewwidget.h"
#include <QPdfDocument>

CCPDF_MainViewWidget::CCPDF_MainViewWidget(QWidget *parent)
    : QWidget{parent},
    core_view(new CCPDF_MyPDFView(this)),
    internal_layout(new QGridLayout(this))
{
    this->setLayout(internal_layout.get());
    internal_layout->addWidget(core_view.get());
}

void CCPDF_MainViewWidget::setLoader(const CCPDF_Loader* loader, bool auto_render)
{
    this->loader = loader;
    if(auto_render)
        core_view->setDocument(loader->passDoc());
}

void CCPDF_MainViewWidget::startRender()
{
    if(this->loader)
        core_view->setDocument(loader->passDoc());
}

int CCPDF_MainViewWidget::currentPageIndex() const
{
    if(!this->core_view)
        return -1;
    else
        return core_view->pageNavigator()->currentPage();
}

QPdfPageNavigator* CCPDF_MainViewWidget::providePageNavigator() const
{
    return core_view->pageNavigator();
}

CCPDF_MainViewWidget::~CCPDF_MainViewWidget()
{
    // empty for NULL, nothing to do now
    qDebug() << "Close pdfViewer";
}
