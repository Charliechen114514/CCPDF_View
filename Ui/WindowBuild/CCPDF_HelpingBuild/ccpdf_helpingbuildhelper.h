#ifndef CCPDF_HELPINGBUILDHELPER_H
#define CCPDF_HELPINGBUILDHELPER_H
#include "CCPDF_Global.h"
class QTabWidget;

struct CCPDF_HelpingBuildHelper
{
    CCPDF_HelpingBuildHelper() = default;
    ~CCPDF_HelpingBuildHelper() = default;
    static void addTabTo(
        __MEMEROY_NO_HOLD
        QTabWidget *w, const QString& tabName, const QString& helpFile);
};

#endif // CCPDF_HELPINGBUILDHELPER_H
