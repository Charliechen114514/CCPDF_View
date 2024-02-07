#ifndef REMINDEROFEXPORTSMAINWINDOW_H
#define REMINDEROFEXPORTSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReminderOfExportsMainWindow;
}

class ReminderOfExportsMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReminderOfExportsMainWindow(QWidget *parent = nullptr);
    double calPercentage(int page);
    const   QString     handlingRenderPrefixText = "当前正在渲染: ";
    const   QString     handlingExportPrefixText = "当前正在导出: ";
    const   QString     handlingSuffix = " 页!";
    QString     makeHandlingString(int page);
    enum class STATE
    {
        HANDLING_RENDER,
        HANDLING_EXPORT
    };

    void        setPageTotal(int page);
    int         getPageTotal(){return pgTotal;}
    void        setState(STATE state);
    STATE       getState(){return currentState;}
    ~ReminderOfExportsMainWindow();

    void        closeEvent(QCloseEvent*);

signals:
    void        cancelTheSave();
public slots:
    void        updateProcessing(int value);
    void        switchToExport();
    void        finishAndShallClose();
    void        handleTheCancel();
private:
    int                             pgTotal = 0;
    STATE                           currentState = STATE::HANDLING_RENDER;
    bool                            isAbleClose = false;
    Ui::ReminderOfExportsMainWindow *ui;
};

#endif // REMINDEROFEXPORTSMAINWINDOW_H
