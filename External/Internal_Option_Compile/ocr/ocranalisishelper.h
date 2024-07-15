#ifndef OCRANALISISHELPER_H
#define OCRANALISISHELPER_H
class CCPDF_ExternalPlugin_ExternelDLL_Importer;


// Handles For Registering
template<int CREATE_PTR_N, int SETTING_PTR_N, int FETCH_PTR_N, int ERASE_PTR_N>
struct OCR_Analisys_Helper
{
    static constexpr int SYMBOL_SUM = CREATE_PTR_N + \
                                      SETTING_PTR_N + \
                                      FETCH_PTR_N + \
                                      ERASE_PTR_N;
    static constexpr int SYMBOL_MAX_INDEX = SYMBOL_SUM - 1;
    static constexpr int SYMBOL_FOR_INTERNAL_ERROR = SYMBOL_MAX_INDEX - 1;
    using General_PTR = void(*)();
    using CREATE_PTR = void*(*)();
    using SET_PTR = void*(*)(void*, const char*);
    using GET_PTR = const char*(*)(void*);
    using ERASE_PTR = void(*)(void*);

    CREATE_PTR  createInstance[CREATE_PTR_N];
    SET_PTR     settingsPTR[SETTING_PTR_N];
    GET_PTR     fetchResultsPTR[FETCH_PTR_N];
    ERASE_PTR   eraseHandlePTR[ERASE_PTR_N];

    virtual void registerHandles(General_PTR symbolTable[SYMBOL_SUM],
                                 CCPDF_ExternalPlugin_ExternelDLL_Importer* imp) = 0;
};

static constexpr int TESS_CREATE    = 1;
static constexpr int TESS_SET       = 3;
static constexpr int TESS_GET       = 2;
static constexpr int TESS_ERASE     = 1;

struct TesseractOCRHandle : OCR_Analisys_Helper<TESS_CREATE,
                                                TESS_SET,
                                                TESS_GET,
                                                TESS_ERASE>
{
    static constexpr const char*      symbols[SYMBOL_SUM] = {
        "TesseractWrapper_create",          // 0

        "TesseractWrapper_setLanguage",
        "TesseractWrapper_setTessPrifix",
        "TesseractWrapper_setViewImage",

        "TesseractWrapper_getTextFromImage",
        "TesseractWrapper_ErrorString",

        "TesseractWrapper_Erase"            // 6
    };

    enum class SYMBOL_FUNC_INDEX
    {
        TesseractWrapper_create = 0,
        TesseractWrapper_setLanguage,
        TesseractWrapper_setTessPrifix,
        TesseractWrapper_setViewImage,
        TesseractWrapper_getTextFromImage,
        TesseractWrapper_ErrorString,
        TesseractWrapper_Erase
    };

    void registerHandles(General_PTR symbolTable[SYMBOL_SUM],
                         CCPDF_ExternalPlugin_ExternelDLL_Importer* imp) override;
};


#endif // OCRANALISISHELPER_H
