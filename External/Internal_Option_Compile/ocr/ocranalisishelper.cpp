#include "ocranalisishelper.h"
#include "DLLSupport/CCPDF_DLLPluginImporter/ccpdf_externalplugin_externeldll_importer.h"

void TesseractOCRHandle::registerHandles(General_PTR symbolTable[SYMBOL_SUM],
                                         CCPDF_ExternalPlugin_ExternelDLL_Importer* imp)
{
    for(int i = 0; i <= SYMBOL_MAX_INDEX; i++)
    {
        symbolTable[i] = imp->resolve_symbol(symbols[i]);
    }
}
