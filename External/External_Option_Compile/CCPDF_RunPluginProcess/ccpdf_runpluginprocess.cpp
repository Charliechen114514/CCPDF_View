#include <QProcess>
#include <QApplication>
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "ccpdf_runpluginprocess.h"
#include <QStringConverter>
#include <QStringDecoder>
CCPDF_RunPluginProcess::CCPDF_RunPluginProcess(QObject *parent)
    : QObject{parent}
{}

void CCPDF_RunPluginProcess::
setProcess(const QString& atWhere)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(atWhere))
    {
        e = RunningError::NO_EXEC_FOUND;
    }
    execPath = atWhere;
}

void CCPDF_RunPluginProcess::
setfetchResultAt(const QString& atWhere)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(atWhere))
    {
        e = RunningError::NO_READ_FILE_EXSITS;
    }
    fetchResFile = atWhere;

}

void CCPDF_RunPluginProcess::
runThis()
{
    QProcess* processRunning = new QProcess(this);
    connect(processRunning, &QProcess::finished,
            this, &CCPDF_RunPluginProcess::fetchResult);
    QString exeWhere = CCPDF_FileUtils::PathUtils::atDir(execPath);
    processRunning->setWorkingDirectory(exeWhere);
    processRunning->start(execPath, {fetchResFile});
}

void CCPDF_RunPluginProcess::
fetchResult()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(fetchResFile))
    {
        e = RunningError::NO_READ_FILE_EXSITS;
    }
    auto res = CCPDF_FileUtils::File_ReadWrite::readFile(fetchResFile);
    this->result = QString::fromUtf8(res);
    emit finish();
}
