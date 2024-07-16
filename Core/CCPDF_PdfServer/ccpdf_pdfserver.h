#ifndef CCPDF_PDFSERVER_H
#define CCPDF_PDFSERVER_H
#include "CCPDF_LinkListWidgetManager/ccpdf_pdflinkwidgetmanager.h"
#include "CCPDF_Global.h"
class CCPDF_PDFPageNavigator;
class CCPDF_ZoomController;
class CCPDF_SinglePDF_Widget;
class CCPDF_TextHelper;
class CCPDF_BookMarkManager;
class CCPDF_SearchManager;
class CCPDF_PDfLinkWidgetManager;
class QLabel;
class QPdfPageSelector;


struct CCPDF_PdfServer{
    __MEMEROY_HOLD_BY_OBJ_TREE          __COM_SIG_WIDGET
        CCPDF_PDFPageNavigator*                 pageNavigator;
    __MEMEROY_HOLD_BY_SMT_PTR           __COM_SIG_WIDGET
        std::unique_ptr<CCPDF_ZoomController>   zoomController;
    __MEMEROY_HOLD_BY_SMT_PTR           __COM_SIG_WIDGET
        std::unique_ptr<CCPDF_TextHelper>       textHelper;
    __MEMEROY_HOLD_BY_SMT_PTR           __COM_SIG_WIDGET
    std::unique_ptr<CCPDF_BookMarkManager>      bookMarkManager;
    __MEMEROY_HOLD_BY_SMT_PTR           __COM_SIG_WIDGET
    std::unique_ptr<CCPDF_SearchManager>        searchManager;
    __MEMEROY_HOLD_BY_SMT_PTR           __COM_SIG_WIDGET
    std::unique_ptr<CCPDF_PDfLinkWidgetManager> linkModelManager;
    void    updateGlobal(CCPDF_SinglePDF_Widget* w, QLabel *l, QPdfPageSelector* selector);
    void    updateAllBindPdfWidget(CCPDF_SinglePDF_Widget* w);
    void    setStatusText(QLabel* l);
    CCPDF_SinglePDF_Widget*             current_widget() const {return w;}
private:
    CCPDF_SinglePDF_Widget*             w;
};

#endif // CCPDF_PDFSERVER_H
