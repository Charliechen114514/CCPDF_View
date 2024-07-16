#include "CCPDF_BookMarkManager/BookMarkModel/ccpdf_bookmarkmodel.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "ccpdf_bookmarkmanager.h"
#include "ccpdf_bookmarkwidget.h"

CCPDF_BookMarkManager::CCPDF_BookMarkManager(CCPDF_BookMarkWidget* w)
{
    operatingWidget = w;
    book_mark_model = std::make_unique<CCPDF_BookMarkModel>();
}

void CCPDF_BookMarkManager::setOperatingPDF(CCPDF_SinglePDF_Widget* m)
{
    if(!m)return;
    book_mark_model->setDocument(m->getLoader()->passDoc());
    operatingWidget->setModel(book_mark_model.get());
}
