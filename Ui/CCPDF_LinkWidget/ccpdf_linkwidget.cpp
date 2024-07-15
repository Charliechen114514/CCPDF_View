#include <QPdfLinkModel>
#include <QUrl>
#include <QDesktopServices>
#include "ccpdf_linkwidget.h"
#include "ui_ccpdf_linkwidget.h"

CCPDF_LinkWidget::CCPDF_LinkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCPDF_LinkWidget)
{
    ui->setupUi(this);
    connect(ui->linkListView, &QAbstractItemView::pressed,
            this, &CCPDF_LinkWidget::handleLink);
}

void CCPDF_LinkWidget::setModel(QPdfLinkModel* model)
{
    ui->linkListView->setModel(model);
}

void CCPDF_LinkWidget::handleLink(const QModelIndex &current)
{
    qDebug() << "III";
    if (!current.isValid())
        return;
    const int possiblePage = current.data(int(QPdfLinkModel::Role::Page)).toInt();
    if(possiblePage != -1)
        emit navigateTo(possiblePage);
    QUrl url = current.data(int(QPdfLinkModel::Role::Url)).toUrl();
    if(url.isValid())
        QDesktopServices::openUrl(url);
}


CCPDF_LinkWidget::~CCPDF_LinkWidget()
{
    delete ui;
}


