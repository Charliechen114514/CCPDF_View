#ifndef CCPDF_LOGGER_H
#define CCPDF_LOGGER_H
#include <QString>
#include <QFile>
#include <QDebug>
#ifndef LOGING_PREFIX   // No Pre-defined yet

#ifndef NO_TIME
#define LOGING_PREFIX(LEVEL) QString("[%1]: [%2]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(LEVEL)
#else
#define LOGING_PREFIX(LEVEL) QString("[%1]:").arg(LEVEL)
#endif
#endif

class CCPDF_Logger
{
public:
    CCPDF_Logger() = delete;
    CCPDF_Logger(const CCPDF_Logger&) = delete;
    const CCPDF_Logger& operator=(const CCPDF_Logger&) = delete;
    CCPDF_Logger(const QString& filePath);
    ~CCPDF_Logger();
    struct LoggerLevel{
        enum class Level{
            Debug,
            Info,
            Warning,
            Critical,
            Error
        } currentLevel = Level::Info;
        static short    toShort(Level l){return static_cast<short>(l);}
        static QString  string(Level l){
            switch (l) {
            case Level::Debug:
                return "Debug";
            case Level::Info:
                return "Info";
            case Level::Warning:
                return "Warning";
            case Level::Critical:
                return "Critical";
            case Level::Error:
                return "Error";
            }
            return "Unknown!";
        }
        short           toShort(){return toShort(currentLevel);}
        bool            shouldLog(Level l){return toShort(l) >= toShort();}

    };

    struct LoggerError{
        enum class Error{
            NO_ERROR,
            NOT_EXSIT_FILE,
            WRITE_PERMISSION_DENIED,
            WRITE_ERROR,
            OTHER_OPEN_FAILED,
        } e {Error::NO_ERROR};
        static Error    translate(QFile::FileError f);
        void            setError(Error e){this->e = e;}
        void            setError(QFile::FileError f){this->e = translate(f);};
        static QString  errorString(Error e){
            switch(e)
            {
            case Error::NO_ERROR:
                return "No Error";
            case Error::NOT_EXSIT_FILE:
                return "Target File not exists!";
            case Error::WRITE_PERMISSION_DENIED:
                return "writing permission denied";
            case Error::WRITE_ERROR:
                return "write error";
            case Error::OTHER_OPEN_FAILED:
                return "other unknown error!";
            }
            return "other unknown error!";
        }
        QString         errorString(){return errorString(e);}
    };
    bool                        setShell_log(bool shell_log){this->shell_log = shell_log; return shell_log;;}
    bool                        debug(QString debug){return logging(debug, LoggerLevel::Level::Debug);}
    bool                        info(QString info){return logging(info, LoggerLevel::Level::Info);};
    bool                        warning(QString warning){return logging(warning, LoggerLevel::Level::Warning);}
    bool                        critical(QString critical){return logging(critical, LoggerLevel::Level::Critical);}
    bool                        error(QString error){return logging(error, LoggerLevel::Level::Error);}
    void                        setLoggingLevel(LoggerLevel::Level l){level.currentLevel = l;}
    LoggerError::Error          getError(){return e.e;}
    QString                     errorString(){return e.errorString();}
    bool                        fine(){return e.e == LoggerError::Error::NO_ERROR;}
private:
    bool            logging(QString& log, LoggerLevel::Level l);
    bool            writePrefix(LoggerLevel::Level l);
    bool            shell_log = true;
    LoggerLevel     level;
    QFile           loggerFile;
    LoggerError     e;
};

#endif // CCPDF_LOGGER_H
