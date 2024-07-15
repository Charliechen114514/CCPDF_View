#ifndef CCPDF_EXTERNTRANSLATION_H
#define CCPDF_EXTERNTRANSLATION_H
#include "External_Option_Compile/CCPDF_RunPluginProcess/ccpdf_runpluginprocess.h"

class CCPDF_ExternTranslation : public CCPDF_RunPluginProcess
{
public:
    static constexpr const char* FILE_NAME = "writing.plugin.output";
    CCPDF_ExternTranslation(QObject* obj);
    DISABLE_COPY(CCPDF_ExternTranslation);
    void    setTranslationExecutionPlugin(const QString& where){
        setProcess(where);
    }
    void    setTranslationResultReading(const QString& where){
        setfetchResultAt(where);
    }
    void    run(){
        this->runThis();
    }
    QString fetchResult(){
        return this->result;
    }
};

#endif // CCPDF_EXTERNTRANSLATION_H
