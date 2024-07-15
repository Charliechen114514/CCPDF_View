#include <QTabWidget>
#include "CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.h"
#include "plugin_ocruimanager.h"
#include "plugin_ocr_uiwidget.h"
#include <QGridLayout>

Plugin_OCRUiManager::Plugin_OCRUiManager():ui_widget(new Plugin_OCR_UiWidget){
    ui_widget->setManager(this);
}

void Plugin_OCRUiManager::initOCR_Ui(QTabWidget* w)
{
#ifndef SUPPORT_TESS_OCR
    return;
#endif
    w->addTab(ui_widget.get(), "OCR");
}

void Plugin_OCRUiManager::setOCR(TesseractOCRTextHelper* helper)
{
    ui_widget->bindOCR(helper);
}

bool Plugin_OCRUiManager::setDLLFile(const QString& dllDir){
    if(ui_widget->setDLLFile(dllDir))
    {
        registerOrUpdateConfigToHist();
        return true;
    }
    return false;
}

void  Plugin_OCRUiManager::registerOrUpdateConfigToHist()
{
    if(histHelper)
    {
        auto record = histHelper->fetchAccordingType(_OCR_TESS);
        if(!record)
        {
            auto new_dll_record = new Plugin_DLLInfo;
            new_dll_record->PluginType = _OCR_TESS;
            new_dll_record->PluginDependencyDir = ui_widget->record_dll_dir;
            new_dll_record->PluginDLLPath = ui_widget->record_dll_path;
            histHelper->addPluginConfig(new_dll_record);
        }
        else
        {
            histHelper->updateConfig(record);
        }
    }
}

void Plugin_OCRUiManager::scanIfOCRAcceptable()
{
    if(!ui_widget->isBinding() || !w)
    {
        ui_widget->setOCRDisable(false);
    }
    else{
        ui_widget->setOCRDisable(true);
    }
}
