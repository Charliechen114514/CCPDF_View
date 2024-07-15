#include "ccpdf_booklirabry_filesystemmodel.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"

CCPDF_BookLirabry_FileSystemModel::CCPDF_BookLirabry_FileSystemModel(QObject *parent)
    : QFileSystemModel{parent}
{}

QVariant CCPDF_BookLirabry_FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        if( role == Qt::DecorationRole ) //DecorationRole
        {
            QFileInfo info = CCPDF_BookLirabry_FileSystemModel::fileInfo(index);
            if(info.isFile() && CCPDF_FileUtils::Prefix_Precheck::isPDFFile(filePath(index)))
            {
                return pdf_icon;
            }
        }
    }
    return QFileSystemModel::data(index, role);
}
