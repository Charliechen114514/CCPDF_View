#ifndef CCPDF_SEARCHMANAGER_H
#define CCPDF_SEARCHMANAGER_H
#include <QObject>
#include <QPdfSearchModel>
#include "CCPDF_SearchDelegate/CCPDF_SearchDelegate.h"
#include "CCPDF_Global.h"
class CCPDF_SearchWidget;
class CCPDF_SinglePDF_Widget;
class CCPDF_SearchDelegate;
class QPdfSearchModel;

class CCPDF_SearchManager : public QObject
{
    Q_OBJECT
public:
    CCPDF_SearchManager() = delete;
    DISABLE_COPY(CCPDF_SearchManager);
    CCPDF_SearchManager(CCPDF_SearchWidget* w, QObject *Parent = nullptr);
    void    setOperatingWidget(CCPDF_SinglePDF_Widget* w);
    void    setString(const QString& res);
private:
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_SearchDelegate>   delegate;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<QPdfSearchModel>        searchModel;
    CCPDF_SearchWidget*                     operating_widget;
};

#endif // CCPDF_SEARCHMANAGER_H
