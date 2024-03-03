#ifndef OCRPACKAGECORE_H
#define OCRPACKAGECORE_H

#include <QProcess>         // Imports Actually Executer
#include <QStringList>

//  *******************************************************************
//  Class Name:> OCRPackageCore
//  Usage and comments:> The Base Core of Processings,
//  here we config the real processor and handle the OCR tasks
//
//  *******************************************************************
class OCRPackageCore{
public:
    OCRPackageCore() = delete;
    const OCRPackageCore& operator=(const OCRPackageCore&) = delete;
    OCRPackageCore(const OCRPackageCore&) = delete;
    ~OCRPackageCore(){
        delete processor;
    }

    OCRPackageCore(QString exePath):exePath(exePath){
        this->processor = new QProcess;
    }

    void config(QString picturePath, QString toWhere, QString languageString){
        this->picturePath = picturePath;
        this->toWhere = toWhere;
        this->languageString = languageString;
    }

    OCRPackageCore(QString exePath, QString picturePath, QString toWhere, QString languageString):
        languageString(languageString), picturePath(picturePath),toWhere(toWhere),exePath(exePath){
        this->processor = new QProcess;
    };


    bool   execute();

    QString getResultTxt(){
        return toWhere.endsWith(".txt") ? toWhere : toWhere + ".txt";
    }

    // static:
    // setters:
    // getters:
protected:

private:
    QProcess*               processor = nullptr;
    QString                 languageString;
    QString                 picturePath;
    QString                 toWhere;
    QString                 exePath;
    QStringList             makeArgs(){
        QStringList args;
        args << picturePath << toWhere << "-l" << languageString;
        return args;
    }
};

#endif // OCRPACKAGECORE_H
