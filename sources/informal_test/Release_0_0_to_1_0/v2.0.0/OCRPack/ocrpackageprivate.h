#ifndef OCRPACKAGEPRIVATE_H
#define OCRPACKAGEPRIVATE_H
#include <QObject>
#include <QThread>
#include "ocr_detectinfo.h"
class OCRSingtonsPackages;

class OCRWorkingThread : public QThread
{
    Q_OBJECT;
public:
    OCRWorkingThread() = delete;
    explicit OCRWorkingThread(OCRSingtonsPackages* pack,int index, QObject* parent = nullptr)
        :QThread(parent), taskPack(pack), index(index){}

signals:
    void finishWork(OCRSingtonsPackages* work);
protected:
    void run() override;

private:
    OCRSingtonsPackages* taskPack = nullptr;
    int index = 0;
};


class OCRPackagePrivate : public QObject
{
    Q_OBJECT;
public:
    enum class ErrorState{
        NO_ERROR,
        // config ERROR
        NO_EXECUTABLE,
        NO_SAVING_DIR,

        EMPTY_TASK,
        TASK_ALREADY_DEPATCH
    } error = ErrorState::NO_ERROR;

    enum class SupportLanguage{
        CHINESE,
        ENGLISH,
    };

    enum class Working_State{
        NO_START,
        STARTING,
        FINISH
    } working_state = OCRPackagePrivate::Working_State::NO_START;

    OCRPackagePrivate(QObject* parent = nullptr);
    OCRPackagePrivate(const OCRPackagePrivate&) = delete;
    const OCRPackagePrivate& operator=(const OCRPackagePrivate&) = delete;

    ~OCRPackagePrivate();

    void            setLanguage(SupportLanguage l){language = l;}
    SupportLanguage getLanguage(){return language;}
    void setCORE(QString path){this->exePath = path;}
    void addPic(QString pic){picLists.push_back(pic);}
    bool removePic(QString pic){return picLists.removeOne(pic);}
    void setResDir(QString dir){this->resultDir = dir;}
    bool startTasks();
    bool checkBasic();
    bool checkVadility();
    QStringList getResults(){return this->readResult;}

    bool cleanTasksAndThread();
    bool cleanAllPicsAndTasksThreads();
signals:
    // finish and ready signals are registered for the topper level
    void finish(int index);

    void ready(int index);

    void generateResult(); // TO readEachPackInfo()

    void finishAll(); // After reading signals

    void errorOccur();

private slots:

    void addFinishIndex(OCRSingtonsPackages* work); // Match the finishWork

    void readEachPackInfo();

private:
    // Path of the tessaract.exe
    QString                                         exePath;
    // Path of the place gonna save
    QString                                         resultDir;
    // Path of the pics waiting to be detected
    QStringList                                     picLists;
    // Wrapped OCR Package
    QList<OCRSingtonsPackages*>                     taskLists;
    // Threads working to get the execute
    QList<OCRWorkingThread*>                        workingThreads;
    // Current support Language
    SupportLanguage                                 language = SupportLanguage::CHINESE;
    // Packages of detections results
    QList<OCR_DetectInfo*>                          finished;
    // the strings
    QStringList                                     readResult;
    void initConnections();
    void releaseTaskLists();
    void releaseThread();
    bool constructTasks();

    // Reminder to the topper level
    void emitReady(int index);
    void emitFinish(int index);

    void sortTheOCRLists(){
        std::sort(finished.begin(), finished.end(),
        [](OCR_DetectInfo* a1, OCR_DetectInfo* a2)->bool{return a1->getIndex() < a2->getIndex();});
    }

    void setCurrentState(Working_State st){working_state = st;};
};




#endif // OCRPACKAGEPRIVATE_H
