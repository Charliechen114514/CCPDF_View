#include <QPdfPageNavigator>
#include "CCPDF_PdfView/ccpdf_mypdfview.h"
#include "CCPDF_MainView/ccpdf_mainviewwidget.h"
#include "ccpdf_pdfpagenavigator.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDF_Info/ccpdf_info.h"
CCPDF_PDFPageNavigator::CCPDF_PDFPageNavigator(QObject *parent)
    : QObject{parent}
{}

void CCPDF_PDFPageNavigator::setOperatingPDF(CCPDF_SinglePDF_Widget* w)
{
    operatingPDF_Widget = w;
}

bool CCPDF_PDFPageNavigator::pageBackWard()
{
    return jump(operatingPDF_Widget->pdf_info->currentPageIndex() - 1);
}

bool CCPDF_PDFPageNavigator::pageForward()
{
    return jump(operatingPDF_Widget->pdf_info->currentPageIndex() + 1);
}

void CCPDF_PDFPageNavigator::pageBegin()
{
    jump(0);
}
void CCPDF_PDFPageNavigator::pageEnd()
{
    jump(operatingPDF_Widget->pdf_info->pageCnt() - 1);
}

bool CCPDF_PDFPageNavigator::checkVadility()
{
    if(!fine())
        return false;
    if(!checkHasWidget())
    {
        e.e = PageNav_Error::Error::NO_BIND_PDF;
        return false;
    }
    return true;
}

bool CCPDF_PDFPageNavigator::jump(const int page)
{
    if(!checkVadility())
        return false;

    if(!checkPageVadility(page))
        return false;

    operatingPDF_Widget->core_view->
        core_view->pageNavigator()->jump(page, {});

    operatingPDF_Widget->freshPDFInfo();
    return true;
}

bool CCPDF_PDFPageNavigator::jump(const int page, QPointF link)
{
    if(!checkVadility())
        return false;

    if(!checkPageVadility(page))
        return false;

    operatingPDF_Widget->core_view->
        core_view->pageNavigator()->jump(page, link);
    return true;
}

bool CCPDF_PDFPageNavigator::checkPageVadility(int page)
{
    if(page < 0)
    {
        e.e = PageNav_Error::Error::PAGE_UNDERFLOW;
        return false;
    }

    if(page >= operatingPDF_Widget->pdf_info->pageCnt())
    {
        e.e = PageNav_Error::Error::PAGE_OVERFLOW;
        return false;
    }

    return true;
}

CCPDF_PDFPageNavigator::~CCPDF_PDFPageNavigator()
{
    qDebug() << "Erase Navigator";
}

