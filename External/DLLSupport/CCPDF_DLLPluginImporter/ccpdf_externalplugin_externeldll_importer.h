#ifndef CCPDF_EXTERNALPLUGIN_EXTERNELDLL_IMPORTER_H
#define CCPDF_EXTERNALPLUGIN_EXTERNELDLL_IMPORTER_H
#include "CCPDF_Global.h"

class QLibrary;

class CCPDF_ExternalPlugin_ExternelDLL_Importer
{
public:
    using GeneralFunctionPtr = void(*)();
    CCPDF_ExternalPlugin_ExternelDLL_Importer();
    ~CCPDF_ExternalPlugin_ExternelDLL_Importer();
    DISABLE_COPY(CCPDF_ExternalPlugin_ExternelDLL_Importer);

    bool    fetchDLL(const QString& dllPath);
    void    setDLLSearchingPath(const QString& lib);
    bool    isFine(){return e.e == DyLoadError::Error::NO_ERR;}
    bool    isDLLLoad();
    void    clearError(){e.e = DyLoadError::Error::NO_ERR;}
    __Required_Static_Cast_For_Further_Using
        GeneralFunctionPtr   resolve_symbol(const char* what_symbol);
    QString errorString() const;

    struct DyLoadError
    {
        enum class Error{
            NO_ERR,
            NOT_LOADABLE_PLUGIN,
            NO_DLL_FOUND,
            CAN_NOT_RESOLVE_NAME
        }e;
    };

private:
    bool                        checkIsLoad();
    QStringList                 functionNameLists;
    std::unique_ptr<QLibrary>   internal_library;
    DyLoadError                 e;
};

#endif // CCPDF_EXTERNALPLUGIN_EXTERNELDLL_IMPORTER_H
