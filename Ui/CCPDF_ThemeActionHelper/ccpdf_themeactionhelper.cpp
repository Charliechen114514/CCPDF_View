#include "ccpdf_themeactionhelper.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"

CCPDF_ThemeActionHelper::Name CCPDF_ThemeActionHelper::renderAlg(const Path& p)
{
    return CCPDF_FileUtils::PathUtils::fileName(p);
}
