#include "ccpdf_fileutils.h"
#include <QStandardPaths> // for common paths
#include <QFileDialog>
#include <QFileInfo>
#include <QDirIterator>
#include <QDir>
#include <QStringDecoder>

QString CCPDF_FileUtils::PDF_Info::fetchNameAccordPath(const QString& Path)
{
    QFileInfo f(Path);
    return f.fileName();
}

QStringList CCPDF_FileUtils::PDF_Info::nameFilters()
{
    QStringList filters;
    for(const auto& each : PDF_SUFFIX)
    {
        QString temp = "";
        temp += "*.";
        filters << temp + each;
    }
    return filters;
}

QStringList CCPDF_FileUtils::PDF_Info::nameFilters(const QString& fileName, bool isStrict)
{
    QStringList filters;
    for(const auto& each : PDF_SUFFIX)
    {
        QString temp;
        if(!isStrict){
            temp = QString("*%1*.").arg(fileName);
        }
        else{
            temp = QString("%1.").arg(fileName);
        }
        filters << temp + each;
    }
    return filters;
}

bool CCPDF_FileUtils::FileUtils::isDirExsits(const QString &dirPath)
{
    QDir dir;
    return dir.exists(dirPath);
}

bool CCPDF_FileUtils::Prefix_Precheck::isPDFFile(const QString &path)
{
    QStringList suffix_req {CCPDF_FileUtils::PDF_Info::PDF_SUFFIX_LIST()};
    QFileInfo checker(path);
    QString file_prefix = checker.suffix();

    for(const auto& each : suffix_req)
        if(each == file_prefix)
            return true;

    return false;
}

bool CCPDF_FileUtils::Prefix_Precheck::isSymbolLinkToPdf(const QString& path)
{
    QFileInfo info(path);
    if (info.exists() && info.isSymLink())
    {
        QString res = info.symLinkTarget();
        if(isPDFFile(res))
            return true;
    }
    return false;
}

QString CCPDF_FileUtils::Prefix_Precheck::parseSymbolLinkPdfPath(const QString& path)
{
    QFileInfo info(path);
    if (info.exists() && info.isSymLink())
    {
        QString res = info.symLinkTarget();
        if(isPDFFile(res))
            return res;
    }
    return "";
}


QString CCPDF_FileUtils::CommonPath::desktopPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

QString CCPDF_FileUtils::CommonPath::mainPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

QString CCPDF_FileUtils::SelectFileUtils::selectExsitingFile(const QString caption, const QStringList suffixs, const QString path, QWidget* parent)
{
    return QFileDialog::getOpenFileName(
        parent, caption, path,
        CCPDF_FileUtils::Filter_Creator::createFilterString(suffixs));
}

QString CCPDF_FileUtils::SelectFileUtils::selectExsitingDir(
    QString caption, QString path, QWidget* parent)
{
    return QFileDialog::getExistingDirectory(parent, caption, path);
}

QString CCPDF_FileUtils::SaveFileUtils::saveFile(
    QString caption, QString dirs, QStringList req_suffixs, QWidget* parent)
{
    QString res = QFileDialog::getSaveFileName(
        parent, caption, dirs,
        CCPDF_FileUtils::Filter_Creator::createFilterString(req_suffixs));
    return res.isEmpty() ? "" : res;
}

bool CCPDF_FileUtils::FileUtils::isFileExsits(const QString &filePath)
{
    QFile f;
    return f.exists(filePath);
}

bool CCPDF_FileUtils::FileUtils::
isFileInTargetDir(const QString& dir, const QString& ref_files)
{
    QString makeFilePath = dir + QDir::separator() + ref_files;
    return CCPDF_FileUtils::FileUtils::isFileExsits(makeFilePath);
}

QString CCPDF_FileUtils::FileUtils::
getIfFileInTargetDir(const QString& dir, const QString& ref_files)
{
    if(isFileInTargetDir(dir, ref_files))
        return dir + QDir::separator() + ref_files;
    return "";
}

QString CCPDF_FileUtils::PathUtils::absolutePath(QString& Path){
    QFileInfo f(Path);
    return f.absoluteFilePath();
}

QString CCPDF_FileUtils::PathUtils::atDir(const QString& path)
{
    QFileInfo f(path);
    return f.dir().path();
}

QString CCPDF_FileUtils::PathUtils::fileName(const QString& path)
{
    QFileInfo f(path);
    return f.baseName();
}

bool CCPDF_FileUtils::PathUtils::isFile(const QString& path)
{
    QFileInfo f(path);
    return f.isFile();
}

bool CCPDF_FileUtils::PathUtils::isDir(const QString& path)
{
    QFileInfo f(path);
    return f.isDir();
}

QString CCPDF_FileUtils::PathUtils::composePath(QString& dir, QString& file){
    return QDir::cleanPath(dir) + QDir::separator() + file;
}

bool CCPDF_FileUtils::FileUtils::createDir(const QString& dirPath)
{
    QDir dir(dirPath);
    if(!dir.exists(dirPath)){
        return dir.mkpath(".");
    }
    return false;
}

bool CCPDF_FileUtils::FileUtils::createDirAnyWay(const QString& dirPath)
{
    if(!isDirExsits(dirPath)){
        return createDir(dirPath);
    }
    return true;
}

bool CCPDF_FileUtils::FileUtils::createFile(QString& file)
{
    QString sPath = file.left(file.lastIndexOf('/'));
    QDir dir(sPath);
    dir.mkpath(".");
    QFile f(file);
    f.open(QIODevice::WriteOnly);
    f.close();
    return f.exists();
}

bool CCPDF_FileUtils::FileUtils::createFileAnyWay(QString& filePath)
{
    if(!isFileExsits(filePath)){
        return createFile(filePath);
    }
    return true;
}

bool CCPDF_FileUtils::FileUtils::removeFile(const QString& path)
{
    return QFile::remove(path);
}

QString  CCPDF_FileUtils::File_NameDataBaseGenerator::geneDateBaseFileName
    (const QString& dirPath, const QString& suffix)
{
    return dirPath + "/" + QString::number(QDateTime::currentMSecsSinceEpoch()) + "." + suffix;
}

QByteArray CCPDF_FileUtils::File_ReadWrite::readFile(const QString& file)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    if(f.isOpen()){
        return f.readAll();
    }
    return "";
}

bool CCPDF_FileUtils::File_ReadWrite::writeFile(QString& str, QString& filePath)
{
    QFile f(filePath);
    f.open(QIODevice::WriteOnly);
    if(f.isOpen()){
        return f.write(str.toStdString().c_str());
    }
    return false;
}

QString CCPDF_FileUtils::ImageWrite::
saveRandImageTo(const QImage* image, const QString& dirPath)
{
    QString fileName = File_NameDataBaseGenerator::geneDateBaseFileName(dirPath, "png");
    image->save(fileName);
    return fileName;
}

bool CCPDF_FileUtils::DirentClear::
clearAllTargets(const QString& path)
{
    QDir Dir(path);
    if(Dir.isEmpty())
    {
        return true;
    }

    // 第三个参数是QDir的过滤参数，这三个表示收集所有文件和目录，且不包含"."和".."目录。
    // 因为只需要遍历第一层即可，所以第四个参数填QDirIterator::NoIteratorFlags
    QDirIterator DirsIterator(path, QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);
    while(DirsIterator.hasNext())
    {
        if (!Dir.remove(DirsIterator.next())) // 删除文件操作如果返回否，那它就是目录
        {
            QDir(DirsIterator.filePath()).removeRecursively(); // 删除目录本身以及它下属所有的文件及目录
        }
    }
    return true;
}

