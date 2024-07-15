#include <QPdfLinkModel>
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "CCPDF_Info/ccpdf_info.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "ccpdf_pdflinkwidgetmanager.h"
#include "CCPDF_LinkWidget/ccpdf_linkwidget.h"
CCPDF_PDfLinkWidgetManager::CCPDF_PDfLinkWidgetManager(CCPDF_LinkWidget *w)
{
    operatingWidget = w;
    linkModel = std::make_unique<QPdfLinkModel>();
}


void CCPDF_PDfLinkWidgetManager::setOperatingPDF(CCPDF_SinglePDF_Widget* w)
{
    if(!w)
        return;
    linkModel->setDocument(w->getLoader()->passDoc());
    linkModel->setPage(w->pdf_info->currentPageIndex());
    operatingWidget->setModel(linkModel.get());
}

void CCPDF_PDfLinkWidgetManager::setPage(int index)
{
    linkModel->setPage(index);
}
