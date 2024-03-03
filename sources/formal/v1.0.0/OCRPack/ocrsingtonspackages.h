#ifndef OCRSINGTONSPACKAGES_H
#define OCRSINGTONSPACKAGES_H
#include <QFile>

//  *******************************************************************
//  Class Name:> OCRSingtonsPackages
//  Usage and comments:> Single Task Packages of OCR, it only handles one pictures at one time :)
//
//  *******************************************************************
class OCRSingtonsPackages{
public:
    // statics
    enum class Common_Language{
        Chinese,
        English,

    };

    using TaskIndex = int;

    // static Method to get the String
    static QString translateLanguageToString(Common_Language l);

    OCRSingtonsPackages() = delete;
    const OCRSingtonsPackages& operator=(const OCRSingtonsPackages&) = delete;
    OCRSingtonsPackages(const OCRSingtonsPackages&) = delete;
    OCRSingtonsPackages(QString exePath, TaskIndex index):executionPath(exePath), index(index){};

    QStringList getCurrentDetectingLanguage();
    ~OCRSingtonsPackages(){}
    bool addLanguage(Common_Language l);
    bool popLanguage(Common_Language l);

    void    setPictures(QString pic){
        pictureSource = pic;
    }
    void    setSavingDir(QString dir){this->savingDir = dir;}


    QString getPicture(){return pictureSource;}

    TaskIndex getIndex(){return index;}

    QString getSavePath(){
        return makeSavePathString() + ".txt";
    }

    bool startMission();

    bool setTaskStates(bool state){this->state = state; return this->state;}
protected:
private:
    QString                 pictureSource;
    QString                 executionPath;
    QList<Common_Language>  languages;
    QString                 savingDir;
    TaskIndex               index = 0;

    QString makeLanguageString();

    QString makeSavePathString(){
        return savingDir + QString::number(index);
    }

    bool state = false;
};

#endif // OCRSINGTONSPACKAGES_H
