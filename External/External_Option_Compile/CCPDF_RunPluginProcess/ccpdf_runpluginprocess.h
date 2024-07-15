#ifndef CCPDF_RUNPLUGINPROCESS_H
#define CCPDF_RUNPLUGINPROCESS_H
#include <QObject>
#include "CCPDF_Global.h"
class QProcess;

class CCPDF_RunPluginProcess : public QObject
{
    Q_OBJECT
signals:
    void                        finish();
public:

    enum class CurrentSupportType{
        TRANSLATION
    };

    enum class RunningError{
        NO_ERROR,
        NO_READ_FILE_EXSITS,
        NO_EXEC_FOUND
    } e {RunningError::NO_ERROR};

protected:
    explicit                    CCPDF_RunPluginProcess(QObject *parent = nullptr);
    DISABLE_COPY(CCPDF_RunPluginProcess);
    void                        setProcess(const QString& atWhere);
    void                        setfetchResultAt(const QString& atWhere);
    void                        runThis();
    CurrentSupportType          type;
    QString                     result;
    QString                     execPath;
    QString                     fetchResFile;
private slots:
    void                        fetchResult();

};

#endif // CCPDF_RUNPLUGINPROCESS_H
