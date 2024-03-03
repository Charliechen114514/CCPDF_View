#include <QProgressBar>
#include <QRandomGenerator>
#include <QCloseEvent>
#include "PDF_PathSettings.h"
#include "PDF_Utils.h"
#include "reminderprocesswindow.h"
#include "ui_reminderprocesswindow.h"


ReminderProcessWindow::ReminderProcessWindow(int pgCt, QWidget *parent) :
    QWidget(parent),ui(new Ui::ReminderProcessWindow),
    pgCnt(pgCt)
{
    ui->setupUi(this);
    setWindowTitle(SAVE_WINDOW_NAME);
    configBars();
    initSentencePool();
    initBrowser();
    initConnections();
}

double ReminderProcessWindow::getProcessPercentage(QProgressBar* bar,const int index)
{
    if(bar->maximum() - bar->minimum() == 0){
        return 100;
    }
    return 100.0 * (index - bar->minimum()) /
           (bar->maximum() - bar->minimum());
}

void ReminderProcessWindow::configBars()
{
    ui->exportProgressBar->setMaximum(pgCnt);
    ui->renderProgressBar->setMaximum(pgCnt);
    ui->renderProgressBar->setMinimum(0);
    ui->exportProgressBar->setMinimum(0);
    ui->renderProgressBar->setValue(0);
    ui->exportProgressBar->setValue(0);
}

void ReminderProcessWindow::initSentencePool()
{
    bool state = false;
    sentencePool = PDFWindowDataUtils_ReadWriteFile::getDatasFromFile(SENTENCE_POOL_PATH, state);
    if(!state)
    {
        sentencePool << "啊哈，貌似没法显示彩蛋，你就看这句话等吧" << "反转了，还有另一句话";
    }
}

void ReminderProcessWindow::selectSentence()
{
    refresh_sentence(QRandomGenerator::global()->generate() % sentencePool.size());
}

void ReminderProcessWindow::refresh_sentence(int index)
{
    if(index < 0 || index >= sentencePool.size())
        return;
    ui->sthFunShow->setText(sentencePool.at(index));
    ui->sthFunShow->setAlignment(Qt::AlignCenter);
}

void ReminderProcessWindow::initBrowser()
{
    timer.setInterval(switchSentenceInterval);
    timer.start();
    selectSentence();
}

void ReminderProcessWindow::initConnections()
{
    connect(&this->timer, &QTimer::timeout,
            this, &ReminderProcessWindow::selectSentence);
}

QString ReminderProcessWindow::makeHandlingString(int page, bool isRender)
{
    return
        (isRender?handlingRenderPrefixText:handlingExportPrefixText) +
        QString::number(page) + handlingSuffix;
}

void ReminderProcessWindow::handleProcessBar(QProgressBar* bar,QTextEdit* e, int page,bool isRender)
{
    bar->setFormat(QString("%1%").arg(QString::number(getProcessPercentage(bar, page), 'f',1)));
    bar->setValue(page);
    e->setText(makeHandlingString(page, isRender));
}

void ReminderProcessWindow::required_update_export(int index)
{
    handleProcessBar(ui->exportProgressBar, ui->exportProcessTextEdit, index, false);
}

void ReminderProcessWindow::required_update_render(int index)
{
    handleProcessBar(ui->renderProgressBar, ui->renderProcessTextEdit, index, true);
}

void ReminderProcessWindow::required_update_as_renderFinish()
{
    ui->renderProcessTextEdit->setText("已完成渲染的工作！");
    ui->renderProgressBar->setValue(ui->exportProgressBar->maximum());
    ui->renderProgressBar->setFormat(QString("%1%").arg(QString::number(100.0, 'f',1)));
}

void ReminderProcessWindow::cancel_progressSetUi(QProgressBar* bar,QTextEdit* e)
{
    e->setText("正在取消...");
    bar->setValue(0);
    bar->setFormat("正在取消...");
}


void ReminderProcessWindow::ReminderProcessWindow::receive_cancel()
{
    cancel_SuccessSetUi();
    isAbleClose = true;
}

void ReminderProcessWindow::ReminderProcessWindow::receive_finish()
{
    isAbleClose = true;
    ui->exportProcessTextEdit->setText("已完成所有的工作！");
    ui->exportProgressBar->setValue(ui->exportProgressBar->maximum());
    ui->exportProgressBar->setFormat(QString("%1%").arg(QString::number(100.0, 'f',1)));
    ui->renderProcessTextEdit->setText("已完成所有的工作！");
    ui->renderProgressBar->setValue(ui->exportProgressBar->maximum());
    ui->renderProgressBar->setFormat(QString("%1%").arg(QString::number(100.0, 'f',1)));
}

void ReminderProcessWindow::closeEvent(QCloseEvent* e)
{
    if(!isAbleClose){
        if(PDF_Window_SavingConfig::generalAskForLeave(this, "是否撤销保存?"))
        {
            cancel_progressSetUi(ui->exportProgressBar, ui->exportProcessTextEdit);
            cancel_progressSetUi(ui->renderProgressBar, ui->renderProcessTextEdit);
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

void ReminderProcessWindow::cancel_SuccessSetUi()
{
    ui->exportProgressBar->setFormat("全部取消");
    ui->exportProcessTextEdit->setText("成功取消全部！");
    ui->renderProgressBar->setFormat("全部取消");
    ui->renderProcessTextEdit->setText("成功取消全部！");
}

ReminderProcessWindow::~ReminderProcessWindow()
{
    timer.stop();
    delete ui;
}
