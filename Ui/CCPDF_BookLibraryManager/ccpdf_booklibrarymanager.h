#ifndef CCPDF_BOOKLIBRARYMANAGER_H
#define CCPDF_BOOKLIBRARYMANAGER_H
#include <QAbstractItemModel>
#include "CCPDF_Global.h"

class QTreeView;
class CCPDF_BookLirabry_FileSystemModel;


class CCPDF_BookLibraryManager
{
public:
    explicit    CCPDF_BookLibraryManager(QTreeView* view);
    DISABLE_COPY(CCPDF_BookLibraryManager);
    void        setRootPath(const QString& Path);
    void        searchInRoot(const QString& fileName);
    QString     filePath(const QModelIndex& m);
private:
    __MEMEROY_HOLD_BY_OBJ_TREE
    CCPDF_BookLirabry_FileSystemModel*  fileSystemModel;
    __MEMEROY_NO_HOLD   QTreeView*      operating_view;
};

#endif // CCPDF_BOOKLIBRARYMANAGER_H
