#ifndef CCPDF_FILEUTILS_H
#define CCPDF_FILEUTILS_H
#include <QStringList>
#ifndef _SUPPORT_PDF_SUFFIX
#define _SUPPORT_PDF_SUFFIX "pdf", "PDF"
#endif

class QWidget;
class QImage;

struct CCPDF_FileUtils
{
    // pdf base related
    struct PDF_Info{
        constexpr static short          PDF_SUFFIX_SUPPORT {2};
        constexpr static const char*    PDF_SUFFIX[PDF_SUFFIX_SUPPORT] {_SUPPORT_PDF_SUFFIX};
        static QStringList              PDF_SUFFIX_LIST() {return {_SUPPORT_PDF_SUFFIX};}
        static QString                  get_pdf_suffix_filter(){return Filter_Creator::createFilterString(PDF_SUFFIX_LIST());}
        static QString                  fetchNameAccordPath(const QString &path);
        static QStringList              nameFilters();
        static QStringList              nameFilters(const QString& fileName, bool isStrict = false);
    };

    struct Prefix_Precheck{
        static bool                     isPDFFile(const QString& path);
        static bool                     isSymbolLinkToPdf(const QString& path);
        static QString                  parseSymbolLinkPdfPath(const QString& path);
    };

    struct Filter_Creator{
        static QString createFilterString(const QStringList& suffixs){
            QString         res;
            for(const auto& each : suffixs)
                res += "(*." + each + ");;";
            return res;
        }
    };

    struct CommonPath{
        static  QString                 desktopPath();
        static  QString                 mainPath();
    };

    struct SelectFileUtils{
        static QString                  selectExsitingFile(const QString caption, const QStringList suffixs, const QString path = ".", QWidget* parent = nullptr);
        static QString                  selectExsitingDir(QString caption, QString path = ".", QWidget* parent = nullptr);

    };

    struct SaveFileUtils{
        static QString                  saveFile(QString caption, QString dirs, QStringList req_suffixs, QWidget* parent = nullptr);
    };

    struct PathUtils{
        static QString                  composePath(QString& dir, QString& fileName);
        static QString                  absolutePath(QString& path);
        static QString                  atDir(QString& path);
        static QString                  fileName(const QString& path);
        static bool                     isFile(const QString& path);
        static bool                     isDir(const QString& path);
    };

    struct FileUtils{
        // check if in
        static bool                     isDirExsits(const QString& dirPath);
        static bool                     isFileExsits(const QString& filePath);
        static bool                     isFileInTargetDir(const QString& dir, const QString& ref_files);
        static QString                  getIfFileInTargetDir(const QString& dir, const QString& ref_files);
        // create dir
        static bool                     createDir(const QString &dirPath);
        static bool                     createFile(QString& file);
        static bool                     createDirAnyWay(const QString &dirPath);
        static bool                     createFileAnyWay(QString& filePath);

        static bool                     removeFile(const QString& path);
    };

    struct File_NameDataBaseGenerator{
        static QString                  geneDateBaseFileName(
            const QString& dirPath, const QString& suffix);
    };


    struct File_ReadWrite{
        enum class WritingFormat{
            INIFormat
        };

        static bool                     clearFile(QString& file);
        static QByteArray               readFile(const QString &file);
        static bool                     writeFile(QString& str, QString& filePath);
    };

    struct ImageWrite{
        static QString                  saveRandImageTo(const QImage* image, const QString& dirPath);
    };


    struct DirentClear{
        static bool                     clearAllTargets(const QString& dir);
    };

};

#undef _SUPPORT_PDF_SUFFIX


#endif // CCPDF_FILEUTILS_H
