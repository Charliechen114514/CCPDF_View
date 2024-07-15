#include <QTreeView>
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "ccpdf_booklibrarymanager.h"
#include "CCPDF_BookLibraryManager/FileSystemModel/ccpdf_booklirabry_filesystemmodel.h"

CCPDF_BookLibraryManager::CCPDF_BookLibraryManager(QTreeView *view)
{
    operating_view = view;
    fileSystemModel = new CCPDF_BookLirabry_FileSystemModel(operating_view);
}

void CCPDF_BookLibraryManager::setRootPath(const QString& path)
{
    fileSystemModel->setRootPath(path);
    auto rootModelIndex = fileSystemModel->index(path);
    fileSystemModel->setNameFilters(CCPDF_FileUtils::PDF_Info::nameFilters());
    fileSystemModel->setNameFilterDisables(false);
    fileSystemModel->setReadOnly(true);
    operating_view->setModel(fileSystemModel);
    operating_view->setRootIndex(rootModelIndex);
    operating_view->setHeaderHidden(true);
}

void CCPDF_BookLibraryManager::searchInRoot(const QString& fileName)
{
    if(fileName.isEmpty())
    {
        fileSystemModel->setNameFilters(CCPDF_FileUtils::PDF_Info::nameFilters());
        return;
    }
    fileSystemModel->setNameFilters(CCPDF_FileUtils::PDF_Info::nameFilters(fileName));
}

QString CCPDF_BookLibraryManager::filePath(const QModelIndex& m)
{
    return fileSystemModel->filePath(m);
}

