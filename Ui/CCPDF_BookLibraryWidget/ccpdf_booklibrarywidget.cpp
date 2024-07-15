#include "ccpdf_booklibrarywidget.h"
#include "CCPDF_BookLibraryManager/ccpdf_booklibrarymanager.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "ui_ccpdf_booklibrarywidget.h"

CCPDF_BookLibraryWidget::CCPDF_BookLibraryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCPDF_BookLibraryWidget)
{
    ui->setupUi(this);
    manager = std::make_unique<CCPDF_BookLibraryManager>(ui->booklibrary_treeView);
}

void CCPDF_BookLibraryWidget::setRootPath(const QString& Path)
{
    manager->setRootPath(Path);
}

void CCPDF_BookLibraryWidget::searchInRoot(const QString& fileName)
{
    manager->searchInRoot(fileName);
}

void CCPDF_BookLibraryWidget::on_btn_set_bookLibPath_clicked()
{
    QString dirPath = CCPDF_FileUtils::SelectFileUtils::selectExsitingDir(
        "选择书库目录", CCPDF_FileUtils::CommonPath::desktopPath(), this);
    if(dirPath.isEmpty())
        return;
    setRootPath(dirPath);
    emit tellShellRecord(dirPath);
}

void CCPDF_BookLibraryWidget::on_btn_book_lib_searching_search_clicked()
{
    QString fetchFromLineEdit = ui->book_lib_searching_lineEdit->text();
    searchInRoot(fetchFromLineEdit);
}

CCPDF_BookLibraryWidget::~CCPDF_BookLibraryWidget()
{
    delete ui;
}

void CCPDF_BookLibraryWidget::on_booklibrary_treeView_clicked(const QModelIndex &index)
{
    QString filePath = manager->filePath(index);
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(filePath))
        return;
    emit tellLoadWhat(filePath);
}

