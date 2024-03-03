#ifndef OCRPACKAGE_H
#define OCRPACKAGE_H
#include "qobject.h"
#include <QStringList>
class OCRPackagePrivate;

#if defined(OCRPACKAGE_LIBRARY)
# define OCRPACKAG_EXPORT Q_DECL_EXPORT
#else
# define OCRPACKAG_EXPORT
#endif


class OCRPACKAG_EXPORT OCRPackage : public QObject
{
    Q_OBJECT; // enable signals
public:
    using TaskIndex = int;
    enum class ErrorState{
        NO_ERROR,
        // initializal error
        CORE_UNINITED,
        // config error
        NO_OCR_EXE_PATH,
        NO_SAVING_DIR_PATH,
        NO_TASK_BUT_START,
        // running time error
        TASK_ALREADY_DEPATCH,

        // UNKNOWN
        Unknown_Error,
    } error = OCRPackage::ErrorState::NO_ERROR;

    QString errorString();
    const QStringList supportedLanguageStrings{"汉语", "英语"};
    enum class LanguageOCR{
        CHINESE,
        ENGLISH
    };

    enum class ConfigMethod{
        BY_HAND_INPUT,
        BY_DIALOG_CONFIG
    };

    explicit OCRPackage(QObject* parent = nullptr);
    const OCRPackage& operator=(const OCRPackage&) = delete;
    OCRPackage(const OCRPackage&) = delete;
    ~OCRPackage();

    void        setLanguage(LanguageOCR l);
    LanguageOCR getLanguage();

    QStringList getSupportedLanguageStrings();
    bool configOCRExecutable(QString Path);
    bool configOCRSavingDirectory(QString Path);
    bool tryifIsRunnable(); // no error will be set!
    bool checkMissionStartAble(); // error will be set
    bool addSinglePic(QString pic);
    bool addMutltiPics(QStringList pics);
    bool removePicsTarget(QString pic);
    bool configExecutableOCRPath(QString path);
    bool configSavingDirPath(QString path);
    bool startRecognize();

    bool clearPackages();

    QStringList& getResult(){return results;}
    // for current state
signals:
    // emit the signals when a task is ready
    void readyTask(TaskIndex index);
    // emit the signals when a task is finish
    void finishTask(TaskIndex index);
    // emit the finish all
    void finishAll();
protected slots:
    void receiveReady(TaskIndex indexReady);
    void receiveFinish(TaskIndex indexFinish);
    void receiveFinishAll();
    void checkAndUpdateError();
private:
    OCRPackagePrivate*      privateCore = nullptr;
    QStringList             results;
    void                    initCore();
    void                    initConnections();
    bool                    isPackagePTRAvaible();
};

#endif // OCRPACKAGE_H
