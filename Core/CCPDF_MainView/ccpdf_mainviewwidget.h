#ifndef CCPDF_MAINVIEWWIDGET_H
#define CCPDF_MAINVIEWWIDGET_H
#include <QWidget>
#include <QGridLayout>
#include "CCPDF_Global.h"
class CCPDF_MyPDFView;
class QPdfDocument;
class QPdfPageNavigator;
class CCPDF_Loader;

class CCPDF_MainViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit    CCPDF_MainViewWidget(QWidget *parent = nullptr);
    void        setLoader(const CCPDF_Loader* loader, bool auto_render = true);
    void        startRender();
    int         currentPageIndex() const;
    void        setSearchIndex(int index);
    CCPDF_MyPDFView*    getView() const {return core_view.get();}
    ~CCPDF_MainViewWidget();
private:
    friend struct CCPDF_Info;
    friend class CCPDF_SinglePDF_Widget;
    friend class CCPDF_PDFPageNavigator;
    QPdfPageNavigator*                      providePageNavigator() const;
    std::unique_ptr<CCPDF_MyPDFView>        core_view;
    std::unique_ptr<QGridLayout>            internal_layout;
    const CCPDF_Loader* __MEMEROY_NO_HOLD   loader;
signals:

};

#endif // CCPDF_MAINVIEWWIDGET_H
