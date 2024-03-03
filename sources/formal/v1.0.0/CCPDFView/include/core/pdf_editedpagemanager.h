#ifndef PDF_EDITEDPAGEMANAGER_H
#define PDF_EDITEDPAGEMANAGER_H
#include <QStringList>
#include <QPixmap>
#include "PDF_PathSettings.h"
#include <QMap>
#include <QObject>
class PDF_EditedPageManager : public QObject
{
    Q_OBJECT
public:
    PDF_EditedPageManager() = delete;
    PDF_EditedPageManager(QString belongingPDF, QObject* parent);
    PDF_EditedPageManager(const PDF_EditedPageManager&) = delete;
    virtual ~PDF_EditedPageManager();
    const PDF_EditedPageManager& operator=(const PDF_EditedPageManager&) = delete;
    bool                    isThisPageEdited(int pg);
    void                    insertTheEditPage(int pg, QPixmap& map);
    QString                 getPathAccordingtoThePageIndex(int index);
    void                    setEditingDirPath(QString path){dirSave = path;}
    QString                 getEditingDirPath(){return dirSave;}
    void                    popTheLastEditing(int pg);
    void                    clearAllEditing();
signals:
    void                    canFetchTheEdited(int pg);
private:
    // At first we consider no save happen
    QMap<int, QString>      editedPageholder;
    QString                 dirSave = EDIT_PDF_SAVING_PATH_DIR;
    QString                 belongingPDF;
    void                    clearThePathingFile(QString path);
    void                    clearAllEditedFiles();
    void                    makeTmpPDF(QString saverName, QPixmap& map);
};

#endif // PDF_EDITEDPAGEMANAGER_H
