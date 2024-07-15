#ifndef CCPDF_PDFLINKWIDGETMANAGER_H
#define CCPDF_PDFLINKWIDGETMANAGER_H
#include <QObject>
#include <QPdfLinkModel>
#include "CCPDF_Global.h"

class CCPDF_SinglePDF_Widget;
class CCPDF_LinkWidget;

class CCPDF_PDfLinkWidgetManager
{
public:
    explicit    CCPDF_PDfLinkWidgetManager(CCPDF_LinkWidget* w);
    void        setOperatingPDF(CCPDF_SinglePDF_Widget* w);
    void        setPage(int index);
private:
    __MEMEROY_NO_HOLD   CCPDF_LinkWidget*       operatingWidget;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<QPdfLinkModel>              linkModel;
};

#endif // CCPDF_PDFLINKWIDGETMANAGER_H
