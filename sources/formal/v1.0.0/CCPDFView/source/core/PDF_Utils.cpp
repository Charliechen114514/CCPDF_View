#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardPaths>
#include <QPdfWriter>
#include <QPainter>
#include "PDF_Utils.h"

void PDF_Window_SavingConfig::setShellQueryingSave()
{
    isSave = false;
}

void PDF_Window_SavingConfig::unsetShellQueryingSave()
{
    isSave = true;
}

bool PDF_Window_SavingConfig::checkIfNeedQueryingSave()
{
    return !isSave;
}

bool PDF_Window_SavingConfig::queryingForSave(QWidget* w)
{
    if(!isSave)
    {
        return QMessageBox::Yes == QMessageBox::question(w, "是否保存", "是否完成保存");
    }
    return true;
}

bool PDF_Window_SavingConfig::queryingForSaveDef(QWidget* w, QString text)
{
    if(!isSave)
    {
        return QMessageBox::Yes == QMessageBox::question(w, "是否保存", text);
    }
    return true;
}

bool PDF_Window_SavingConfig::generalAskForLeave(QWidget* w, QString text)
{
    return QMessageBox::Yes == QMessageBox::question(w, "是否保存", text);
}

QMessageBox::StandardButton PDF_Window_SavingConfig::alterQuestions(QWidget* w, QString text)
{
    return QMessageBox::question(w, "是否保存", text,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
}


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

QString PDF_LocationDefaults::addPDFSuffix(QString& path)
{
    if(!path.endsWith(".pdf"))
        path += ".pdf";
    return path;
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
QString PDF_Saver::saverNameProducer(QString dirPath, QString pdfName, QString suffix)
{
    return dirPath + pdfName + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()) + suffix;
}

bool PDF_Saver::saveImage(QImage image, QString path){
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

QPixmap PDF_ExportWriterConfig::getA4Printable(QPixmap& p)
{
    return p.scaled(PDF_A4_Width*4 + 100, PDF_A4_Height*4 + 100*PDF_A4Ratio, Qt::KeepAspectRatio);
}

QImage  PDF_ExportWriterConfig::getA4PrintableImage(QImage& p)
{
    return p.scaled(PDF_A4_Width*4 + 100, PDF_A4_Height*4 + 100*PDF_A4Ratio, Qt::KeepAspectRatio);
}

bool PDF_WriteTmpPDF::writeTmpPDF(QPixmap &map, QString writingWhere)
{
    QPdfWriter pdfWriter(writingWhere);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);
    PDF_ExportWriterConfig conf;
    map = conf.getA4Printable(map);
    painter.drawPixmap(100, 0, map);
    return true;
}


bool PDF_RemoveFile::removeFile(QString path)
{
    if(path.isEmpty() || !PDF_LocationDefaults::isFileExsits(path)){
        return false;
    }

    if(!QFileInfo(path).isFile())
        return false;

    return QFile::remove(path);
}

bool PDF_RemoveFile::removeDir(QString dirPath)
{
    if(dirPath.isEmpty() || // path empty
        !PDF_LocationDefaults::isFileExsits(dirPath) ||
        !PDF_LocationDefaults::isADir(dirPath)
        ){ // invaild path
        return false;
    }
    QDir dir(dirPath);
    bool st =  dir.removeRecursively();
    dir.mkdir(dirPath);
    return st;
}


