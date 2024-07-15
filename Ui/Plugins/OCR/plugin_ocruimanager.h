#ifndef PLUGIN_OCRUIMANAGER_H
#define PLUGIN_OCRUIMANAGER_H
#include "CCPDF_Global.h"
#include "Plugins/OCR/plugin_ocr_uiwidget.h"

class QTabWidget;
struct TesseractOCRTextHelper;
class CCPDF_SinglePDF_Widget;
class Plugin_HistoricalHelper;

class Plugin_OCRUiManager
{
public:
    Plugin_OCRUiManager();
    DISABLE_COPY(Plugin_OCRUiManager);
    void    initOCR_Ui(QTabWidget* w);
    void    setOCR(TesseractOCRTextHelper* w);
    void    scanIfOCRAcceptable();
    bool    setDLLFile(const QString& dllDir);
    void    setOperatingPDF(CCPDF_SinglePDF_Widget* _w){w = _w;scanIfOCRAcceptable();}
    void    setHist(Plugin_HistoricalHelper* h){histHelper = h;}
    void    registerOrUpdateConfigToHist();

private:
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<Plugin_OCR_UiWidget>        ui_widget;
    __MEMEROY_NO_HOLD
    CCPDF_SinglePDF_Widget*         w;
    __MEMEROY_NO_HOLD
        Plugin_HistoricalHelper*    histHelper{nullptr};

};

#endif // PLUGIN_OCRUIMANAGER_H
