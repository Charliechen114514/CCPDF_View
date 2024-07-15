#ifndef CCPDF_OCRTEXTHELLPER_H
#define CCPDF_OCRTEXTHELLPER_H
#include "ocranalisishelper.h"
#include "CCPDF_Global.h"
#include <QImage>
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "DLLSupport/CCPDF_DLLPluginImporter/ccpdf_externalplugin_externeldll_importer.h"

class CCPDF_ExternalPlugin_ExternelDLL_Importer;
class QImage;
class CCPDF_SinglePDF_Widget;

template<int CREATE_PTR_N, int SETTING_PTR_N, int FETCH_PTR_N, int ERASE_PTR_N>
class CCPDF_OCRTextHelper
{
public:

    using OCRHelper = OCR_Analisys_Helper<
        CREATE_PTR_N, SETTING_PTR_N,
        FETCH_PTR_N, ERASE_PTR_N>;

    using OCR_HANDLE_INDEX = int;

    using OCR_Core_Handle = void*;

    struct OCRError
    {
        enum class Error{
            NO_ERROR,
            NO_BIND_PDF,
            _NO_PLUGIN_FOUND,
            _CANNOT_LOAD_PLUGIN,
            _CANNOT_CREATE_HANDLE,
            _CANNOT_RESOLVE_SYMBOL,
            NO_IMAGE_SAVE_TO_READ
        } e {Error::NO_ERROR};
        QString errorString(){
            switch(e)
            {
            case Error::NO_ERROR:
                return "";
            case Error::NO_BIND_PDF:
                return "没有选中目标PDF！";
            case Error::_NO_PLUGIN_FOUND:
                return "你没有加载插件!请先加载插件";
            case Error::_CANNOT_LOAD_PLUGIN:
                return "无法加载插件！";
            case Error::_CANNOT_CREATE_HANDLE:
                return "插件缺失句柄信息！无法创建句柄！";
            case Error::_CANNOT_RESOLVE_SYMBOL:
                return "库错误！请重新安装插件尝试！";
            case Error::NO_IMAGE_SAVE_TO_READ:
                return "导出图片不存在，请先创建存储文件夹！";
            }
            return "";
        }
    };
    QString errorString(){checkGlobalError();return e.errorString();}
    CCPDF_OCRTextHelper(OCRHelper* helper):
        ocrHandle(new CCPDF_ExternalPlugin_ExternelDLL_Importer),
        helper(helper){}
    DISABLE_COPY(CCPDF_OCRTextHelper);
    virtual ~CCPDF_OCRTextHelper()
    {
        if(handle)
        {
            typename OCRHelper::ERASE_PTR ErasePTR = (typename OCRHelper::ERASE_PTR)functors[eraseHandleIndex];
            if(ErasePTR)
                ErasePTR(handle);
        }
    }
    void    setImageSavingDir(const QString dir = __OCR_SHARE_PIC){
        CCPDF_FileUtils::FileUtils::createDirAnyWay(dir);
        this->image_dir = dir;
    };
    void    setOperatingPDF(CCPDF_SinglePDF_Widget* w){this->w = w;}
    void    setPluginDependencyPath(const QString& LibraryDir, const QString& LibraryPath)
    {
        ocrHandle->setDLLSearchingPath(LibraryDir);
        ocrHandle->fetchDLL(LibraryPath);
        helper->registerHandles(functors, ocrHandle.get());
        registerHandle();
    }
    virtual void    setLanguage(const char* lang, OCR_HANDLE_INDEX index)
    {
        if(!running_check(index)){
            return;
        }
        typename OCRHelper::SET_PTR languageSetFunc = (typename OCRHelper::SET_PTR)functors[index];
        languageSetFunc(handle, lang);
    }
    virtual void    setPicture(OCR_HANDLE_INDEX index)
    {
        if(!running_check(index)){
            return;
        }
        QImage image = w->renderImage();
        imagePath = CCPDF_FileUtils::ImageWrite::saveRandImageTo(&image, image_dir);
        typename OCRHelper::SET_PTR imageSet = (typename OCRHelper::SET_PTR)functors[index];
        imageSet(handle,  imagePath.toStdString().c_str());
    }
    virtual QString innerError(OCR_HANDLE_INDEX index){
        if(!running_check(index)){
            return "符号解析错误！";
        }
        typename OCRHelper::GET_PTR error = (typename OCRHelper::GET_PTR)functors[index];
        const char* errorString = error(handle);
        return {errorString};
    }

    virtual QString getText(OCR_HANDLE_INDEX index)
    {
        if(!fine()){
            checkGlobalError();
            return "";
        }
        if(!running_check(index)){
            checkGlobalError();
            return "";
        }
        if(!CCPDF_FileUtils::FileUtils::isFileExsits(imagePath))
        {
            e.e = OCRError::Error::NO_IMAGE_SAVE_TO_READ;
            return "";
        }

        typename OCRHelper::GET_PTR Textget = (typename OCRHelper::GET_PTR)functors[index];
        const char* heapSrc = Textget(handle);
        QString res(heapSrc);
        if(res.isEmpty()){
            res = innerError(OCRHelper::SYMBOL_FOR_INTERNAL_ERROR);
            return res;
        }
        else
        {
            delete[] heapSrc;
        }
        CCPDF_FileUtils::FileUtils::removeFile(imagePath);
        return res;
    }
    bool            setDataSets(const char* path,OCR_HANDLE_INDEX index){
        if(!neccessCheck(registerHandleIndex))
            return false;
        auto setDataSet = (typename OCRHelper::SET_PTR)functors[index];
        setDataSet(handle, path);
        return true;
    }
    void                        clearImageDir(){CCPDF_FileUtils::DirentClear::clearAllTargets(image_dir);}
    bool                        fine() const {return e.e == OCRError::Error::NO_ERROR && w && isSymbolLoadAll();};
    typename OCRError::Error    getError(){return e.e;}
    void                        clearError(){e.e = OCRError::Error::NO_ERROR;ocrHandle->clearError();}
    int                         registerHandleIndex = 0;
    int                         eraseHandleIndex = OCRHelper::SYMBOL_MAX_INDEX;
protected:
    OCRError        e;
    void            registerHandle(){
        if(!neccessCheck(registerHandleIndex))
            return;
        auto initializationsFunc = (typename OCRHelper::CREATE_PTR)functors[registerHandleIndex];
        handle = initializationsFunc();
    }

    bool            neccessCheck(OCR_HANDLE_INDEX index){
        if(!w)
        {e.e = OCRError::Error::NO_BIND_PDF;return false;}
        if(index > OCRHelper::SYMBOL_MAX_INDEX)
        {e.e = OCRError::Error::_CANNOT_RESOLVE_SYMBOL;return false;}
        if(!functors[index])
        {e.e = OCRError::Error::_CANNOT_RESOLVE_SYMBOL;return false;}
        return true;
    }
    bool            running_check(OCR_HANDLE_INDEX index){
        if(!neccessCheck(index)) return false;
        if(!handle) {e.e = OCRError::Error::_CANNOT_CREATE_HANDLE; return false;}
        return true;
    }
    bool            isSymbolLoadAll() const{
        for(int i = 0; i < OCRHelper::SYMBOL_SUM; i++)
            if(!functors[i]) return false;
        return true;
    }
    void                                        checkGlobalError(){
        if(!w) {e.e = OCRError::Error::NO_BIND_PDF;return;}
        if(!ocrHandle->isDLLLoad()){e.e = OCRError::Error::_NO_PLUGIN_FOUND;return;}
        if(!handle){e.e = OCRError::Error::_CANNOT_CREATE_HANDLE;return;}
        if(!isSymbolLoadAll()){e.e = OCRError::Error::_CANNOT_RESOLVE_SYMBOL;return;}
    }
    QString                                     image_dir {""};
    OCR_Core_Handle handle{};
    std::unique_ptr<CCPDF_ExternalPlugin_ExternelDLL_Importer> ocrHandle;
    std::unique_ptr<OCRHelper>                  helper;
    QString                                     imagePath;
    typename OCRHelper::General_PTR             functors[OCRHelper::SYMBOL_SUM] {};
    __MEMEROY_NO_HOLD CCPDF_SinglePDF_Widget*   w {nullptr};
};

struct TesseractOCRTextHelper : public  CCPDF_OCRTextHelper<TESS_CREATE, TESS_SET, TESS_GET, TESS_ERASE>
{
    TesseractOCRTextHelper(OCRHelper* helper):CCPDF_OCRTextHelper(helper){}
    DISABLE_COPY(TesseractOCRTextHelper);
    ~TesseractOCRTextHelper() = default;
};
#endif // CCPDF_OCRTEXTHELLPER_H
