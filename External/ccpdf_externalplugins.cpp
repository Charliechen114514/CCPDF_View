#include "ccpdf_externalplugins.h"
#ifdef SUPPORT_TESS_OCR
#include "Internal_Option_Compile/ocr/ocranalisishelper.h"
#endif
#include "Core/CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.h"
#include "Plugins/OCR/plugin_ocruimanager.h"

CCPDF_ExternalPlugins::CCPDF_ExternalPlugins():
    pluginHist(new Plugin_HistoricalHelper)
#ifdef SUPPORT_TESS_OCR
    ,OCRUiManager(new Plugin_OCRUiManager)
    ,tessHandle(new TesseractOCRTextHelper(new TesseractOCRHandle))
#endif
#ifdef SUPPORT_TRANSLATION
    ,translations(new CCPDF_ExternTranslation(nullptr))
#endif
{
#ifdef SUPPORT_TESS_OCR
    supportPlugins << CurrentSupportPlugin::OCR_Plugin;
#endif

#ifdef SUPPORT_TRANSLATION
    supportPlugins << CurrentSupportPlugin::TRANSLATION;
#endif
#ifdef SUPPORT_TESS_OCR
    tessHandle->setOperatingPDF(nullptr);
    OCRUiManager->setOperatingPDF(nullptr);
    OCRUiManager->setHist(pluginHist.get());
#endif
}

bool CCPDF_ExternalPlugins::
checkPluginSupport(CurrentSupportPlugin w)
{
    return supportPlugins.contains(w);
}

void CCPDF_ExternalPlugins::
updateAllBindPdfWidget(CCPDF_SinglePDF_Widget* w[[maybe_unused]])
{
#ifdef SUPPORT_TESS_OCR
    tessHandle->setOperatingPDF(w);
    OCRUiManager->setOperatingPDF(w);
#endif
}

void CCPDF_ExternalPlugins::
activateAccordingToPluginHist()
{
    if(pluginHist->ownsSupportiveInfoType(_OCR_TESS))
    {
        auto record = pluginHist->fetchAccordingType(_OCR_TESS);
        if(!record)
            goto TRANS;
#ifdef SUPPORT_TESS_OCR
        if(record->inner_type() == Plugin_Info::DLL)
        {
            auto res = dynamic_cast<const Plugin_DLLInfo*>(record);
            if(!res->PluginDependencyDir.isEmpty())
                OCRUiManager->setDLLFile(res->PluginDependencyDir);
        }
#endif
    }

TRANS:
    if(pluginHist->ownsSupportiveInfoType(_TRANSLATION))
    {
        auto record = pluginHist->fetchAccordingType(_TRANSLATION);
        if(!record)
            return;
#ifdef SUPPORT_TRANSLATION
        if(record->inner_type() == Plugin_Info::EXE)
        {
            auto res = dynamic_cast<const Plugin_ExeInfo*>(record);
            if(res)
            {
                this->translateWidget->setEXE(res->exe);
                this->translateWidget->setOutPut(res->readAt);
            }
        }
#endif
    }
}

void CCPDF_ExternalPlugins::
setPluginExeWidgets(QWidget* w[[maybe_unused]], CurrentSupportPlugin t)
{
    switch(t)
    {
    case CurrentSupportPlugin::DISABLE_ALL_PLUGIN:break;
    case CurrentSupportPlugin::OCR_Plugin:break;
    case CurrentSupportPlugin::TRANSLATION:
#ifdef SUPPORT_TRANSLATION
        auto res = dynamic_cast<CCPDF_TranslationWidget*>(w);
        if(!res)return;
        res->setTrans(this->translations.get());
        res->setHolder(pluginHist.get());
        translateWidget = res;
#endif
        break;
    }
}

void CCPDF_ExternalPlugins::
setPluginInputFromOutWard(const QString& what[[maybe_unused]], CurrentSupportPlugin t)
{
    switch(t)
    {
    case CurrentSupportPlugin::DISABLE_ALL_PLUGIN:
        break;
    case CurrentSupportPlugin::OCR_Plugin:
#ifdef SUPPORT_TESS_OCR
#endif
        break;
    case CurrentSupportPlugin::TRANSLATION:
#ifdef SUPPORT_TRANSLATION
        translateWidget->setInputEdit(what);
#endif
        break;
    }
}

void CCPDF_ExternalPlugins::
writePluginConfig()
{
    pluginHist->writePluginInfo_HistoricalRecord();
}

