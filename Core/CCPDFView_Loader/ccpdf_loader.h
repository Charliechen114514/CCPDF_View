#ifndef CCPDF_LOADER_H
#define CCPDF_LOADER_H
#include <QObject>
#include <QPdfDocument>

class CCPDF_Loader : public QObject
{
    Q_OBJECT
public:
    explicit                        CCPDF_Loader(QObject *parent = nullptr);
    CCPDF_Loader(const CCPDF_Loader&) = delete;
    const CCPDF_Loader& operator=(const CCPDF_Loader&) = delete;
    ~CCPDF_Loader();
    bool                            loadPDF(QString path);
    int                             pageCount();
    struct CCPDF_Loader_Error{
        enum class Error{
            NO_ERROR,
            FILE_UNFIND,
            PASSWD_INCORRECT,
            InvalidFileFormat,
            WAIT_LOAD,
            UNKNOWN
        }e{Error::NO_ERROR};
        static QString errorString(Error r){
            switch (r) {
            case Error::NO_ERROR:
                return "No Error";
            case Error::FILE_UNFIND:
                return "File Unfind";
            case Error::PASSWD_INCORRECT:
                return "Passwd incorrect";
            case Error::InvalidFileFormat:
                return "file format invalid";
            case Error::WAIT_LOAD:
                return "WaitLoad";
            case Error::UNKNOWN:
                return "Unsupported checked error!";
            }
            return "Unsupported checked error!";
        }
        QString errorString(){
            return errorString(e);
        }
    };

    bool                            fine(){return e.e == CCPDF_Loader_Error::Error::NO_ERROR;}
    QString                         path(){return loadPath;}
    QImage                          passCurrentImage(int page, QSize size);
private:
    friend class    CCPDF_MainViewWidget;
    friend struct   CCPDF_Info;
    friend class    CCPDF_TextHelper;
    friend class    CCPDF_BookMarkManager;
    friend class    CCPDF_SearchManager;
    friend class    CCPDF_PDfLinkWidgetManager;
    std::unique_ptr<QPdfDocument>   core_document;
    CCPDF_Loader_Error              e;
    QPdfDocument*                   passDoc() const {return core_document.get();};
    QString                         loadPath;
signals:
    void                            loadSuccess();
};

#endif // CCPDF_LOADER_H
