#include "ccpdf_bookmarkwidget.h"
#include <QPdfBookmarkModel>
#include "ui_ccpdf_bookmarkwidget.h"

CCPDF_BookMarkWidget::CCPDF_BookMarkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCPDF_BookMarkWidget)
{
    ui->setupUi(this);
}

void CCPDF_BookMarkWidget::setModel(QPdfBookmarkModel* m)
{
    ui->bookmodel_treeView->setModel(m);
}

CCPDF_BookMarkWidget::~CCPDF_BookMarkWidget()
{
    delete ui;
}

void CCPDF_BookMarkWidget::on_bookmodel_treeView_activated(const QModelIndex &index)
{
    const int page = index.data(int(QPdfBookmarkModel::Role::Page)).toInt();
    const qreal zoomLevel = index.data(int(QPdfBookmarkModel::Role::Level)).toReal();
    emit navigateTo(page, zoomLevel);
}

