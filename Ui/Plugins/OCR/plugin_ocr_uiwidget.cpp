#include "plugin_ocr_uiwidget.h"
#include "ui_plugin_ocr_uiwidget.h"
#ifdef SUPPORT_TESS_OCR
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "Internal_Option_Compile/ocr/ccpdf_ocrtexthellper.hpp"
#include "CCPDF_Utils/ccpdf_messgaeboxutils.h"
#include "plugin_ocruimanager.h"
#endif

Plugin_OCR_UiWidget::Plugin_OCR_UiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plugin_OCR_UiWidget)
{
    ui->setupUi(this);

#ifndef SUPPORT_TESS_OCR
    this->setEnabled(false);
    return;
#else
    ui->start_OCR->setEnabled(false);
#endif
}

Plugin_OCR_UiWidget::~Plugin_OCR_UiWidget()
{
    delete ui;
}

#ifdef SUPPORT_TESS_OCR
bool Plugin_OCR_UiWidget::setDLLFile(const QString& target)
{
    QString res = CCPDF_FileUtils::FileUtils::getIfFileInTargetDir(target, REQ_FILE);
    if(res.isEmpty()){
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError("未找到文件", QString("没有找到") + REQ_FILE, this);
        return false;
    }
    helper->setImageSavingDir();
    helper->setPluginDependencyPath(target, res);
    record_dll_path = res;
    record_dll_dir = target;
    QString dataSet = target + "/share";
    helper->setDataSets(dataSet.toStdString().c_str(),
                        static_cast<int>(TesseractOCRHandle::SYMBOL_FUNC_INDEX::TesseractWrapper_setTessPrifix));
    helper->setLanguage("chi_sim",
                        static_cast<int>(TesseractOCRHandle::SYMBOL_FUNC_INDEX::TesseractWrapper_setLanguage));
    if(helper->fine())
    {
        ui->start_OCR->setEnabled(true);
        if(manager)
            manager->registerOrUpdateConfigToHist();
        return true;
    }
    else{
        return false;
    }
}

void Plugin_OCR_UiWidget::selectDLLFile()
{
    if(!isBinding()){
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError("没有绑定到PDF", "请先选择PDF!", this);
        return;
    }
    QString target = CCPDF_FileUtils::SelectFileUtils::selectExsitingDir("选择文件夹: TesseractWrapper.dll所在的文件夹");
    if(target.isEmpty()){
        return;
    }
    setDLLFile(target);
}

void Plugin_OCR_UiWidget::doOCR()
{
    if(!helper->fine())
    {
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError("发生错误",helper->errorString(), this);
        return;
    }
    helper->setPicture(static_cast<int>(TesseractOCRHandle::SYMBOL_FUNC_INDEX::TesseractWrapper_setViewImage));
    QString res = helper->getText(
        static_cast<int>(
            TesseractOCRHandle::SYMBOL_FUNC_INDEX::TesseractWrapper_getTextFromImage));
    ui->OCR_Result->setText(res);
}

void Plugin_OCR_UiWidget::setOCRDisable(bool able)
{
    ui->btn_setPluginDLL->setEnabled(able);
    if(able && helper->fine())
        ui->start_OCR->setEnabled(able);
}
#endif



