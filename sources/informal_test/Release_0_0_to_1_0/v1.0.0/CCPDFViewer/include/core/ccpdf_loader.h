#ifndef CCPDF_LOADER_H
#define CCPDF_LOADER_H

#include <QObject>
#include <QPdfDocument> // Load QPdfCoreFile


class CCPDF_Loader : public QObject
{
    Q_OBJECT
public:
    enum class LoaderErrorState{
        No_Error,
        Unknown_Error,
        Data_Loading,
        FilePath_Error,
        InvalidFileFormat,
        Uncorrected_Password,
        UnsupportedSecurityScheme,
        Unallowed_MultiInit
    }state = LoaderErrorState::No_Error;

    explicit CCPDF_Loader(QObject* parent = nullptr);
    bool        loadPdfByFileDialog(QWidget* parent, QString title, bool allowed_duplicate_init = true);
    bool        loadPdf(QString Path, bool allowed_duplicate_init = true);
    ~CCPDF_Loader();
    bool        checkIsLoaded();

    bool        closeThisDocument();

    int         getPageCount();

    QString     getPDFPath(){return pdfPath;}

    bool        showErrorUI(QWidget* parent);

    QString     getErrorString();
private:
    friend class CCPDF_View;
    QPdfDocument*       coreDocument    = nullptr;
    QString             pdfPath;

    bool                HandleErrorFromUiMethod(
                        QWidget* wid, QString loadPath,
                        QPdfDocument::Error err);
    // private func
    void                setPdfPath(QString Path){pdfPath = Path;}
    void                setErrorState(LoaderErrorState s){state = s;}
    void                clearError(){state = LoaderErrorState::No_Error;}
};

#endif // CCPDF_LOADER_H
