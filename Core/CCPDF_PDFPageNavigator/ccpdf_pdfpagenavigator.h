#ifndef CCPDF_PDFPAGENAVIGATOR_H
#define CCPDF_PDFPAGENAVIGATOR_H
#include "CCPDF_Global.h"
#include <QObject>
class CCPDF_SinglePDF_Widget;


class CCPDF_PDFPageNavigator : public QObject
{
    Q_OBJECT
public:
    CCPDF_PDFPageNavigator() = default;
    ~CCPDF_PDFPageNavigator();
    struct PageNav_Error {
        enum class Error{
            NO_ERROR,
            NO_BIND_PDF,
            PAGE_OVERFLOW,
            PAGE_UNDERFLOW,
            PAGE_IDX_FMT_INVALID
        } e {Error::NO_ERROR};
        QString errorString(){
            switch(e){
                case Error::NO_ERROR:return "";
                case Error::PAGE_OVERFLOW:
                    return "页码上溢！";
                case Error::PAGE_UNDERFLOW:
                    return "页码下溢！";
                case Error::PAGE_IDX_FMT_INVALID:
                    return "提供的页码存在格式问题";
                case Error::NO_BIND_PDF:
                    return "没有绑定的PDF";
                    break;
                }
            return "未知错误";
        }
    };
    PageNav_Error::Error    getError(){return e.e;}
    explicit                CCPDF_PDFPageNavigator(QObject *parent = nullptr);
    void                    setOperatingPDF(CCPDF_SinglePDF_Widget* w){operatingPDF_Widget = w;}
    bool                    pageBackWard();
    bool                    pageForward();
    void                    pageBegin();
    void                    pageEnd();
    bool                    jump(const int page);
    bool                    jump(const int page, QPointF link);
    bool                    fine(){return e.e == PageNav_Error::Error::NO_ERROR;}
    void                    clearError(){e.e = PageNav_Error::Error::NO_ERROR;}
private:
    __MEMEROY_NO_HOLD CCPDF_SinglePDF_Widget*       operatingPDF_Widget {nullptr};
    bool                                            checkHasWidget(){if(!operatingPDF_Widget) e.e = PageNav_Error::Error::NO_BIND_PDF; return operatingPDF_Widget;};
    bool                                            checkVadility();
    bool                                            checkPageVadility(int page);
    PageNav_Error                                   e;
signals:
    void                                            updatePage(CCPDF_SinglePDF_Widget*);
};

#endif // CCPDF_PDFPAGENAVIGATOR_H
