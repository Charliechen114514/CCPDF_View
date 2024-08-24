#include "ccpdf_translationwidget.h"
#include "ui_ccpdf_translationwidget.h"

#ifdef SUPPORT_TRANSLATION
#include <QClipboard>
#include <QParallelAnimationGroup>
#include "CCPDF_Animanations/ccpdf_animanations.h"
#include "CCPDF_Error_Helper/CCPDF_ErrorHelper.h"
#include "CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "CCPDF_Utils/ccpdf_messgaeboxutils.h"
#endif
static void __pvt_handleBtnTextTrans(QPushButton* btn, bool state);

CCPDF_TranslationWidget::CCPDF_TranslationWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CCPDF_TranslationWidget) {
    ui->setupUi(this);
#ifndef SUPPORT_TRANSLATION
    this->setEnabled(false);
    return;
#else
    ui->btn_depatch->setEnabled(false);
    QFont font("Microsoft YaHei", 12);  // 使用支持中文的字体，如微软雅黑
    ui->result_textBrowser->setFont(font);
    __pvt_handleBtnTextTrans(ui->btn_setAutoTrans, setAutoTranslate);
    connect(ui->btn_setAutoTrans, &QPushButton::clicked, this,
            &CCPDF_TranslationWidget::opposeAutoTransLate);
    registerAnimation();
#endif
}

CCPDF_TranslationWidget::~CCPDF_TranslationWidget() {
    delete ui;
}

#ifdef SUPPORT_TRANSLATION

static void __pvt_handleBtnTextTrans(QPushButton* btn, bool state) {
    if (state)
        btn->setText("自动翻译: 开");
    else
        btn->setText("自动翻译: 关");
}

static void __pvt_handle_input_text(QString& res) {
    res = res.remove("\n");
}

void CCPDF_TranslationWidget::opposeAutoTransLate() {
    setAutoTranslate = !setAutoTranslate;
    __pvt_handleBtnTextTrans(ui->btn_setAutoTrans, setAutoTranslate);
}

bool CCPDF_TranslationWidget::tryCheck() {
    return CCPDF_FileUtils::FileUtils::isFileExsits(exe);
}

bool CCPDF_TranslationWidget::checkRunnable() {
    if (!CCPDF_FileUtils::FileUtils::isFileExsits(exe)) {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::NoFileExsits(exe);
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details + pac.possible_help, this);
        return false;
    }
    return true;
}

void CCPDF_TranslationWidget::setInput() {
    QString AtDir     = CCPDF_FileUtils::PathUtils::atDir(exe);
    QString inputName = INPUT;
    QString inputPath =
        CCPDF_FileUtils::PathUtils::composePath(AtDir, inputName);
    CCPDF_FileUtils::FileUtils::createFileAnyWay(inputPath);
    QString res = ui->input_textEdit->toPlainText();
    __pvt_handle_input_text(res);
    CCPDF_FileUtils::File_ReadWrite::writeFile(res, inputPath);
}

void CCPDF_TranslationWidget::setTrans(CCPDF_ExternTranslation* w) {
    translations = w;
    connect(translations, &CCPDF_ExternTranslation::finish, this,
            &CCPDF_TranslationWidget::handleRes);
}

void CCPDF_TranslationWidget::setEXE() {
    QString res = CCPDF_FileUtils::SelectFileUtils::selectExsitingFile(
        "选择文件", {"exe"}, "", this);
    if (res.isEmpty()) return;
    setEXE(res);
}

void CCPDF_TranslationWidget::setInputEdit(const QString& what) {
    ui->input_textEdit->setText(what.simplified());
    if (setAutoTranslate && CCPDF_FileUtils::FileUtils::isFileExsits(exe)) {
        makeRun();
    }
}

void CCPDF_TranslationWidget::setEXE(const QString& res) {
    exe = res;
    ui->plugin_exe_edit->setText(res);
    if (tryCheck()) {
        ui->btn_depatch->setEnabled(true);
    }
}

void CCPDF_TranslationWidget::registerAnimation() {
    visible_button_animation = std::make_unique<CCPDF_BinaryStateAnimations>();
    visible_button_animation->bindObjectAndProperty(ui->widget_settings,
                                                    "size");
    visible_button_animation->setDuration(400);
    QObject::connect(visible_button_animation->getAnimation(),
                     &QPropertyAnimation::finished, [this]() {
                         settingVisiblity = !settingVisiblity;
                         ui->widget_settings->setVisible(settingVisiblity);
                     });
}

void CCPDF_TranslationWidget::resizeEvent(QResizeEvent* e [[maybe_unused]]) {
    QSize current_size = ui->widget_settings->size();
    visible_button_animation->setBeginState(current_size);
    visible_button_animation->setEndState(QSize(current_size.width(), 0));
}

void CCPDF_TranslationWidget::opposeVisiSettings() {
    if (settingVisiblity)
        visible_button_animation->startAnimation(settingVisiblity);
    else {
        settingVisiblity = !settingVisiblity;
        ui->widget_settings->setVisible(settingVisiblity);
    }
    ui->btn_setSettingsVisible->setText(settingVisiblity ? "收起设置板"
                                                         : "展开设置板");
}

void CCPDF_TranslationWidget::registerOrUpdate() {
    if (histroyHolder) {
        auto p        = new Plugin_ExeInfo;
        p->PluginType = _TRANSLATION;
        p->exe        = exe;
        p->readAt     = outPut;
        if (!histroyHolder->fetchAccordingType(_TRANSLATION)) {
            histroyHolder->addPluginConfig(p);
        } else {
            histroyHolder->updateConfig(p);
            delete p;
        }
    }
}

void CCPDF_TranslationWidget::setOutPut(const QString& res) {
    outPut = res;
    ui->output_linedit->setText(res);
    ui->output_linedit->setToolTip(res);
}

void CCPDF_TranslationWidget::setOutPut() {
    QString res = CCPDF_FileUtils::SelectFileUtils::selectExsitingDir(
        "选择文件", "", this);
    if (res.isEmpty()) return;
    QString thisFile = CCPDF_ExternTranslation::FILE_NAME;
    QString outPut   = CCPDF_FileUtils::PathUtils::composePath(res, thisFile);
    setOutPut(outPut);
}

void CCPDF_TranslationWidget::makeRun() {
    if (!checkRunnable()) return;
    setInput();
    translations->setTranslationExecutionPlugin(exe);
    translations->setTranslationResultReading(outPut);
    translations->run();
}

void CCPDF_TranslationWidget::handleRes() {
    if (!CCPDF_FileUtils::FileUtils::isFileExsits(outPut)) {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::
            PluginFinishButOutPutFileUnread(outPut);
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details + pac.possible_help, this);
        return;
    }
    registerOrUpdate();
    ui->result_textBrowser->setText(translations->fetchResult());
}

void CCPDF_TranslationWidget::on_btn_copyToClipBoard_clicked() {
    QApplication::clipboard()->setText(ui->result_textBrowser->toPlainText());
}
#endif
