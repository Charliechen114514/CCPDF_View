#include "ccpdf_logger.h"
#include <QDateTime>

CCPDF_Logger::LoggerError::Error CCPDF_Logger::LoggerError::translate(QFile::FileError f)
{
    switch(f){
        case QFileDevice::OpenError:
            return Error::NOT_EXSIT_FILE;
        case QFileDevice::WriteError:
            return Error::WRITE_ERROR;
        case QFileDevice::PermissionsError:
            return Error::WRITE_PERMISSION_DENIED;
        case QFileDevice::ReadError:
        case QFileDevice::FatalError:
        case QFileDevice::ResourceError:
        case QFileDevice::NoError:
        case QFileDevice::AbortError:
        case QFileDevice::TimeOutError:
        case QFileDevice::UnspecifiedError:
        case QFileDevice::RemoveError:
        case QFileDevice::RenameError:
        case QFileDevice::PositionError:
        case QFileDevice::ResizeError:
        case QFileDevice::CopyError:
            return Error::OTHER_OPEN_FAILED;
    }
    return Error::OTHER_OPEN_FAILED;
}

CCPDF_Logger::CCPDF_Logger(const QString& filePath)
    :loggerFile(filePath)
{
    if(!loggerFile.open(QIODevice::WriteOnly)){
        e.setError(loggerFile.error());
    }

}

bool CCPDF_Logger::writePrefix(LoggerLevel::Level l)
{
    return loggerFile.write(LOGING_PREFIX(LoggerLevel::string(l)).toStdString().c_str());
}

bool CCPDF_Logger::logging(QString& log, LoggerLevel::Level l)
{
    if(!shell_log)
        return false;
    if(!fine())
        return false;
    if(!level.shouldLog(l))
        return false;

    writePrefix(l);
    loggerFile.write((log + "\n").toStdString().c_str());

    return true;
}

CCPDF_Logger::~CCPDF_Logger()
{
    debug("Logger file close");
    loggerFile.close();
}





