#include "ccpdf_externtranslation.h"

CCPDF_ExternTranslation::CCPDF_ExternTranslation(QObject* obj):CCPDF_RunPluginProcess(obj)
{
    type = CurrentSupportType::TRANSLATION;
}
