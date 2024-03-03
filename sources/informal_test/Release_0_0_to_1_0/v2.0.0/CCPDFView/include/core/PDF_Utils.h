#ifndef PDF_UTILS_H
#define PDF_UTILS_H
#include "qfilesystemmodel.h"
#include "qpagesize.h"
class QWidget;
#include <QStringList>
#include <QMessageBox>
#define QString2CChar(X)            (X).toStdString().c_str()
#define ERROR_LOADING(ERR_MSG)

class PDF_Window_SavingConfig
{
public:
    void        setShellQueryingSave();
    void        unsetShellQueryingSave();
    bool        checkIfNeedQueryingSave();
    bool        queryingForSave(QWidget *w);
    bool        queryingForSaveDef(QWidget* w, QString text);
    static bool generalAskForLeave(QWidget* w, QString text);
    static QMessageBox::StandardButton alterQuestions(QWidget* w, QString text);
private:
    bool        isSave      =   true;
};


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
    static QString      addPDFSuffix(QString& path);
};

class PDF_NoteCreator
{
public:
    static bool         createFile(QString path);
};

class PDF_Saver
{
public:
    static QString      saverNameProducer(QString dirPath, QString pdfName, QString suffix);
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


class PDF_ExportWriterConfig
{
public:
    const int PDF_A4_Width  = QPageSize::size(QPageSize::A4, QPageSize::Point).toSize().width();
    const int PDF_A4_Height = QPageSize::size(QPageSize::A4, QPageSize::Point).toSize().height();
    const double PDF_A4Ratio = PDF_A4_Height / PDF_A4_Width;
    const QSize PDF_Size = QSizeF(PDF_A4_Width*4 + 100, PDF_A4_Height*4 + 100*PDF_A4Ratio).toSize();
    QPixmap getA4Printable(QPixmap &p);
    QImage  getA4PrintableImage(QImage& p);
};

class PDF_WriteTmpPDF
{
public:
    static bool writeTmpPDF(QPixmap&map, QString writingWhere);
};


class PDF_RemoveFile
{
public:
    static bool removeFile(QString path);
    static bool removeDir(QString dirPath);
};


#endif // PDF_UTILS_H
