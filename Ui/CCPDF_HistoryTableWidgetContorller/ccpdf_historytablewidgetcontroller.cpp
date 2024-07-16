#include <QMenu>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "ccpdf_historytablewidgetcontroller.h"

static inline QString composePageIndex(const PDF_Info_Historical_Record& record){
    return QString::number(record.current_page + 1);
}

static inline QStringList generateHeaders()
{
    QStringList headers;
    for(const auto& each : CONTROL_UI_INFO::TITLES)
    {
        headers << each;
    }
    return headers;
}

static inline QString composeFileName(const PDF_Info_Historical_Record& record){
    return CCPDF_FileUtils::PDF_Info::fetchNameAccordPath(record.pdf_Path);;
}


static inline void configItem(QTableWidgetItem* item, bool is_selectable)
{
    item->setToolTip(item->text());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    if(!is_selectable)
    {
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    }
}

static inline void doUpdate(QTableWidget* item,int row ,const PDF_Info_Historical_Record& record)
{
    auto page_one = item->item(row, CONTROL_UI_INFO::PAGE_INDEX);
    if(!page_one)
        return;
    page_one->setText(composePageIndex(record));
}


static inline void helpCompose(QTableWidget* operatingWidget,
                               const PDF_Info_Historical_Record& each_record,
                               int current_operating_index)
{
    auto ItW_Path = new QTableWidgetItem(each_record.pdf_Path);
    auto Itw_Name = new QTableWidgetItem(composeFileName(each_record));
    auto Itw_Page = new QTableWidgetItem(composePageIndex(each_record));
    operatingWidget->setItem(current_operating_index, CONTROL_UI_INFO::PATH_INDEX, ItW_Path);
    operatingWidget->setItem(current_operating_index, CONTROL_UI_INFO::FILE_NAME_INDEX, Itw_Name);
    operatingWidget->setItem(current_operating_index, CONTROL_UI_INFO::PAGE_INDEX, Itw_Page);
    configItem(ItW_Path, true);
    configItem(Itw_Name, false);
    configItem(Itw_Page, false);
}


CCPDF_HistoryTableWidgetController::CCPDF_HistoryTableWidgetController(
    QTableWidget* w, QObject *parent):QObject(parent)
{
    w->setContextMenuPolicy(Qt::CustomContextMenu);
    operatingWidget = w;
    operatingWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    operatingWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    operatingWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    operatingWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    operatingWidget->setColumnCount(CONTROL_UI_INFO::DEFAULT_COL);
    operatingWidget->setHorizontalHeaderLabels(generateHeaders());
    initMenu();
}

void CCPDF_HistoryTableWidgetController::initMenu()
{
    operatingWidgetMenu = new QMenu(operatingWidget);
    auto act = new QAction("删除选中的历史记录", operatingWidget);
    operatingWidgetMenu->addAction(act);
    connect(act, &QAction::triggered, this,
            &CCPDF_HistoryTableWidgetController::handleRemoveSelected);
}

void CCPDF_HistoryTableWidgetController::setBindHistLists(
    const QList<PDF_Info_Historical_Record>& infos)
{
    operatingWidget->clearContents();
    operatingWidget->setRowCount(infos.size());
    int current_operating_index = 0;
    for(const auto& each_record : infos)
    {
        helpCompose(operatingWidget, each_record, current_operating_index);
        current_operating_index++;
    }
}

void CCPDF_HistoryTableWidgetController::handleRemoveSelected()
{
    auto get = operatingWidget->itemAt(exePoint);
    if(!get)
        return;
    QTableWidgetItem* item = operatingWidget->item(get->row(), CONTROL_UI_INFO::PATH_INDEX);
    operatingWidget->removeRow(item->row());
    emit emitTellRemovePdfPath(item->text());
}

void CCPDF_HistoryTableWidgetController::removeFromOutward(const QString& path)
{
    short tol_cnt = operatingWidget->rowCount();
    for(short i = 0; i < tol_cnt; i++)
    {
        const auto wid = operatingWidget->item(i, CONTROL_UI_INFO::PATH_INDEX);
        if(wid && wid->text() == path)
        {
            operatingWidget->removeRow(i);
        }
    }
}

void CCPDF_HistoryTableWidgetController::addToMenu(const PDF_Info_Historical_Record& g)
{
    short ins = operatingWidget->rowCount();
    operatingWidget->setRowCount(ins + 1);
    helpCompose(operatingWidget, g, ins);
}

void CCPDF_HistoryTableWidgetController::update_ui(PDF_Info_Historical_Record g)
{
    QString pdf_Path = g.pdf_Path;
    short tol_cnt = operatingWidget->rowCount();
    for(short i = 0; i < tol_cnt; i++)
    {
        const auto wid = operatingWidget->item(i, CONTROL_UI_INFO::PATH_INDEX);
        if(wid->text() == pdf_Path)
        {
            doUpdate(operatingWidget, i, g);
        }
    }
}

void CCPDF_HistoryTableWidgetController::setExecutionPoint(const QPoint& ff)
{
    exePoint = operatingWidget->viewport()->mapFromParent(ff);
}

bool CCPDF_HistoryTableWidgetController::setFocusingForMenu(QPoint where)
{
    auto res = operatingWidget->itemAt(where);
    if(!res)
        return false;
    operatingWidget->setCurrentItem(res);
    return false;
}


void CCPDF_HistoryTableWidgetController::doItemClick(QTableWidgetItem* w)
{
    QTableWidgetItem* item = operatingWidget->item(w->row(), CONTROL_UI_INFO::PATH_INDEX);
    emit emitTellLoadPdf(item->text());
}

void CCPDF_HistoryTableWidgetController::doMenuShowUp()
{
    operatingWidgetMenu->exec(QCursor::pos());
}
