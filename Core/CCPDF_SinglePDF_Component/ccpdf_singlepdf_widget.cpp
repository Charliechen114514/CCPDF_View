#include "CCPDF_MainView/ccpdf_mainviewwidget.h"
#include "ccpdf_singlepdf_widget.h"
#include "CCPDF_Error_Helper/CCPDF_ErrorHelper.h"
#include "CCPDF_Info/ccpdf_info.h"
#include "CCPDF_PdfView/ccpdf_mypdfview.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "CCPDF_Utils/ccpdf_messgaeboxutils.h"
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "CCPDF_MainView/ccpdf_mainviewwidget.h"
#include <QGuiApplication>
#include <QScreen>
CCPDF_SinglePDF_Widget::CCPDF_SinglePDF_Widget(QWidget *parent)
    : QWidget{parent},
    pdf_info(new CCPDF_Info),
    loader(new CCPDF_Loader(this)),
    core_view(new CCPDF_MainViewWidget(this))
{
    this->setLayout(new QGridLayout(this));
    this->layout()->addWidget(core_view);
}

PDF_Info_Historical_Record  CCPDF_SinglePDF_Widget::getRecord(){
    return {loader->path(), pdf_info->currentPageIndex()};
}

QString CCPDF_SinglePDF_Widget::statusText() const
{
    return pdf_info->statuText();
}

CCPDF_MyPDFView* CCPDF_SinglePDF_Widget::getView() const
{
    return core_view->getView();
}

CCPDF_Loader*   CCPDF_SinglePDF_Widget::getLoader() const
{
    return loader;
}

QImage CCPDF_SinglePDF_Widget::renderImage()
{
    return loader->passCurrentImage(pdf_info->currentPageIndex(), pdfConfig.pageSize);
}

void CCPDF_SinglePDF_Widget::setSearchIndex(int index)
{
    core_view->getView()->setCurrentSearchResultIndex(index);
}

QString CCPDF_SinglePDF_Widget::pdfPath()
{
    return loader->path();
}


CCPDF_SinglePDF_Widget::~CCPDF_SinglePDF_Widget()
{
    qDebug() << "Close Single Widget";
}

void CCPDF_SinglePDF_Widget::freshPDFInfo()
{
    pdf_info->updateCoreInfo(loader);
    pdf_info->updateRunTimeInfo(core_view);
}

bool CCPDF_SinglePDF_Widget::loadPDF(QString path)
{
    if(!CCPDF_FileUtils::Prefix_Precheck::isPDFFile(path))
    {
        auto err_msg =
            CCPDF_Error_Helper::ErrorMessgageUtils::UnsupportedFormat(path);
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            err_msg.title, err_msg.details, this);
        return false;
    }

    loader->loadPDF(path);
    core_view->setLoader(loader);
    calcPageSize();
    // update loading infos
    freshPDFInfo();
    return true;
}


void CCPDF_SinglePDF_Widget::calcPageSize()
{
    pdfConfig.pageSize = QPageSize(QPageSize::PageSizeId::A4).size(QPageSize::Unit::Point).toSize();
    QScreen* screen = QGuiApplication::primaryScreen();
    int dpiX =  screen->physicalDotsPerInchX();
    int dpiY =  screen->physicalDotsPerInchX();
    pdfConfig.pageSize.setWidth((pdfConfig.pageSize.width() * dpiX) / 36.0);
    pdfConfig.pageSize.setHeight((pdfConfig.pageSize.height() * dpiY) / 36.0);
}
