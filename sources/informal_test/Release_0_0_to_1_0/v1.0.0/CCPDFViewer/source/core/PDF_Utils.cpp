#include "PDF_Utils.h"
#include "qdir.h"
#include "qfiledialog.h"
#include "qfileinfo.h"
#include <QFile>
#include <QStandardPaths>
QString PDFWindowDataUtils_ReadWriteFile::getDataFromFile(QString file, bool& state)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
    {
        state = false;
        return "";
    }
    state = true;
    QString buf = f.readAll();
    f.close();
    return buf;
}

QStringList PDFWindowDataUtils_ReadWriteFile::getDatasFromFile(QString file, bool& state)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
    {
        state = false;
        return QStringList();
    }
    QStringList l;
    while(!f.atEnd())
    {
        QString tmp = QString(f.readLine()).removeLast();
        if(!l.contains(tmp)) // remove possible duplicated files
            l << tmp;
    }
    f.close();
    state = true;
    return l;
}

QList<int> PDFWindowDataUtils_ReadWriteFile::getIndexFromFile(QString file, bool& state)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
    {
        state = false;
        return QList<int>();
    }
    QStringList get;
    QList<int> l;
    while(!f.atEnd())
    {
        bool isSuccess = false;
        short index = QString(f.readLine()).remove("\n").toInt(&isSuccess);
        if(isSuccess)
            l << index;
        else
            l << 0;
    }
    f.close();
    state = true;
    return l;
}

bool PDFWindowDataUtils_ReadWriteFile::writeDataToFile(QString file, QString what)
{
    QFile f(file);
    f.open(QIODevice::WriteOnly);
    if(!f.isOpen())
    {
        return false;
    }
    f.write(QString2CChar(what + "\n"));
    f.close();
    return true;
}

bool PDFWindowDataUtils_ReadWriteFile::writeDatasToFile(QString file, QStringList what)
{
    QFile f(file);
    f.open(QIODevice::WriteOnly);
    if(!f.isOpen())
    {
        return false;
    }
    for(const QString& each : what)
    {
        f.write(QString2CChar(each + "\n"));
    }
    f.close();
    return true;
}

bool PDFWindowDataUtils_ReadWriteFile::writeIndexs(QString file, QList<int> what)
{
    QFile f(file);
    f.open(QIODevice::WriteOnly);
    if(!f.isOpen())
    {
        return false;
    }
    for(const int& each : what)
    {
        f.write(QString2CChar(QString::number(each) + "\n"));
    }
    f.close();
    return true;
}


void PDFWindowDataUtils_ReadWriteFile::clearFiles(QString file)
{
    QFile f(file);
    f.open(QFile::WriteOnly|QFile::Truncate);
    if(!f.isOpen())
        return;
    f.close();
}

bool PDF_LocationDefaults::getOpenFileName(QString& path, QWidget* parent)
{
    path = QFileDialog::getOpenFileName(parent, "选择一个处理文件","选择文件");
    if(path.isEmpty())
        return false;
    return true;
}

bool PDF_LocationDefaults::getOpenFileNameSelfDef(QString& path, QWidget* w, QString title, QString text, QString suffix)
{
    path = QFileDialog::getOpenFileName(w, title,text,suffix);
    if(path.isEmpty())
        return false;
    return true;
}
bool PDF_LocationDefaults::getSavingFileName(QString& path, QWidget* parent)
{
    path = QFileDialog::getSaveFileName(parent, "创建文件","选择文件");
    if(path.isEmpty())
        return false;
    return true;
}


bool PDF_LocationDefaults::getPathDir(QString& path, QWidget* w)
{
    path = QFileDialog::getExistingDirectory(w, "选择目录","选择你的目录");
    if(path.isEmpty())
        return false;
    return true;
}


QString PDF_LocationDefaults::getDesktopLocation()
{
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

QString PDF_LocationDefaults::getFileNameByPath(QString path)
{
    return QFileInfo(path).fileName();
}

QString PDF_LocationDefaults::getDirNameByPath(QString path)
{
    return QFileInfo(path).absoluteDir().absolutePath();
}

bool PDF_LocationDefaults::isFileExsits(QString path)
{
    return QFile::exists(path);
}

bool PDF_LocationDefaults::isADir(QString dir)
{
    return QFileInfo(dir).isDir();
}

QString PDF_LocationDefaults::getSuffixOfFile(QString file)
{
    return QFileInfo(file).suffix();
}

bool PDF_NoteCreator::createFile(QString path)
{
    QFile f(path);
    f.open(QIODevice::WriteOnly);
    if(f.isOpen())
    {
        f.close();
        return true;
    }
    return false;
}
QString PDF_ImageSaver::imageSaverNameProducer(QString dirPath, QString pdfName)
{
    return dirPath + pdfName + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()) +".png";
}

bool PDF_ImageSaver::saveImage(QImage image, QString path){
    return image.save(path);
}

QVariant PDF_FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        if( role == Qt::DecorationRole )//DecorationRole
        {
            QFileInfo info = PDF_FileSystemModel::fileInfo(index);
            if(info.isFile())
            {
                if(info.suffix() == "pdf")
                {
                    return QPixmap(":/windowIcon/icon/pdf.ico");
                }
            }
        }
    }
    return QFileSystemModel::data(index, role);
}


QString PDF_GetDir::getDir(QWidget* parent, QString title, QString text){
    return QFileDialog::getExistingDirectory(parent, title, text);
}

