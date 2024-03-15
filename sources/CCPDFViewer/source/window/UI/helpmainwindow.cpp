#include "helpmainwindow.h"
#include "ui_helpmainwindow.h"
static const char* WINDOW_HELP = "帮助";

HelpMainWindow::HelpMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpMainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(WINDOW_HELP);
}

HelpMainWindow::~HelpMainWindow()
{
    delete ui;
}
