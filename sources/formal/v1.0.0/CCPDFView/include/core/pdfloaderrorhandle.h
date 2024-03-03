#ifndef PDFLOADERRORHANDLE_H
#define PDFLOADERRORHANDLE_H
#include "ccpdf_loader.h"
#include <QString>
class CCPDF_Loader;
// Error handle
class HandlePdfLoaderError
{
public:
    static QString getErrorString(CCPDF_Loader* l);
    static CCPDF_Loader::LoaderErrorState getErrorState(QPdfDocument::Error);
};

#endif // PDFLOADERRORHANDLE_H
