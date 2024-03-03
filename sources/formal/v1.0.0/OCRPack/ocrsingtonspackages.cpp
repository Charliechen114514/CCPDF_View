#include "ocrsingtonspackages.h"
#include "ocrpackagecore.h" // Imports the exactly execuation package
bool OCRSingtonsPackages::addLanguage(Common_Language l){
    if(!languages.contains(l))
    {
        languages.push_back(l);
        return true;
    }
    else
        return false;
}

bool OCRSingtonsPackages::popLanguage(Common_Language l)
{
    return this->languages.removeOne(l);
}

QString OCRSingtonsPackages::translateLanguageToString(Common_Language l)
{
    switch(l)
    {
    case Common_Language::Chinese:
        return "chi_sim";
    case Common_Language::English:
        return "eng";
    }
    return "eng";
}

QString OCRSingtonsPackages::makeLanguageString()
{
    QString lang;
    for(auto& l : this->languages)
        lang += translateLanguageToString(l) + "+";
    lang.removeLast();
    return lang;
}


bool OCRSingtonsPackages::startMission()
{
    OCRPackageCore core(this->executionPath, pictureSource, makeSavePathString(), makeLanguageString());
    return core.execute();
}
