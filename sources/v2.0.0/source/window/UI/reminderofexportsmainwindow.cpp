#include <QMessageBox>
#include <QCloseEvent>

#include "reminderofexportsmainwindow.h"
#include "ui_reminderofexportsmainwindow.h"
#include "PDF_Utils.h"
const char* REMINDER_WINDOW_NAME = "保存进度";

double ReminderOfExportsMainWindow::calPercentage(int page)
{
    if(ui->savingProcessBar->maximum() - ui->savingProcessBar->minimum() == 0){
        return 100;
    }
    return 100.0 * (page - ui->savingProcessBar->minimum()) /
           (ui->savingProcessBar->maximum() - ui->savingProcessBar->minimum());
}

ReminderOfExportsMainWindow::ReminderOfExportsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReminderOfExportsMainWindow)
{
    ui->setupUi(this);
    setWindowTitle(REMINDER_WINDOW_NAME);
}

void ReminderOfExportsMainWindow::setPageTotal(int page)
{
    pgTotal = page;
    ui->savingProcessBar->setMaximum(page);
    ui->savingProcessBar->setMinimum(0);
}

QString ReminderOfExportsMainWindow::makeHandlingString(int page)
{
    switch(currentState)
    {
    case STATE::HANDLING_RENDER:
        return handlingRenderPrefixText + QString::number(page) + handlingSuffix;
    case STATE::HANDLING_EXPORT:
        return handlingExportPrefixText + QString::number(page) + handlingSuffix;
    }
    return "";
}


void ReminderOfExportsMainWindow::updateProcessing(int page)
{
    ui->savingProcessBar->setFormat(QString("%1%").arg(QString::number(calPercentage(page), 'f',1)));
    ui->savingProcessBar->setValue(page);
    ui->processLineEdit->setText(makeHandlingString(page));
}

void ReminderOfExportsMainWindow::finishAndShallClose()
{
    isAbleClose = true;
    ui->processLineEdit->setText("已完成所有的工作！");
    ui->savingProcessBar->setValue(ui->savingProcessBar->maximum());
    ui->savingProcessBar->setFormat(QString("%1%").arg(QString::number(100.0, 'f',1)));
}

void ReminderOfExportsMainWindow::switchToExport()
{
    currentState = STATE::HANDLING_EXPORT;
    updateProcessing(0);
}


void ReminderOfExportsMainWindow::closeEvent(QCloseEvent* e)
{
    if(!isAbleClose){
        if(PDF_Window_SavingConfig::generalAskForLeave(this, "是否撤销保存?"))
        {
            ui->processLineEdit->setText("正在取消...");
            ui->savingProcessBar->setValue(0);
            ui->savingProcessBar->setFormat("正在取消...");
            update();
            emit cancelTheSave();
            e->ignore();
        }
        else
        {
            e->ignore();
        }
        return;
    }
    e->accept();
}

void ReminderOfExportsMainWindow::handleTheCancel()
{
    ui->processLineEdit->setText("成功取消全部！");
    ui->savingProcessBar->setValue(0);
    ui->savingProcessBar->setFormat("全部取消");
    isAbleClose = true;
}


ReminderOfExportsMainWindow::~ReminderOfExportsMainWindow()
{
    delete ui;
}



