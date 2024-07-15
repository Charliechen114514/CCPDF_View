#ifndef CCPDF_BOOKMARKMANAGER_H
#define CCPDF_BOOKMARKMANAGER_H
#include <QPdfBookmarkModel>
#include "CCPDF_Global.h"

class CCPDF_BookMarkWidget;
class CCPDF_SinglePDF_Widget;
class CCPDF_BookMarkManager
{
public:
    CCPDF_BookMarkManager(CCPDF_BookMarkWidget* b);
    DISABLE_COPY(CCPDF_BookMarkManager);
    void                    setOperatingPDF(CCPDF_SinglePDF_Widget* m);
private:
    CCPDF_BookMarkWidget*               operatingWidget;
    std::unique_ptr<QPdfBookmarkModel>  book_mark_model;
};

#endif // CCPDF_BOOKMARKMANAGER_H
