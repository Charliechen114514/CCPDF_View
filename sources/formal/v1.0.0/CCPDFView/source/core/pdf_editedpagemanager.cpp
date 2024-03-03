#include "pdf_editedpagemanager.h"
#include "PDF_Utils.h"
PDF_EditedPageManager::PDF_EditedPageManager(QString belongingPDF, QObject *parent):QObject(parent)
{
    this->belongingPDF = belongingPDF;
}

PDF_EditedPageManager::~PDF_EditedPageManager()
{
    clearAllEditedFiles();
}

bool PDF_EditedPageManager::isThisPageEdited(int pg)
{
    return this->editedPageholder.keys().contains(pg);
}

void PDF_EditedPageManager::insertTheEditPage(int pg, QPixmap& map)
{
    // 对于在编辑者:
    if(isThisPageEdited(pg))
    {
        QString previous = editedPageholder.value(pg);
        if(!previous.isEmpty())
            clearThePathingFile(previous);
    }
    QString saverName = PDF_Saver::saverNameProducer(dirSave, belongingPDF, ".tmppdf");
    this->editedPageholder.insert(pg, saverName);
    makeTmpPDF(saverName, map);
    emit canFetchTheEdited(pg);
}


void PDF_EditedPageManager::clearThePathingFile(QString path)
{
    PDF_RemoveFile::removeFile(path);
}

void PDF_EditedPageManager::clearAllEditing()
{
    editedPageholder.clear();
    clearAllEditedFiles();
}

void PDF_EditedPageManager::clearAllEditedFiles()
{
    PDF_RemoveFile::removeDir(dirSave);
}

void PDF_EditedPageManager::popTheLastEditing(int pg)
{
    if(isThisPageEdited(pg))
    {
        QString previous = editedPageholder.value(pg);
        clearThePathingFile(previous);
        editedPageholder.remove(pg);
    }
}

void PDF_EditedPageManager::makeTmpPDF(QString saverName, QPixmap& map)
{
    PDF_WriteTmpPDF::writeTmpPDF(map, saverName);
}

QString PDF_EditedPageManager::getPathAccordingtoThePageIndex(int index)
{
    return this->editedPageholder.value(index);
}





