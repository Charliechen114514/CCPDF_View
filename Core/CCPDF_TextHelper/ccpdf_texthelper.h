#ifndef CCPDF_TEXTHELPER_H
#define CCPDF_TEXTHELPER_H
#include "CCPDF_Global.h"
class CCPDF_SinglePDF_Widget;
class QTextBrowser;
struct TesseractOCRTextHelper;

class CCPDF_TextHelper
{
public:
    CCPDF_TextHelper() = default;
    DISABLE_COPY(CCPDF_TextHelper);
    void        setOperatingPDF(CCPDF_SinglePDF_Widget* w){this->w = w;}
    QString     getCurrentPageText();
    bool        isFine() const {return w;}
    void        copyToClipBoard();
    bool        setCurrentPdfText(QTextBrowser* w);
    struct TextGetterHelperError
    {
        enum class Error
        {
            NO_ERROR,
            NO_BIND_PDF,
            NO_DIRECT_GET,
        }e{Error::NO_ERROR};
        QString errorString(){
            switch(e)
            {
            case Error::NO_ERROR:
                return "";
            case Error::NO_BIND_PDF:
                return "没有绑定PDF";
            case Error::NO_DIRECT_GET:
                return "无法直接获取文字";
            }
            return "Unknown Error";
        }
    };
    TextGetterHelperError::Error    getError(){return e.e;}
    void                            clearError(){e.e = TextGetterHelperError::Error::NO_ERROR;}
private:
    bool                            checkVadility();
    bool                            openUpOCR = true;
    TextGetterHelperError           e;
    __MEMEROY_NO_HOLD CCPDF_SinglePDF_Widget*           w {nullptr};
};

#endif // CCPDF_TEXTHELPER_H
