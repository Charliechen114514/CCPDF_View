#ifndef REMINDERPROCESSWINDOW_H
#define REMINDERPROCESSWINDOW_H

#include <QWidget>
#include <QTimer>
class QProgressBar;
class QTextEdit;

namespace Ui {
class ReminderProcessWindow;
}

class ReminderProcessWindow : public QWidget
{
    Q_OBJECT

public:
    const char* SAVE_WINDOW_NAME = "保存进度";
    const   QString     handlingRenderPrefixText = "当前正在渲染: ";
    const   QString     handlingExportPrefixText = "当前正在导出: ";
    const   QString     handlingSuffix = " 页!";
    const   int         switchSentenceInterval = 5 * 1000;
    QString     makeHandlingString(int page, bool isRender);
    void        handleProcessBar(QProgressBar* bar,QTextEdit* e, int pg, bool isRender);
    double      getProcessPercentage(QProgressBar* bar,const int index);
    explicit    ReminderProcessWindow(int pgCt, QWidget *parent = nullptr);

    void        refresh_sentence(int index);
    ~ReminderProcessWindow();
signals:
    void cancelTheSave();
public slots:
    void required_update_export(int index);
    void required_update_render(int index);
    void required_update_as_renderFinish();
    void receive_cancel();
    void receive_finish();
    void selectSentence();
    void closeEvent(QCloseEvent* e);

private:
    Ui::ReminderProcessWindow *ui;
    void        configBars();
    void        initSentencePool();
    void        initBrowser();
    void        initConnections();
    void        cancel_progressSetUi(QProgressBar* bar,QTextEdit* e);
    void        cancel_SuccessSetUi();
    QStringList sentencePool;
    int         pgCnt;
    bool        isAbleClose;
    QTimer      timer;
};

#endif // REMINDERPROCESSWINDOW_H
