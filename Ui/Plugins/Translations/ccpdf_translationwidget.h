#ifndef CCPDF_TRANSLATIONWIDGET_H
#define CCPDF_TRANSLATIONWIDGET_H
#include <CCPDF_Global.h>

#ifdef SUPPORT_TRANSLATION
#include "External_Option_Compile/CCPDF_ExternTranslations/Translate/ccpdf_externtranslation.h"
#endif
#include <QWidget>

namespace Ui {
class CCPDF_TranslationWidget;
}
class Plugin_HistoricalHelper;
class CCPDF_TranslationWidget : public QWidget
{
    Q_OBJECT

public:

    explicit    CCPDF_TranslationWidget(QWidget *parent = nullptr);
    ~CCPDF_TranslationWidget();
private:
    Ui::CCPDF_TranslationWidget *ui;

public:
#ifdef SUPPORT_TRANSLATION
    static constexpr const char* INPUT = "reading.plugin.input";
    void        setTrans(CCPDF_ExternTranslation* _translation);
    void        setHolder(Plugin_HistoricalHelper* w){histroyHolder = w;}

    void        setEXE();
    void        setInputEdit(const QString& what);
    void        setEXE(const QString& res);
    void        setOutPut();
    void        setOutPut(const QString& res);
    void        makeRun();
    bool        tryCheck();
    void        handleRes();

private slots:
    __BIND_Ui_Widgets   void on_btn_set_exe_clicked(){setEXE();}
    __BIND_Ui_Widgets   void on_btn_set_output_read_clicked(){setOutPut();}
    __BIND_Ui_Widgets   void on_btn_depatch_clicked(){makeRun();}
private:
    void                setInput();
    bool                checkRunnable();
    void                registerOrUpdate();
    QString             exe;
    QString             outPut;

    __MEMEROY_NO_HOLD
    Plugin_HistoricalHelper*                        histroyHolder;
    __MEMEROY_NO_HOLD   CCPDF_ExternTranslation*    translations;
#endif
};

#endif // CCPDF_TRANSLATIONWIDGET_H
