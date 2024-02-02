#ifndef PDF_UTILS_H
#define PDF_UTILS_H
#include "qfilesystemmodel.h"
class QWidget;
#include <QStringList>
#define QString2CChar(X)            (X).toStdString().c_str()
#define ERROR_LOADING(ERR_MSG)

class PDFWindowDataUtils_ReadWriteFile
{
public:
    static QString      getDataFromFile(QString file, bool& state);
    static QStringList  getDatasFromFile(QString file, bool& state);
    static QList<int>   getIndexFromFile(QString file, bool& state);
    static bool         writeDataToFile(QString file, QString what);
    static bool         writeDatasToFile(QString file, QStringList what);
    static bool         writeIndexs(QString file, QList<int> what);
    static void         clearFiles(QString file);
};

class PDF_LocationDefaults
{
public:
    static bool         getPathDir(QString& path, QWidget* parent);
    static bool         getOpenFileName(QString& path, QWidget* parent);
    static bool         getOpenFileNameSelfDef(QString& path, QWidget* w, QString title, QString text, QString suffix);
    static bool         getSavingFileName(QString& path, QWidget* parent);
    static QString      getDesktopLocation();
    static QString      getFileNameByPath(QString path);
    static QString      getDirNameByPath(QString path);
    static bool         isFileExsits(QString path);
    static bool         isADir(QString dir);
    static QString      getSuffixOfFile(QString file);
};

class PDF_NoteCreator
{
public:
    static bool         createFile(QString path);
};

class PDF_ImageSaver
{
public:
    static QString      imageSaverNameProducer(QString dirPath, QString pdfName);
    static bool         saveImage(QImage image, QString path);
};


class PDF_FileSystemModel: public QFileSystemModel
{
public:
    explicit            PDF_FileSystemModel(QObject *parent = nullptr):QFileSystemModel(parent){}
    ~PDF_FileSystemModel(){};
private:
    const short         DEFAULT_COLUMN_SHOW = 1;
    int                 columnCount(const QModelIndex &parent[[maybe_unused]]) const{return DEFAULT_COLUMN_SHOW;}
    QVariant            data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

class PDF_GetDir
{
public:
    static QString      getDir(QWidget* parent, QString title, QString text);
};

#endif // PDF_UTILS_H
