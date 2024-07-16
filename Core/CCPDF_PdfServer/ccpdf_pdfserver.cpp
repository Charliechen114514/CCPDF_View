#include <QLabel>
#include <QPdfPageSelector>
#include "CCPDF_BookMarkManager/ccpdf_bookmarkmanager.h"
#include "CCPDF_SearchManager/ccpdf_searchmanager.h"
#include "ccpdf_pdfserver.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDF_PDFPageNavigator/ccpdf_pdfpagenavigator.h"
#include "CCPDF_TextHelper/ccpdf_texthelper.h"
#include "CCPDF_ZoomController/ccpdf_zoomcontroller.h"
#include "CCPDF_LinkListWidgetManager/ccpdf_pdflinkwidgetmanager.h"

void CCPDF_PdfServer::updateGlobal(CCPDF_SinglePDF_Widget* w, QLabel* l, QPdfPageSelector *selector)
{
    updateAllBindPdfWidget(w);
    setStatusText(l);
    if(w)
    {
        w->helpSetSelector(selector);
    }
}

void CCPDF_PdfServer::updateAllBindPdfWidget(CCPDF_SinglePDF_Widget* w)
{
    pageNavigator->setOperatingPDF(w);
    zoomController->setOperatingPDF(w);
    textHelper->setOperatingPDF(w);
    bookMarkManager->setOperatingPDF(w);
    searchManager->setOperatingWidget(w);
    linkModelManager->setOperatingPDF(w);
    this->w = w;
}

void CCPDF_PdfServer::setStatusText(QLabel* l)
{
    if(!w)
        return;
    l->setText(w->statusText());
}

