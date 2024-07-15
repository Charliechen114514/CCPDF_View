#ifndef CCPDF_HISTORICALRECORDHELPER_H
#define CCPDF_HISTORICALRECORDHELPER_H
#include <QString>
#include "CCPDF_Global.h"
#include "External/CCPDF_Plugin_Supports.h"
#include "CCPDF_Historical/Historical/historical_record.h"
class CCPDF_HistoricalRecordHelper
{
public:
    using PDF_Path = QString;

    enum class History_Type{
        PDF_Info
    };

    struct HistError{
        enum class Error{
            NO_ERROR,
            LoggerPath_Missing
        } e{Error::NO_ERROR};
        QString errorString(){
            switch (e) {
            case Error::LoggerPath_Missing:
                return "日志记录文件丢失！请检查路径！";
            case Error::NO_ERROR:
                break;
            }
            return "Unknown Error";
        }
    };

    struct MaintainKey{
        static constexpr const char* PDF_RECORD = "pdf_record";
    };

    CCPDF_HistoricalRecordHelper() = default;
    ~CCPDF_HistoricalRecordHelper(){writePDF_HistoricalRecord();}
    DISABLE_COPY(CCPDF_HistoricalRecordHelper);
    bool    readPDF_HistoricalRecord();
    bool    writePDF_HistoricalRecord();
    bool    setPDF_InfoLoggerPath(QString where);
    void    addPDF_Info_Record(const PDF_Info_Historical_Record& path);
    PDF_Info_Historical_Record  record(const QString& path){return pdf_info_records.value(path);};
    void    remove_Info_record(const PDF_Path path);
    void    update_target_Info_record(const PDF_Path path,
                                   const PDF_Info_Historical_Record &rec);
    QString getPDF_InfoLoggerPath(){return PDF_Info_LoggerPath;}
    QList<PDF_Info_Historical_Record>   getRecords(){return pdf_info_records.values();}
    bool    isPdfInAlready(const QString& path) const {return pdf_info_records.keys().contains(path);};
    QList<PDF_Info_Historical_Record>   current_records() const{return pdf_info_records.values();}
    QList<PDF_Path>                     current_pdf_paths() const {return pdf_info_records.keys();}

private:
    void                                        loadAccordingReading(QString& strings);
    QMap<PDF_Path, PDF_Info_Historical_Record>  pdf_info_records;
    QString                                     PDF_Info_LoggerPath;
    HistError                                   e;
};

// Those who only serve one instancese do at here
class CCPDF_Other_Simple_Server_HistoricalHelper
{
public:
    CCPDF_Other_Simple_Server_HistoricalHelper() = default;
    ~CCPDF_Other_Simple_Server_HistoricalHelper(){writePDF_HistoricalRecord();}
    DISABLE_COPY(CCPDF_Other_Simple_Server_HistoricalHelper);
    struct HistError{
        enum class Error{
            NO_ERROR,
            LoggerPath_Missing
        } e{Error::NO_ERROR};
        QString errorString(){
            switch (e) {
            case Error::LoggerPath_Missing:
                return "日志记录文件丢失！请检查路径！";
            case Error::NO_ERROR:
                break;
            }
            return "Unknown Error";
        }
    };

    struct  MainTainKey{
        static constexpr const char*    PDF_SIMPLE_SERVER = "pdf_simple_server";
    };

    bool    readPDF_HistoricalRecord();
    bool    writePDF_HistoricalRecord();
    bool    setPDF_InfoLoggerPath(QString where);
    void    setRecord(PDF_SimpleServer_Record::SimpleSercerRecord t, const PDF_SimpleServer_Record& record);
    BookLibrary_Record*     bookRecord() const;
    void    analysisObject(const QJsonObject& obj);
    bool    ownsServer(PDF_SimpleServer_Record::SimpleSercerRecord t)
                            {return currentOwns.contains(t);}
private:
    void                                            loadAccordingReading(QString& strings);
    QList<PDF_SimpleServer_Record::SimpleSercerRecord>
                                                    currentOwns;
    QList<std::shared_ptr<PDF_SimpleServer_Record>> records;
    QString                                         PDF_Info_LoggerPath;
    HistError                                       e;
};

class Plugin_HistoricalHelper
{
public:
    struct HistError{
        enum class Error{
            NO_ERROR,
            LoggerPath_Missing
        } e{Error::NO_ERROR};
        QString errorString(){
            switch (e) {
            case Error::LoggerPath_Missing:
                return "日志记录文件丢失！请检查路径！";
            case Error::NO_ERROR:
                break;
            }
            return "Unknown Error";
        }
    };
    struct MaintainKey{
        static constexpr const char* PLUGIN_RECORD = "Plugin_Record";
    };

    struct SupportPluginInfotype{
        static constexpr short CHECK_SUP_MAX  = 2;
        static constexpr const char* RAW_SUPPORTIVE[CHECK_SUP_MAX] = {
            _OCR_TESS,
            _TRANSLATION
        };
    };

    Plugin_HistoricalHelper();
    ~Plugin_HistoricalHelper(){writePluginInfo_HistoricalRecord();}
    DISABLE_COPY(Plugin_HistoricalHelper);
    bool    readPluginInfo_HistoricalRecord();
    bool    writePluginInfo_HistoricalRecord();
    bool    setPluginInfo_LoggerPath(QString where);
    bool    ownsSupportiveInfoType(const char* type){return QString(type).isEmpty()? false : supportives.contains(type);}
    bool    addPluginConfig(const Plugin_Info* i);
    bool    updateConfig(const Plugin_Info* r);
    const Plugin_Info* fetchAccordingType(const char* type);
private:
    void    loadAccordingReading(QString& strings);
    QList<std::shared_ptr<Plugin_Info>>         infos;
    QString                                     PDF_Info_LoggerPath;
    HistError                                   e;
    QStringList                                 supportives;
};

class ThemeHistoricalHelper
{
public:
    struct HistError{
        enum class Error{
            NO_ERROR,
            LoggerPath_Missing
        } e{Error::NO_ERROR};
        QString errorString(){
            switch (e) {
            case Error::LoggerPath_Missing:
                return "日志记录文件丢失！请检查路径！";
            case Error::NO_ERROR:
                break;
            }
            return "Unknown Error";
        }
    };
    struct MaintainKey{
        static constexpr const char* THEME_RECORD = "Theme_record";
    };
    ThemeHistoricalHelper() = default;
    ~ThemeHistoricalHelper(){writePluginInfo_HistoricalRecord();}
    bool                                readPluginInfo_HistoricalRecord();
    bool                                writePluginInfo_HistoricalRecord();
    bool                                setPluginInfo_LoggerPath(QString where);
    QString                             getStyleSheet(const QString& fileName);
    QString                             getInUsedOne();
    void                                enRecord(const QString& filePath);
    void                                deRecord(const QString& name);
    QStringList                         paths();
private:
    HistError                           e;
    void                                loadAccordingReading(QString& strings);
    QList<ThemeRecord>                  themeRecord;
    QString                             PDF_Info_LoggerPath;
};

#endif // CCPDF_HISTORICALRECORDHELPER_H
