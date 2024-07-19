#ifndef PLUGIN_OCR_UIWIDGET_H
#define PLUGIN_OCR_UIWIDGET_H
#include <QWidget>
#ifdef SUPPORT_TESS_OCR
#include "CCPDF_Global.h"
#endif
struct TesseractOCRTextHelper;
class Plugin_OCRUiManager;

namespace Ui {
class Plugin_OCR_UiWidget;
}

class Plugin_OCR_UiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Plugin_OCR_UiWidget(QWidget *parent = nullptr);
    ~Plugin_OCR_UiWidget();
private:
    Ui::Plugin_OCR_UiWidget *ui;
public:
#ifdef SUPPORT_TESS_OCR
#ifdef WINDOWS
    static constexpr const char* REQ_FILE = "TessereactWrapper.dll";
#else
    static constexpr const char* REQ_FILE = "libTessereactWrapper.so";
#endif
    QString                 record_dll_path;
    QString                 record_dll_dir;
    bool                    setDLLFile(const QString& dir);
    void                    bindOCR(TesseractOCRTextHelper* _helper){helper = _helper;}
    bool                    isBinding(){return helper;}

    void                    setManager(Plugin_OCRUiManager* m){manager = m;}
    void                    selectDLLFile();
    void                    doOCR();
    void                    setOCRDisable(bool able);
private slots:
    __BIND_Ui_Widgets   void on_btn_setPluginDLL_clicked(){selectDLLFile();}
    void on_start_OCR_clicked(){doOCR();}


private:
    __MEMEROY_NO_HOLD
        Plugin_OCRUiManager*    manager{nullptr};

    __MEMEROY_NO_HOLD       TesseractOCRTextHelper*     helper;
#endif
};

#endif // PLUGIN_OCR_UIWIDGET_H
