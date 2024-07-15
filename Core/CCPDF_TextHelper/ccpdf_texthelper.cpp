#include "ccpdf_texthelper.h"
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "CCPDF_Info/ccpdf_info.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include <QTextBrowser>
#include <QApplication>
#include <QClipboard>


bool CCPDF_TextHelper::checkVadility()
{
    if(!w){
        e.e = CCPDF_TextHelper::TextGetterHelperError::Error::NO_BIND_PDF;
        return false;
    }
    return true;
}

bool CCPDF_TextHelper::setCurrentPdfText(QTextBrowser* w)
{
    QString text {getCurrentPageText()};
    w->setText(text);
    return text.isEmpty();
}


QString CCPDF_TextHelper::getCurrentPageText()
{
    if(!checkVadility())
        return "";
    int current_page_index = w->pdf_info->currentPageIndex();
    QString txt = w->getLoader()->passDoc()->getAllText
                  (current_page_index).text();
    if(txt.isEmpty()){
        e.e = TextGetterHelperError::Error::NO_DIRECT_GET;
    }
    return txt;
}

void CCPDF_TextHelper::copyToClipBoard()
{
    QString text{getCurrentPageText()};
    if(!isFine())
        return;
    QApplication::clipboard()->setText(text);
}

