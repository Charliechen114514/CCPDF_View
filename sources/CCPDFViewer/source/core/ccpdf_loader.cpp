#include "ccpdf_loader.h"
#include "pdfloaderrorhandle.h"
#include <QFileDialog>
#include <QMessageBox>
#include "PDF_Utils.h"
/// Ui error handleLoad
///

CCPDF_Loader::LoaderErrorState transErrorLoaderState(QPdfDocument::Error err)
{
    switch(err)
    {
    case QPdfDocument::Error::None:
        return CCPDF_Loader::LoaderErrorState::No_Error;
    case QPdfDocument::Error::Unknown:
        return CCPDF_Loader::LoaderErrorState::Unknown_Error;
    case QPdfDocument::Error::DataNotYetAvailable:
        return CCPDF_Loader::LoaderErrorState::Data_Loading;
    case QPdfDocument::Error::FileNotFound:
        return CCPDF_Loader::LoaderErrorState::FilePath_Error;
    case QPdfDocument::Error::InvalidFileFormat:
        return CCPDF_Loader::LoaderErrorState::InvalidFileFormat;
    case QPdfDocument::Error::IncorrectPassword:
        return CCPDF_Loader::LoaderErrorState::Uncorrected_Password;
    case QPdfDocument::Error::UnsupportedSecurityScheme:
        return CCPDF_Loader::LoaderErrorState::UnsupportedSecurityScheme;
    }
    return CCPDF_Loader::LoaderErrorState::Unknown_Error;
}

QPdfDocument::Error transErrorLoaderState(CCPDF_Loader::LoaderErrorState l)
{
    switch(l)
    {
    case CCPDF_Loader::LoaderErrorState::No_Error:
        return QPdfDocument::Error::None;
    case CCPDF_Loader::LoaderErrorState::Unknown_Error:
        return QPdfDocument::Error::Unknown;
    case CCPDF_Loader::LoaderErrorState::Data_Loading:
        return QPdfDocument::Error::DataNotYetAvailable;
    case CCPDF_Loader::LoaderErrorState::FilePath_Error:
        return QPdfDocument::Error::FileNotFound;
    case CCPDF_Loader::LoaderErrorState::InvalidFileFormat:
        return QPdfDocument::Error::InvalidFileFormat;
    case CCPDF_Loader::LoaderErrorState::Uncorrected_Password:
        return QPdfDocument::Error::IncorrectPassword;
    case CCPDF_Loader::LoaderErrorState::UnsupportedSecurityScheme:
        return QPdfDocument::Error::UnsupportedSecurityScheme;
    case CCPDF_Loader::LoaderErrorState::Unallowed_MultiInit:
        return QPdfDocument::Error::Unknown;
        break;
    }
    return QPdfDocument::Error::Unknown;
}

QString CCPDF_Loader::getErrorString()
{
    return HandlePdfLoaderError::getErrorString(this);
}


bool CCPDF_Loader::HandleErrorFromUiMethod(QWidget* wid, QString loadPath, QPdfDocument::Error err)
{
    switch(err)
    {
    case QPdfDocument::Error::None:
        return true;
    case QPdfDocument::Error::Unknown:
        QMessageBox::critical(wid, "错误","无法加载PDF，发生了未知的错误");return false;
    case QPdfDocument::Error::DataNotYetAvailable:
        QMessageBox::critical(wid, "错误","无法加载PDF，数据尚未加载成功");return false;
    case QPdfDocument::Error::FileNotFound:
        QMessageBox::critical(wid, "错误","无法加载PDF，请检查路径:> " + loadPath);return false;
    case QPdfDocument::Error::InvalidFileFormat:
        QMessageBox::critical(wid, "错误","无法加载PDF，这是因为文件格式有问题！");return false;
    case QPdfDocument::Error::IncorrectPassword:
        QMessageBox::critical(wid, "错误","无法加载PDF，这是因为密码有问题!");return false;
    case QPdfDocument::Error::UnsupportedSecurityScheme:
        QMessageBox::critical(wid, "错误","无法加载PDF，这是因为本软件尚不支持解密此PDF!");return false;
        break;
    }

    return false;
}


CCPDF_Loader::CCPDF_Loader(QObject *parent):QObject(parent)
{}

bool CCPDF_Loader::loadPdfByFileDialog(QWidget* parent, QString title, bool allowed_duplicate_init)
{
    QString res = QFileDialog::getOpenFileName(parent, title, PDF_LocationDefaults::getDesktopLocation(), "PDF文件(*.pdf)");
    if(res.isEmpty())
        return false;

    return loadPdf(res, allowed_duplicate_init);
}


bool CCPDF_Loader::loadPdf(QString Path, bool allowed_duplicate_init)
{
    // Null Path return
    if(Path.isEmpty())
    {
        setErrorState(LoaderErrorState::FilePath_Error);
        return false;
    }

    // Handle Multi-init
    if(!allowed_duplicate_init && this->coreDocument)
    {
        setErrorState(LoaderErrorState::Unallowed_MultiInit);
        return false;
    }
    else
    {
        if(!this->coreDocument)
            delete this->coreDocument;
    }

    this->coreDocument = new QPdfDocument(this);
    QPdfDocument::Error err = coreDocument->load(Path);
    this->state = transErrorLoaderState(err);
    this->pdfPath = Path;
    return true;
}

int CCPDF_Loader::getPageCount()
{
    if(!this->checkIsLoaded())
        return 0;
    else
        return this->coreDocument->pageCount();
}

bool CCPDF_Loader::checkIsLoaded()
{
    return this->coreDocument && this->coreDocument->status() == QPdfDocument::Status::Ready;
}


bool CCPDF_Loader::closeThisDocument()
{
    if(!this->checkIsLoaded())
        return false;

    this->coreDocument->close();
    delete this->coreDocument;

    return true;
}

bool CCPDF_Loader::showErrorUI(QWidget* parent)
{
    return HandleErrorFromUiMethod(parent, pdfPath, transErrorLoaderState(state));
}

CCPDF_Loader::~CCPDF_Loader()
{
    closeThisDocument();
}

