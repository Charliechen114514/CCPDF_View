#include "ocr_mainwindow.h"
#include "qmessagebox.h"
#include "ui_ocr_mainwindow.h"
#include "PDF_Utils.h"
#include "eventhandler.h"
static const char* OCR_WINDOW_TITLE = "OCR识别";

OCR_MainWindow::OCR_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OCR_MainWindow)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::ColorRole::Window, QColor(255,255,255));
    ui->image_label->setPalette(pa);
    setWindowTitle(OCR_WINDOW_TITLE);
    initUI();
}

void OCR_MainWindow::setImageSaveDirPath(QString imageSavePath_DIR)
{
    this->imageSavePath_DIR = imageSavePath_DIR;
}
void OCR_MainWindow::setResultSaveDirPath(QString resultSavePath_DIR)
{
    this->resultSavePath_DIR = resultSavePath_DIR;
};
void OCR_MainWindow::setOCRtExePath(QString exePath)
{
    this->exeLibPath = exePath;
}
QString OCR_MainWindow::getImageSaveDir()
{
    return imageSavePath_DIR;
}
QString OCR_MainWindow::getResultDir()
{
    return resultSavePath_DIR;
}
QString OCR_MainWindow::getExePath()
{
    return exeLibPath;
}


void OCR_MainWindow::bindImage(QImage i, QString pdfPath)
{
    if(ocrPackage)
    {
        ocrPackage->clearPackages();
    }
    ocr_image = i;
    this->pdfPath = pdfPath;
    displayImage();
}

void OCR_MainWindow::initUI()
{
    refreshPathEdit();
    initMenu();
}

void OCR_MainWindow::initMenu()
{
    this->actionHandler = new ActionHandler<OCR_MainWindow>;
    this->actionHandler->insertConnections(ui->action_setTesseractPath, &OCR_MainWindow::on_btn_setExe_clicked);
    this->actionHandler->insertConnections(ui->action_setImageSaveDirPath, &OCR_MainWindow::on_btn_set_ImageDir_clicked);
    this->actionHandler->insertConnections(ui->action_setResultTxtDir, &OCR_MainWindow::on_btn_set_textDir_clicked);
    this->actionHandler->insertConnections(ui->action_setChinese, &OCR_MainWindow::setChinese);
    this->actionHandler->insertConnections(ui->action_setEnglish, &OCR_MainWindow::setEnglish);
    this->actionHandler->insertConnections(ui->action_viewConfig, &OCR_MainWindow::viewConfig);
    this->actionHandler->insertConnections(ui->action_setDefaultConfigAll, &OCR_MainWindow::recoverDefaultConfig);
    this->actionHandler->insertConnections(ui->action_clearImages, &OCR_MainWindow::clearImage);
    this->actionHandler->insertConnections(ui->action_clearRes, &OCR_MainWindow::clearRes);
    this->actionHandler->insertConnections(ui->action_clearAll, &OCR_MainWindow::clearAll);
    this->actionHandler->connectAll(this);
}

void OCR_MainWindow::registerOCRSignal()
{
    connect(ocrPackage, &OCRPackage::finishAll, this, &OCR_MainWindow::handleReceivingResult);
}

void OCR_MainWindow::refreshPathEdit()
{
    ui->exeEdit->setText(this->exeLibPath);
    ui->imageDirEdit->setText(this->imageSavePath_DIR);
    ui->resultEdit->setText(this->resultSavePath_DIR);
    ui->exeEdit->setToolTip(this->exeLibPath);
    ui->imageDirEdit->setToolTip(this->imageSavePath_DIR);
    ui->resultEdit->setToolTip(this->resultSavePath_DIR);
}

void OCR_MainWindow::displayImage()
{
    if(isTaskDetachable())
        ui->image_label->setPixmap(QPixmap::fromImage(ocr_image));
    configImage();
}

void OCR_MainWindow::configImage()
{
    if(!isTaskDetachable())
        return;
    if(ocrPackage)
        delete ocrPackage;
    ocrPackage = new OCRPackage();
    registerOCRSignal();
    QString savingPath =  PDF_Saver::saverNameProducer(
                            this->imageSavePath_DIR,
                            PDF_LocationDefaults::getFileNameByPath(this->pdfPath),".pdf").remove(".pdf") + ".png";

    PDF_Saver::saveImage(ui->image_label->grab().toImage(), savingPath);
    ocrPackage->addSinglePic(savingPath);
    ocrPackage->configExecutableOCRPath(this->exeLibPath);
    ocrPackage->configSavingDirPath(this->resultSavePath_DIR);
    ui->btn_depatchTask->setEnabled(ocrPackage->tryifIsRunnable());
    emit enableStartRecognize(ocrPackage->tryifIsRunnable());
}

void OCR_MainWindow::handleReceivingResult()
{
    this->ocrText = ocrPackage->getResult().first();
    ui->ocrTextResultBrowser->setText(this->ocrText);
    emit handInTheOCRResult(this->ocrText);
}


void OCR_MainWindow::postTheConfigChangeEvent()
{
    QStringList* l = new QStringList;
    *l << this->exeLibPath << this->imageSavePath_DIR << this->resultSavePath_DIR;
    emit configPathFileChange(l);
}


void OCR_MainWindow::startMission()
{
    if(!ocrPackage->checkMissionStartAble())
    {
        QMessageBox::critical(this, "出错了！", ocrPackage->errorString());
        return;
    }
    ocrPackage->startRecognize();
}

bool OCR_MainWindow::setChinese()
{
    this->ocrPackage->setLanguage(OCRPackage::LanguageOCR::CHINESE);
    ui->action_setChinese->setText("中文√");
    ui->action_setEnglish->setText("英文");
    return true;
}

bool OCR_MainWindow::setEnglish()
{
    this->ocrPackage->setLanguage(OCRPackage::LanguageOCR::ENGLISH);
    ui->action_setChinese->setText("中文");
    ui->action_setEnglish->setText("英文√");
    return true;
}

QString OCR_MainWindow::getOCRConfigDescriptions()
{
    return QString("当前的配置:\n") +
    "Tesseract配置路径:> " + getExePath() + "\n" +
    "Image存储位置:> " + getImageSaveDir() + "\n" +
           "结果存储位置:> " + getResultDir() + "\n";
}

bool OCR_MainWindow::recoverDefaultConfig()
{
    setOCRtExePath();
    setImageSaveDirPath();
    setResultSaveDirPath();
    refreshPathEdit();
    emit enableStartRecognize(ocrPackage->tryifIsRunnable());
    return true;
}


void OCR_MainWindow::on_btn_depatchTask_clicked()
{
    configImage();
    startMission();
}

bool OCR_MainWindow::on_btn_setExe_clicked()
{
    QString it;
    PDF_LocationDefaults::getOpenFileName(it, this);
    if(it.isEmpty()){
        return false;
    }
    setOCRtExePath(it);
    refreshPathEdit();
    postTheConfigChangeEvent();
    return true;
}


bool OCR_MainWindow::on_btn_set_ImageDir_clicked()
{
    QString it = PDF_GetDir::getDir(this, "选择文件夹", "选择文件夹");
    if(it.isEmpty()){
        return false;
    }
    setImageSaveDirPath(it);
    refreshPathEdit();
    postTheConfigChangeEvent();
    return true;
}


bool OCR_MainWindow::on_btn_set_textDir_clicked()
{
    QString it = PDF_GetDir::getDir(this, "选择文件夹", "选择文件夹");
    if(it.isEmpty()){
        return false;
    }
    setResultSaveDirPath(it);
    refreshPathEdit();
    postTheConfigChangeEvent();
    return true;
}

bool OCR_MainWindow::viewConfig()
{
    QMessageBox::information(this, "配置", getOCRConfigDescriptions());
    return true;
}

bool OCR_MainWindow::isTaskDetachable()
{
    return !ocr_image.isNull();
}


bool OCR_MainWindow::clearImage()
{
    if(!PDF_RemoveFile::removeDir(this->imageSavePath_DIR))
    {
        QMessageBox::critical(this, "清理失败！","尚未清理成功！请去" + this->imageSavePath_DIR + " 查看！");
        return false;
    }
    return true;
}

bool OCR_MainWindow::clearRes()
{
    if(!PDF_RemoveFile::removeDir(this->resultSavePath_DIR))
    {
        QMessageBox::critical(this, "清理失败！","尚未清理成功！请去" + this->resultSavePath_DIR + " 查看！");
        return false;
    }
    return true;
}

bool OCR_MainWindow::clearAll()
{
    bool s1 = clearImage();
    bool s2 = clearRes();
    return s1 && s2;
}

OCR_MainWindow::~OCR_MainWindow()
{
    delete ocrPackage;
    delete actionHandler;
    delete ui;
}
