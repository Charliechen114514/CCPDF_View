#include <QPdfSearchModel>
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "CCPDF_PdfView/ccpdf_mypdfview.h"
#include "CCPDF_SearchWidget/ccpdf_searchwidget.h"
#include "ccpdf_searchmanager.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDF_SearchDelegate/CCPDF_SearchDelegate.h"
CCPDF_SearchManager::CCPDF_SearchManager(CCPDF_SearchWidget *w, QObject* Parent):QObject(Parent)
{
    operating_widget = w;
    delegate = std::make_unique<CCPDF_SearchDelegate>();
    searchModel = std::make_unique<QPdfSearchModel>();
    connect(w, &CCPDF_SearchWidget::tellString, this, &CCPDF_SearchManager::setString);
}

void CCPDF_SearchManager::CCPDF_SearchManager::setString(const QString& res)
{
    searchModel->setSearchString(res);
}

void CCPDF_SearchManager::setOperatingWidget(CCPDF_SinglePDF_Widget* w)
{
    if(!w)
        return;
    searchModel->setDocument(w->getLoader()->passDoc());
    w->getView()->setSearchModel(searchModel.get());
    operating_widget->setModel(searchModel.get());
}
