#ifndef OCR_MAINWINDOW_H
#define OCR_MAINWINDOW_H
#include <QMainWindow>
#include "ocrpackage.h"
#include "PDF_PathSettings.h"
template<class Window>
class ActionHandler;

namespace Ui {
class OCR_MainWindow;
}

class OCR_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit    OCR_MainWindow(QWidget *parent = nullptr);
    void        bindImage(QImage i, QString pdfPath);
    void        displayImage();

    void        configImage();
    void        refreshPathEdit();
    void        setImageSaveDirPath(QString imageSavePath_DIR = IMAGE_SAVE_DIR_PATH);
    void        setResultSaveDirPath(QString resultSavePath_DIR = TEXT_SAVE_DIR_PATH);
    void        setOCRtExePath(QString exePath = OCR_EXE_PATH);
    QString     getImageSaveDir();
    QString     getResultDir();
    QString     getExePath();
    void        postTheConfigChangeEvent();
    void        startMission();
    bool        isTaskDetachable();
    bool        clearImage();
    bool        clearRes();
    bool        clearAll();
    ~OCR_MainWindow();

signals:
    void    enableStartRecognize(bool state);
    void    handInTheOCRResult(QString Text);
    void    configPathFileChange(QStringList* w);
private slots:
    bool    setChinese();
    bool    viewConfig();
    bool    setEnglish();
    bool    recoverDefaultConfig();

    void    handleReceivingResult();


    void    on_btn_depatchTask_clicked();

    bool    on_btn_setExe_clicked();

    bool    on_btn_set_ImageDir_clicked();

    bool    on_btn_set_textDir_clicked();

    QString getOCRConfigDescriptions();

private:
    Ui::OCR_MainWindow *ui;
    QString                             imageSavePath_DIR   = IMAGE_SAVE_DIR_PATH;
    QString                             resultSavePath_DIR  = TEXT_SAVE_DIR_PATH;
    QString                             exeLibPath          = OCR_EXE_PATH;
    ActionHandler<OCR_MainWindow>*      actionHandler;

    OCRPackage*                         ocrPackage = nullptr;
    QImage                              ocr_image;
    QString                             pdfPath;
    QString                             ocrText;

    void                                initUI();
    void                                initMenu();
    void                                registerOCRSignal();

    void                                missionStart();
};

#endif // OCR_MAINWINDOW_H
