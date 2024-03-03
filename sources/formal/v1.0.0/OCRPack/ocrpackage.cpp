#include "ocrerrorstringadapter.h"
#include "ocrpackage.h"
#include "ocrpackageprivate.h"

#define CHECK_BEFORE_DO if(!isPackagePTRAvaible()) {error = ErrorState::CORE_UNINITED; return false;}

OCRPackagePrivate::SupportLanguage LanguageAdapter(OCRPackage::LanguageOCR l){
    switch(l)
    {
    case OCRPackage::LanguageOCR::CHINESE:
        return OCRPackagePrivate::SupportLanguage::CHINESE;
    case OCRPackage::LanguageOCR::ENGLISH:
        return OCRPackagePrivate::SupportLanguage::ENGLISH;
    }
    return OCRPackagePrivate::SupportLanguage::ENGLISH;
}

OCRPackage::LanguageOCR LanguageAdapter(OCRPackagePrivate::SupportLanguage l){
    switch(l)
    {

    case OCRPackagePrivate::SupportLanguage::CHINESE:
        return OCRPackage::LanguageOCR::CHINESE;
    case OCRPackagePrivate::SupportLanguage::ENGLISH:
        return OCRPackage::LanguageOCR::ENGLISH;
    }
    return OCRPackage::LanguageOCR::ENGLISH;
}


QString OCRPackage::errorString(){
    return OCRErrorStringAdapter::makeString(error);
}

bool OCRPackage::tryifIsRunnable()
{
    return isPackagePTRAvaible() && this->privateCore->checkVadility();
}

bool OCRPackage::checkMissionStartAble()
{
    return isPackagePTRAvaible() && this->privateCore->checkBasic();
}

bool OCRPackage::isPackagePTRAvaible(){
    return this->privateCore != nullptr;
}

void OCRPackage::checkAndUpdateError(){
    error = OCR_ErrorAdapter::AdaptionOfError(this->privateCore->error);
}

void OCRPackage::initConnections()
{
    // receive single finish
    connect(this->privateCore, &OCRPackagePrivate::ready, this, &OCRPackage::receiveReady);
    connect(this->privateCore, &OCRPackagePrivate::finish, this, &OCRPackage::receiveFinish);
    // receive all finish
    connect(this->privateCore, &OCRPackagePrivate::finishAll, this, &OCRPackage::receiveFinishAll);
    connect(this->privateCore, &OCRPackagePrivate::errorOccur, this, &OCRPackage::checkAndUpdateError);
}

void OCRPackage::initCore()
{
    this->privateCore = new OCRPackagePrivate;
    initConnections();
}

OCRPackage::OCRPackage(QObject *parent) : QObject(parent)
{
    initCore();
}

OCRPackage::~OCRPackage()
{
    if(this->privateCore)
        delete this->privateCore;
    this->privateCore = nullptr;
}

void OCRPackage::setLanguage(LanguageOCR l)
{
    if(!this->privateCore)
        return;
    this->privateCore->setLanguage(LanguageAdapter(l));
}
OCRPackage::LanguageOCR OCRPackage::getLanguage()
{
    if(!this->privateCore)
        return OCRPackage::LanguageOCR::CHINESE;
    return LanguageAdapter(this->privateCore->getLanguage());
}


void OCRPackage::receiveReady(TaskIndex index)
{
    // transmit the signals to the public
    emit readyTask(index);
}

void OCRPackage::receiveFinish(TaskIndex index)
{
    // transmit the siganls to the public
    emit finishTask(index);
}

void OCRPackage::receiveFinishAll()
{
    this->results = this->privateCore->getResults();
    emit finishAll();
}

bool OCRPackage::configExecutableOCRPath(QString exes)
{
    CHECK_BEFORE_DO;
    this->privateCore->setCORE(exes);
    return true;
}

bool OCRPackage::configSavingDirPath(QString savingDir)
{
    CHECK_BEFORE_DO;
    this->privateCore->setResDir(savingDir);
    return true;
}

bool OCRPackage::addSinglePic(QString pic)
{
    CHECK_BEFORE_DO;
    this->privateCore->addPic(pic);
    return true;
}

bool OCRPackage::addMutltiPics(QStringList l)
{
    CHECK_BEFORE_DO;
    for(const QString& each : l)
        addSinglePic(each);
    return true;
}

bool OCRPackage::removePicsTarget(QString l)
{
    CHECK_BEFORE_DO;
    return this->privateCore->removePic(l);
}

bool OCRPackage::startRecognize()
{
    CHECK_BEFORE_DO;
    if(!this->privateCore->startTasks())
    {
        checkAndUpdateError();
    }
    return true;
}

bool OCRPackage::clearPackages()
{
    CHECK_BEFORE_DO;
    return this->privateCore->cleanAllPicsAndTasksThreads();
}


