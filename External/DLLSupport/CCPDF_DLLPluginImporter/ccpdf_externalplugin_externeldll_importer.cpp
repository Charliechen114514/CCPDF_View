#include <QLibrary>
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#define ADD_LIB_PATH(path)  SetDllDirectoryA(path)
#else
#define ADD_LIB_PATH(path)  setenv("LD_LIBRARY_PATH", (QString("$LD_LIBRARY_PATH:") + path).toStdString().c_str())
#endif
#include "ccpdf_externalplugin_externeldll_importer.h"

CCPDF_ExternalPlugin_ExternelDLL_Importer::
    CCPDF_ExternalPlugin_ExternelDLL_Importer()
{
    internal_library = std::make_unique<QLibrary>();
}

bool CCPDF_ExternalPlugin_ExternelDLL_Importer::
    checkIsLoad()
{
    if(!internal_library->isLoaded())
    {
        e.e = DyLoadError::Error::NO_DLL_FOUND;
        return false;
    }
    return true;
}
bool CCPDF_ExternalPlugin_ExternelDLL_Importer::
isDLLLoad()
{
    return internal_library->isLoaded();
}

QString CCPDF_ExternalPlugin_ExternelDLL_Importer::
    errorString() const
{
    return internal_library->errorString();
}

void CCPDF_ExternalPlugin_ExternelDLL_Importer::
    setDLLSearchingPath(const QString& lib)
{
    ADD_LIB_PATH(lib.toStdString().c_str());
}

bool CCPDF_ExternalPlugin_ExternelDLL_Importer::
    fetchDLL(const QString& dllPath)
{
    if(!internal_library->isLibrary(dllPath)){
        e.e = DyLoadError::Error::NOT_LOADABLE_PLUGIN;
        return false;
    }

    if(internal_library->isLoaded())
    {
        internal_library->unload();
    }
    internal_library->setFileName(dllPath);
    internal_library->load();
    return true;
}


CCPDF_ExternalPlugin_ExternelDLL_Importer::GeneralFunctionPtr
    CCPDF_ExternalPlugin_ExternelDLL_Importer::
    resolve_symbol(const char* what_symbol)
{
    if(!checkIsLoad())
        return nullptr;

    return internal_library->resolve(what_symbol);
}

CCPDF_ExternalPlugin_ExternelDLL_Importer::
    ~CCPDF_ExternalPlugin_ExternelDLL_Importer()
{
    internal_library->unload();
}
