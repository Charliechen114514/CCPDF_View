#ifndef CCPDF_SINGLEPDF_WIDGET_H
#define CCPDF_SINGLEPDF_WIDGET_H
#include <QWidget>
#include <QPageSize>
#include "CCPDF_Historical/Historical/historical_record.h"
#include "CCPDF_Global.h"
struct CCPDF_Info;
class CCPDF_Loader;
class CCPDF_MyPDFView;
class CCPDF_MainViewWidget;
class CCPDF_PDFPageNavigator;
class QPdfDocument;
struct PDF_Export_Config
{
    QSize pageSize;
};

class CCPDF_SinglePDF_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit                    CCPDF_SinglePDF_Widget(QWidget *parent = nullptr);
    ~CCPDF_SinglePDF_Widget();
    bool                        loadPDF(QString Path);
    void                        freshPDFInfo();
    __MEMEROY_HOLD_BY_SMT_PTR   std::unique_ptr<CCPDF_Info> pdf_info;
    PDF_Info_Historical_Record  getRecord();
    QString                     pdfPath();
    QString                     statusText() const;
    CCPDF_MyPDFView*            getView() const;
    CCPDF_Loader*               getLoader() const;
    QImage                      renderImage();
    PDF_Export_Config           pdfConfig;
    void                        setSearchIndex(int index);
private:
    void                        calcPageSize();
    friend class CCPDF_PDFPageNavigator;
    __MEMEROY_HOLD_BY_OBJ_TREE  CCPDF_Loader*               loader;
    __MEMEROY_HOLD_BY_OBJ_TREE  CCPDF_MainViewWidget*       core_view;
signals:
    void                        updateRecord(PDF_Info_Historical_Record r);
};

#endif // CCPDF_SINGLEPDF_WIDGET_H
