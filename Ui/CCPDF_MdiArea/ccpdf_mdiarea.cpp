#include "ccpdf_mdiarea.h"

CCPDF_MdiArea::CCPDF_MdiArea(QWidget *w):QMdiArea(w)
{
    this->setDocumentMode(true);
    this->setViewMode(ViewMode::TabbedView);
    this->setTabsClosable(true);
    this->setTabsMovable(true);
}
