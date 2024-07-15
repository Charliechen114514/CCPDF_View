#include "ccpdf_loader.h"
#include <QPdfDocument>
#include <QPainter>

CCPDF_Loader::CCPDF_Loader(QObject *parent)
    : QObject{parent}
{
    core_document = std::make_unique<QPdfDocument>(new QPdfDocument);
}

CCPDF_Loader::~CCPDF_Loader()
{
    qDebug() << "Close Loader";
}

int CCPDF_Loader::pageCount()
{
    if(!core_document)
        return 0;
    else return core_document->pageCount();
}

QImage CCPDF_Loader::passCurrentImage(int page, QSize size)
{
    QImage transparentImage(core_document->render(page, size));

    // 创建一个新的QImage对象，大小与透明图片相同，并用白色填充背景
    QImage whiteBackgroundImage(transparentImage.size(), QImage::Format_RGB32);
    whiteBackgroundImage.fill(QColor(Qt::white).rgb());

    // 使用QPainter将带透明背景的图片绘制到新的QImage对象上
    QPainter painter(&whiteBackgroundImage);
    painter.drawImage(0, 0, transparentImage);
    return whiteBackgroundImage;
}

bool CCPDF_Loader::loadPDF(QString path)
{
    loadPath = path;
    switch(core_document->load(path))
    {
    case QPdfDocument::Error::None:
        emit loadSuccess();break;
    case QPdfDocument::Error::Unknown:
        e.e = CCPDF_Loader_Error::Error::UNKNOWN;break;
    case QPdfDocument::Error::DataNotYetAvailable:
        e.e = CCPDF_Loader_Error::Error::WAIT_LOAD;break;
    case QPdfDocument::Error::FileNotFound:
        e.e = CCPDF_Loader_Error::Error::FILE_UNFIND;break;
    case QPdfDocument::Error::InvalidFileFormat:
        e.e = CCPDF_Loader_Error::Error::InvalidFileFormat;break;
    case QPdfDocument::Error::IncorrectPassword:
        e.e = CCPDF_Loader_Error::Error::PASSWD_INCORRECT;break;
    case QPdfDocument::Error::UnsupportedSecurityScheme:
        e.e = CCPDF_Loader_Error::Error::UNKNOWN;break;
    }

    return fine();
}


