#ifndef CCPDF_EXTERNALPLUGINS_H
#define CCPDF_EXTERNALPLUGINS_H
#include <CCPDF_Global.h>
class QWidget;
#ifdef SUPPORT_TESS_OCR
#include "External/Internal_Option_Compile/ocr/ccpdf_ocrtexthellper.hpp"
#endif

#ifdef SUPPORT_TRANSLATION
#include "External/External_Option_Compile/CCPDF_ExternTranslations/Translate/ccpdf_externtranslation.h"
#include "Plugins/Translations/ccpdf_translationwidget.h"
#endif

class CCPDF_SinglePDF_Widget;
class Plugin_OCRUiManager;
class Plugin_HistoricalHelper;
class CCPDF_ExternTranslation;

struct CCPDF_ExternalPlugins
{
    CCPDF_ExternalPlugins();
    DISABLE_COPY(CCPDF_ExternalPlugins);
    enum class CurrentSupportPlugin
    {
        DISABLE_ALL_PLUGIN,
        OCR_Plugin,
        TRANSLATION
    };
    void    loadPluginConfig(const QString& where);
    void    writePluginConfig();
    bool    checkPluginSupport(CurrentSupportPlugin w);
    CCPDF_SinglePDF_Widget* w           { nullptr };
    void    updateAllBindPdfWidget(CCPDF_SinglePDF_Widget* w);
    void    activateAccordingToPluginHist();
    std::unique_ptr<Plugin_HistoricalHelper> pluginHist;
    void    setPluginExeWidgets(QWidget* w, CurrentSupportPlugin t);
    void    setPluginInputFromOutWard(const QString& where, CurrentSupportPlugin t);
#ifdef SUPPORT_TESS_OCR
    std::unique_ptr<Plugin_OCRUiManager>    OCRUiManager;
    std::unique_ptr<TesseractOCRTextHelper> tessHandle;

#endif
#ifdef SUPPORT_TRANSLATION
    __MEMEROY_NO_HOLD   CCPDF_TranslationWidget*    translateWidget;
    std::unique_ptr<CCPDF_ExternTranslation>        translations;
#endif
private:
    QList<CurrentSupportPlugin> supportPlugins;
};

#endif // CCPDF_EXTERNALPLUGINS_H
