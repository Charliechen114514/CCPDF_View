#include "ocrpackageprivate.h"
#include "ocrsingtonspackages.h"
#include <QObject>
#include <QDebug>
#include <QMutex> // for lock
#include <QDir>
#define BROADCAST_ERROR_OCCUR   emit errorOccur()
QMutex mutex;

class SingtonsAdpterFromPrivateToSingle{
public:
    OCRSingtonsPackages::Common_Language operator()(OCRPackagePrivate::SupportLanguage l){
        switch (l) {
        case OCRPackagePrivate::SupportLanguage::CHINESE:
            return OCRSingtonsPackages::Common_Language::Chinese;
        case OCRPackagePrivate::SupportLanguage::ENGLISH:
            return OCRSingtonsPackages::Common_Language::English;
        }
        return OCRSingtonsPackages::Common_Language::Chinese;
    }

    OCRPackagePrivate::SupportLanguage operator()(OCRSingtonsPackages::Common_Language l){
        switch(l)
        {
        case OCRSingtonsPackages::Common_Language::Chinese:
            return OCRPackagePrivate::SupportLanguage::CHINESE;
        case OCRSingtonsPackages::Common_Language::English:
            return OCRPackagePrivate::SupportLanguage::ENGLISH;
        }
        return OCRPackagePrivate::SupportLanguage::CHINESE;
    }
};


void OCRWorkingThread::run()
{
    if(!taskPack)
        return;
    taskPack->startMission();
    emit finishWork(taskPack);
}

OCRPackagePrivate::OCRPackagePrivate(QObject* parent) : QObject(parent)
{
    initConnections();
}

void OCRPackagePrivate::initConnections()
{
    // register the time-to-read-result signals
    connect(this, &OCRPackagePrivate::generateResult, this, &OCRPackagePrivate::readEachPackInfo);
}

void OCRPackagePrivate::emitFinish(int index)
{
    emit finish(index);
}

void OCRPackagePrivate::emitReady(int index)
{
    emit ready(index);
}


bool OCRPackagePrivate::constructTasks()
{
    if(!this->taskLists.empty())
    {
        error = ErrorState::TASK_ALREADY_DEPATCH;
        BROADCAST_ERROR_OCCUR;
        return false;
    }

    if(this->picLists.isEmpty())
    {
        error = ErrorState::EMPTY_TASK;
        BROADCAST_ERROR_OCCUR;
        return false;
    }

    int index = 0;
    for(const QString& each : this->picLists)
    {
        OCRSingtonsPackages* p = new OCRSingtonsPackages(exePath, index);
        p->setPictures(each);
        p->addLanguage(SingtonsAdpterFromPrivateToSingle()(this->language));
        p->setSavingDir(this->resultDir);
        this->taskLists.push_back(p);
        index++;
    }

    return true;
}

bool OCRPackagePrivate::checkVadility()
{
    return !this->exePath.isEmpty() && !this->resultDir.isEmpty() // NO NULL
           && QFile::exists(this->exePath) && QDir().exists(this->resultDir); // EXSITS
}

bool OCRPackagePrivate::checkBasic()
{
    // no initialize or wrong initialize
    if(this->exePath.isEmpty() || !QFile::exists(this->exePath))
    {
        error = ErrorState::NO_EXECUTABLE;
        BROADCAST_ERROR_OCCUR;
        return false;
    }

    if(this->resultDir.isEmpty() || !QDir().exists(this->resultDir))
    {
        error = ErrorState::NO_SAVING_DIR;
        BROADCAST_ERROR_OCCUR;
        return false;
    }
    return true;
}

bool OCRPackagePrivate::startTasks()
{
    if(!checkBasic())
        return false;
    setCurrentState(Working_State::STARTING);
    constructTasks();
    if(this->taskLists.isEmpty())
    {
        error = ErrorState::EMPTY_TASK;
        BROADCAST_ERROR_OCCUR;
        return false;
    }

    for(auto each : this->taskLists)
    {
        OCRWorkingThread* thread = new OCRWorkingThread(each, each->getIndex());
        this->workingThreads.push_back(thread);
        connect(thread, &OCRWorkingThread::finishWork, this, &OCRPackagePrivate::addFinishIndex);
        emitReady(each->getIndex());
        qDebug() << "Mission " << each->getIndex() << "ready";
    }

    // depatch all
    for(auto each_thread : this->workingThreads)
        each_thread->start();

    return true;
}


void OCRPackagePrivate::addFinishIndex(OCRSingtonsPackages* finishWork)
{
    mutex.lock();
    finished.push_back(new OCR_DetectInfo(finishWork->getIndex(), finishWork->getSavePath()));
    finishWork->setTaskStates(true);
    emitFinish(finishWork->getIndex());
    qDebug() << "Mission " << finishWork->getIndex() << "finish";
    if(finished.size() == this->taskLists.size())
        emit this->generateResult(); // jumps to readEachPackInfo()
    mutex.unlock();
}

void OCRPackagePrivate::readEachPackInfo()
{
    sortTheOCRLists();
    for(auto pack : this->finished)
        readResult.push_back((*pack)());

    setCurrentState(Working_State::FINISH);
    emit finishAll();
}

void OCRPackagePrivate::releaseTaskLists()
{
    for(auto& each_task : taskLists)
    {
        if(each_task)
            delete each_task;
        each_task = nullptr;
    }
}

void OCRPackagePrivate::releaseThread()
{
    for(auto& each_thread : workingThreads)
    {
        if(each_thread)
            delete each_thread;
        each_thread = nullptr;
    }
}

bool OCRPackagePrivate::cleanTasksAndThread()
{
    if(working_state == Working_State::FINISH)
    {
        releaseThread();
        releaseTaskLists();
        working_state = Working_State::NO_START;
        return true;
    }
    return false;
}

bool OCRPackagePrivate::cleanAllPicsAndTasksThreads()
{
    if(cleanTasksAndThread())
    {
        picLists.clear();
        return true;
    }
    return false;
}


OCRPackagePrivate::~OCRPackagePrivate()
{
    releaseThread();
    releaseTaskLists();
}



