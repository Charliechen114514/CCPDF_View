#include "pdf_fileviewmanager.h"
#include "PDF_Utils.h"
#include <QHeaderView>

PDF_FileViewManager::PDF_FileViewManager(QTableWidget* w):operatingWidget(w){
    if(!this->operatingWidget)
        return;
    this->operatingWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->operatingWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->operatingWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->operatingWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->operatingWidget->setColumnCount(DefaultRowCount);
}

void PDF_FileViewManager::configFiles(QStringList l)
{
    for(auto each : l)
        addPath(each);
    configTableWidget();
}

void PDF_FileViewManager::configWidget(QTableWidgetItem* i)
{
    i->setToolTip(i->text());
    i->setFlags(i->flags() & ~Qt::ItemIsEditable);
}

bool PDF_FileViewManager::isFileExists(QString l)
{
    for(auto each : this->filePathItems.keys()){
        if(l == each->text())
            return true;
    }
    return false;
}
void PDF_FileViewManager::addPath(QString l)
{
    if(l.isEmpty() || isFileExists(l))
        return;
    FilePathWidget* dirW = new QTableWidgetItem(l);
    FileNameWidget* nameW = new QTableWidgetItem(PDF_LocationDefaults::getFileNameByPath(l));
    configWidget(dirW);
    configWidget(nameW);
    nameW->setFlags(nameW->flags() & !Qt::ItemIsSelectable);
    this->filePathItems.insert(dirW,nameW);
}

void PDF_FileViewManager::configTableWidget()
{
    if(!this->operatingWidget)
        return;
    clearWidget();
    this->operatingWidget->setRowCount(this->filePathItems.size());
    auto it = this->filePathItems.constBegin();
    int curOperateRow = 0;
    while(it != this->filePathItems.constEnd())
    {
        this->operatingWidget->setItem(curOperateRow, 0, it.value());
        this->operatingWidget->setItem(curOperateRow, 1, it.key());
        curOperateRow++;
        ++it;
    }
    // update the operatingWidget immediately
    this->operatingWidget->update();
}

void PDF_FileViewManager::removeTarget(QString l)
{
    auto it = this->filePathItems.begin();
    QString dir = PDF_LocationDefaults::getDirNameByPath(l);
    while(it != this->filePathItems.end())
    {
        auto cur = it;
        it++;
        if(cur.key()->text() == dir)
        {
            delete cur.key();
            delete cur.value();
            filePathItems.remove(cur.key());
        }
    }
    configTableWidget();
}

void PDF_FileViewManager::removeTarget(FilePathWidget* w)
{
    auto it = this->filePathItems.begin();
    while(it != this->filePathItems.end())
    {
        auto cur = it;
        it++;
        if(cur.key() == w)
        {
            delete cur.key();
            delete cur.value();
            filePathItems.remove(cur.key());
        }
    }
    configTableWidget();
}

void PDF_FileViewManager::clearWidget()
{
    if(!this->operatingWidget)
        return;
    for(int i = 0; i < this->operatingWidget->rowCount(); i++)
        for(int j = 0; j < this->operatingWidget->columnCount(); j++)
            this->operatingWidget->takeItem(i, j);
}

void PDF_FileViewManager::clearMap()
{
    auto it = this->filePathItems.begin();
    while(it != this->filePathItems.end())
    {
        auto cur = it;
        it++;
        delete cur.key();
        delete cur.value();
    }
}


PDF_FileViewManager::~PDF_FileViewManager()
{
    clearMap();
}
