#include "ccpdf_translationwidget.h"
#include "ui_ccpdf_translationwidget.h"

#ifdef SUPPORT_TRANSLATION
#include "CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "CCPDF_Utils/ccpdf_messgaeboxutils.h"
#include "CCPDF_Error_Helper/CCPDF_ErrorHelper.h"
#endif


CCPDF_TranslationWidget::CCPDF_TranslationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCPDF_TranslationWidget)
{
    ui->setupUi(this);

#ifndef SUPPORT_TRANSLATION
    this->setEnabled(false);
    return;
#else
    ui->btn_depatch->setEnabled(false);
    QFont font("Microsoft YaHei", 12);  // 使用支持中文的字体，如微软雅黑
    ui->result_textBrowser->setFont(font);
#endif
}

CCPDF_TranslationWidget::~CCPDF_TranslationWidget()
{
    delete ui;
}

#ifdef SUPPORT_TRANSLATION
bool CCPDF_TranslationWidget::tryCheck()
{
    return CCPDF_FileUtils::FileUtils::isFileExsits(exe);
}

bool CCPDF_TranslationWidget::checkRunnable()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(exe))
    {
        auto pac =  CCPDF_Error_Helper::ErrorMessgageUtils::NoFileExsits(exe);
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title,
            pac.details + pac.possible_help,
            this
        );
        return false;
    }
    return true;
}

void CCPDF_TranslationWidget::setInput()
{
    QString AtDir = CCPDF_FileUtils::PathUtils::atDir(exe);
    QString inputName = INPUT;
    QString inputPath = CCPDF_FileUtils::PathUtils::composePath(AtDir, inputName);
    CCPDF_FileUtils::FileUtils::createFileAnyWay(inputPath);
    QString res = ui->input_textEdit->toPlainText();
    CCPDF_FileUtils::File_ReadWrite::writeFile(res, inputPath);
}

void CCPDF_TranslationWidget::setTrans(CCPDF_ExternTranslation* w)
{
    translations = w;
    connect(translations, &CCPDF_ExternTranslation::finish, this, &CCPDF_TranslationWidget::handleRes);
}


void CCPDF_TranslationWidget::setEXE()
{
    QString res = CCPDF_FileUtils::SelectFileUtils::selectExsitingFile("选择文件", {"exe"}, "", this);
    if(res.isEmpty())
        return;
    setEXE(res);
}

void CCPDF_TranslationWidget::setInputEdit(const QString& what){
    ui->input_textEdit->setText(what);
}

void CCPDF_TranslationWidget::setEXE(const QString& res)
{
    exe = res;
    ui->plugin_exe_edit->setText(res);
    if(tryCheck())
    {
        ui->btn_depatch->setEnabled(true);
    }
}

void CCPDF_TranslationWidget::registerOrUpdate()
{
    if(histroyHolder)
    {
        if(!histroyHolder->fetchAccordingType(_TRANSLATION))
        {
            auto p = new Plugin_ExeInfo;
            p->PluginType = _TRANSLATION;
            p->exe = exe;
            p->readAt = outPut;
            histroyHolder->addPluginConfig(p);
        }
        else{
            auto p = new Plugin_ExeInfo;
            p->PluginType = _TRANSLATION;
            p->exe = exe;
            p->readAt = outPut;
            histroyHolder->updateConfig(p);
            delete p;
        }
    }
}

void CCPDF_TranslationWidget::setOutPut(const QString& res)
{
    outPut = res;
    ui->output_linedit->setText(res);
    ui->output_linedit->setToolTip(res);
}

void CCPDF_TranslationWidget::setOutPut()
{
    QString res = CCPDF_FileUtils::SelectFileUtils::selectExsitingDir("选择文件", "", this);
    if(res.isEmpty())
        return;
    QString thisFile = CCPDF_ExternTranslation::FILE_NAME;
    QString outPut = CCPDF_FileUtils::PathUtils::composePath(res, thisFile);
    setOutPut(outPut);
}

void CCPDF_TranslationWidget::makeRun()
{
    if(!checkRunnable())
        return;
#ifdef SUPPORT_TRANSLATION
    setInput();
    translations->setTranslationExecutionPlugin(exe);
    translations->setTranslationResultReading(outPut);
    translations->run();
#endif
}

void CCPDF_TranslationWidget::handleRes()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(outPut))
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::
            PluginFinishButOutPutFileUnread(outPut);
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title,
            pac.details + pac.possible_help,
            this
        );
        return;
    }
    registerOrUpdate();
    ui->result_textBrowser->setText(translations->fetchResult());
}
#endif
