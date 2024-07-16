#include "ccpdf_bookmarkmodel.h"

CCPDF_BookMarkModel::CCPDF_BookMarkModel(QObject *parent)
    : QPdfBookmarkModel{parent}
{}


QVariant CCPDF_BookMarkModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return myHeaders.at(section);
    }
    return {};
}


QVariant CCPDF_BookMarkModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        if(role == Qt::DisplayRole)
        {
            int atCol = index.column();
            switch(atCol)
            {
            case BookModelConfig::PAGE_INDEX:
                return index.data(int(QPdfBookmarkModel::Role::Page)).toInt();break;
            }
        }
    }
    return QPdfBookmarkModel::data(index, role);
}
