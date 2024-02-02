#include "pdfloaderrorhandle.h"
#include "ccpdf_loader.h"
#include <qpdfdocument.h>
// handle the ccpdf_loader_error

QString HandlePdfLoaderError::getErrorString(CCPDF_Loader* l)
{
    switch(l->state)
    {
    case CCPDF_Loader::LoaderErrorState::No_Error:
        return "当前没有错误";
    case CCPDF_Loader::LoaderErrorState::Unknown_Error:
        return "无法加载PDF，发生了未知的错误";
    case CCPDF_Loader::LoaderErrorState::Data_Loading:
        return "无法加载PDF，数据尚未加载成功";
    case CCPDF_Loader::LoaderErrorState::FilePath_Error:
        return "无法加载PDF，请检查路径";
    case CCPDF_Loader::LoaderErrorState::InvalidFileFormat:
        return "无法加载PDF，这是因为文件格式有问题！";
    case CCPDF_Loader::LoaderErrorState::Uncorrected_Password:
        return "无法加载PDF，这是因为密码不正确!";
    case CCPDF_Loader::LoaderErrorState::UnsupportedSecurityScheme:
        return "无法加载PDF，这是因为本软件尚不支持解密此PDF!";
    case CCPDF_Loader::LoaderErrorState::Unallowed_MultiInit:
        return "无法加载PDF，这是因为重复的加载导致的！";
    }
    return "";
}
