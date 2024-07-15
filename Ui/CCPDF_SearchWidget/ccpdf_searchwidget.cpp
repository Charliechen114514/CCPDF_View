#include <QPdfSearchModel>
#include "ccpdf_searchwidget.h"
#include "ui_ccpdf_searchwidget.h"

CCPDF_SearchWidget::CCPDF_SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCPDF_SearchWidget)
{
    ui->setupUi(this);
    connect(ui->search_edit, &QLineEdit::returnPressed, this, &CCPDF_SearchWidget::handleTellString);
    connect(ui->btn_startSearch, &QPushButton::clicked, this, &CCPDF_SearchWidget::handleTellString);
}

void CCPDF_SearchWidget::handleTellString()
{
    emit tellString(ui->search_edit->text());
}

void CCPDF_SearchWidget::handleSearch(const QModelIndex& current, const QModelIndex& prev[[maybe_unused]])
{
    if (!current.isValid())
        return;
    const int page = current.data(int(QPdfSearchModel::Role::Page)).toInt();
    const QPointF location = current.data(int(QPdfSearchModel::Role::Location)).toPointF();
    emit tellPageNavigate(page, location, current);
}

void CCPDF_SearchWidget::setModel(QPdfSearchModel* view)
{
    ui->search_listView->setModel(view);
    connect(ui->search_listView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &CCPDF_SearchWidget::handleSearch);
}

CCPDF_SearchWidget::~CCPDF_SearchWidget()
{
    delete ui;
}
