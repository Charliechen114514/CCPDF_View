#include "ccpdf_historicalrecordhelper.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <CCPDF_Utils/ccpdf_fileutils.h>

static inline Plugin_Info* parsePlugin(QJsonObject& obj)
{
    if(obj.contains(Plugin_Info::Common_Key::LOAD_KEY))
    {
        auto res = obj.take(Plugin_Info::Common_Key::LOAD_KEY);
        if(res.isString())
        {
            QString check = res.toString();
            if(check == Plugin_Info::LoadMethod::Dll)
                return new Plugin_DLLInfo(obj);
            else if(check == Plugin_Info::LoadMethod::Exe)
                return new Plugin_ExeInfo(obj);
        }
    }
    return nullptr;
}


bool CCPDF_HistoricalRecordHelper::readPDF_HistoricalRecord()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(PDF_Info_LoggerPath))
    {
        e.e = HistError::Error::LoggerPath_Missing;
        return false;
    }
    QString read = CCPDF_FileUtils::File_ReadWrite::readFile(PDF_Info_LoggerPath);
    loadAccordingReading(read);
    return true;
}

bool CCPDF_HistoricalRecordHelper::setPDF_InfoLoggerPath(QString where)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(where))
    {
        this->PDF_Info_LoggerPath = where;
        return CCPDF_FileUtils::FileUtils::createFileAnyWay(where);
    }
    this->PDF_Info_LoggerPath = where;
    return true;
}

void CCPDF_HistoricalRecordHelper::addPDF_Info_Record(const PDF_Info_Historical_Record &path)
{
    if(!pdf_info_records.contains(path.pdf_Path)){
        pdf_info_records.insert(path.pdf_Path, path);
    }
}

void CCPDF_HistoricalRecordHelper::remove_Info_record(const PDF_Path path)
{
    if(pdf_info_records.contains(path)){
        pdf_info_records.remove(path);
    }
}

void CCPDF_HistoricalRecordHelper::update_target_Info_record(const PDF_Path path, const PDF_Info_Historical_Record &rec)
{
    if(pdf_info_records.contains(path)){
        pdf_info_records.insert(path, rec);
    }
}

bool CCPDF_HistoricalRecordHelper::writePDF_HistoricalRecord()
{
    qDebug() << "Write PDF Records";
    QJsonArray arr;
    for(auto& each_record : pdf_info_records)
    {
        QJsonValue each_value(each_record.generateJsonObject());
        arr.push_back(each_value);
    }
    QJsonDocument   doc;
    QJsonObject     arr_obj;
    arr_obj.insert(MaintainKey::PDF_RECORD, arr);
    doc.setObject(arr_obj);

    QString final_str = doc.toJson();
    return CCPDF_FileUtils::File_ReadWrite::writeFile(final_str, PDF_Info_LoggerPath);
}


void CCPDF_HistoricalRecordHelper::loadAccordingReading(QString& strings)
{
    QJsonDocument doc;
    QJsonParseError err;
    doc = doc.fromJson(strings.toUtf8(), &err);
    if(!doc.isNull() && err.error == QJsonParseError::NoError)
    {
        QJsonObject arr_obj = doc.object();
        if(arr_obj.contains(MaintainKey::PDF_RECORD)){
            QJsonValue v = arr_obj.take(MaintainKey::PDF_RECORD);
            if(v.isArray()){
                QJsonArray arr = v.toArray();
                for(const auto& each : arr)
                {
                    if(each.isObject())
                    {
                        auto obj = each.toObject();
                        auto new_record = PDF_Info_Historical_Record(obj);
                        pdf_info_records.insert(new_record.pdf_Path, new_record);
                    }
                }
            }
        }
    }
}

bool    CCPDF_Other_Simple_Server_HistoricalHelper::readPDF_HistoricalRecord()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(PDF_Info_LoggerPath))
    {
        e.e = HistError::Error::LoggerPath_Missing;
        return false;
    }
    QString read = CCPDF_FileUtils::File_ReadWrite::readFile(PDF_Info_LoggerPath);
    loadAccordingReading(read);
    return true;
}

bool    CCPDF_Other_Simple_Server_HistoricalHelper::writePDF_HistoricalRecord()
{
    qDebug() << "Write Simple Server Record";
    QJsonArray arr;
    for(auto& each_record : records)
    {
        QJsonValue each_value(each_record->generateJsonObject());
        arr.push_back(each_value);
    }
    QJsonDocument   doc;
    QJsonObject     arr_obj;
    arr_obj.insert(MainTainKey::PDF_SIMPLE_SERVER, arr);
    doc.setObject(arr_obj);

    QString final_str = doc.toJson();
    return CCPDF_FileUtils::File_ReadWrite::writeFile(final_str, PDF_Info_LoggerPath);
}

void    CCPDF_Other_Simple_Server_HistoricalHelper::analysisObject(const QJsonObject& obj)
{
    if(obj.contains(BookLibrary_Record::BookLibrary_Record_KeyName::BOOK_LIB_READ_DEF))
    {
        auto new_obj = obj;
        this->records.push_back(std::make_unique<BookLibrary_Record>(new_obj));
        currentOwns << PDF_SimpleServer_Record::SimpleSercerRecord::BOOKLIB_INFO;
    }
}

void    CCPDF_Other_Simple_Server_HistoricalHelper::loadAccordingReading(QString& strings)
{
    QJsonDocument doc;
    QJsonParseError err;
    doc = doc.fromJson(strings.toUtf8(), &err);
    if(!doc.isNull() && err.error == QJsonParseError::NoError)
    {
        QJsonObject arr_obj = doc.object();
        if(arr_obj.contains(MainTainKey::PDF_SIMPLE_SERVER)){
            QJsonValue v = arr_obj.take(MainTainKey::PDF_SIMPLE_SERVER);
            if(v.isArray()){
                QJsonArray arr = v.toArray();
                for(const auto& each : arr)
                {
                    if(each.isObject())
                    {
                        auto obj = each.toObject();
                        analysisObject(obj);
                    }
                }
            }
        }
    }
}

bool    CCPDF_Other_Simple_Server_HistoricalHelper::setPDF_InfoLoggerPath(QString where)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(where))
    {
        this->PDF_Info_LoggerPath = where;
        return CCPDF_FileUtils::FileUtils::createFileAnyWay(where);
    }
    this->PDF_Info_LoggerPath = where;
    return true;
}

BookLibrary_Record* CCPDF_Other_Simple_Server_HistoricalHelper::
bookRecord() const
{
    for(auto& each : records)
    {
        if(each->simpleType() == PDF_SimpleServer_Record::SimpleSercerRecord::BOOKLIB_INFO)
        {
            auto editTarget = dynamic_cast<BookLibrary_Record*>(each.get());
            return editTarget;
        }
    }
    return nullptr;
}

void    CCPDF_Other_Simple_Server_HistoricalHelper::
setRecord(PDF_SimpleServer_Record::SimpleSercerRecord t, const PDF_SimpleServer_Record& record)
{
    if(ownsServer(t))
    {
        for(auto& each : records)
        {
            if(each->simpleType() == t)
            {
                auto viewAsTarget = dynamic_cast<const BookLibrary_Record*>(&record);
                auto editTarget = dynamic_cast<BookLibrary_Record*>(each.get());
                if(!viewAsTarget)
                    return;
                editTarget->libPath = viewAsTarget->libPath;
            }
        }
    }
    else
    {
        switch(t)
        {
        case PDF_SimpleServer_Record::SimpleSercerRecord::BOOKLIB_INFO:
        {
            auto viewAsTarget = dynamic_cast<const BookLibrary_Record*>(&record);
            if(!viewAsTarget)
                return;
            this->records.push_back(std::make_unique<BookLibrary_Record>(*viewAsTarget));
        }break;
        }
    }
}

Plugin_HistoricalHelper::Plugin_HistoricalHelper()
{
    for(const auto& each : SupportPluginInfotype::RAW_SUPPORTIVE)
        if(!QString(each).isEmpty())
            supportives << each;
}

void Plugin_HistoricalHelper::loadAccordingReading(QString& strings)
{
    QJsonDocument doc;
    QJsonParseError err;
    doc = doc.fromJson(strings.toUtf8(), &err);
    if(!doc.isNull() && err.error == QJsonParseError::NoError)
    {
        QJsonObject arr_obj = doc.object();
        if(arr_obj.contains(MaintainKey::PLUGIN_RECORD)){
            QJsonValue v = arr_obj.take(MaintainKey::PLUGIN_RECORD);
            if(v.isArray()){
                QJsonArray arr = v.toArray();
                for(const auto& each : arr)
                {
                    if(each.isObject())
                    {
                        auto obj = each.toObject();
                        auto res = parsePlugin(obj);
                        if(res)
                            infos.push_back(std::unique_ptr<Plugin_Info>(res));
                    }
                }
            }
        }
    }
}

bool Plugin_HistoricalHelper::readPluginInfo_HistoricalRecord()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(PDF_Info_LoggerPath))
    {
        e.e = HistError::Error::LoggerPath_Missing;
        return false;
    }
    QString read = CCPDF_FileUtils::File_ReadWrite::readFile(PDF_Info_LoggerPath);
    loadAccordingReading(read);
    return true;
}

bool Plugin_HistoricalHelper::writePluginInfo_HistoricalRecord()
{
    qDebug() << "Write Plugins";
    QJsonArray arr;
    for(auto& each_record : infos)
    {
        QJsonValue each_value(each_record->generateJsonObject());
        arr.push_back(each_value);
    }
    QJsonDocument   doc;
    QJsonObject     arr_obj;
    arr_obj.insert(MaintainKey::PLUGIN_RECORD, arr);
    doc.setObject(arr_obj);

    QString final_str = doc.toJson();
    return CCPDF_FileUtils::File_ReadWrite::writeFile(final_str, PDF_Info_LoggerPath);
}

bool Plugin_HistoricalHelper::addPluginConfig(const Plugin_Info* i)
{
    if(i->inner_type() == Plugin_Info::Type::DLL)
    {
        const Plugin_DLLInfo* dll = dynamic_cast<const Plugin_DLLInfo*>(i);
        auto res = fetchAccordingType(dll->PluginType.toStdString().c_str());
        auto _res = dynamic_cast<const Plugin_DLLInfo*>(res);
        if(!_res){
            Plugin_DLLInfo* new_dll = new Plugin_DLLInfo(*dll);
            infos.push_back(std::unique_ptr<Plugin_DLLInfo>(new_dll));
            return true;
        }else{
            updateConfig(dll);
            return false;
        }
    }
    else
    {
        const Plugin_ExeInfo* exe = dynamic_cast<const Plugin_ExeInfo*>(i);
        auto res = fetchAccordingType(exe->PluginType.toStdString().c_str());
        auto _res = dynamic_cast<const Plugin_DLLInfo*>(res);
        if(!_res){
            Plugin_ExeInfo* new_exe = new Plugin_ExeInfo(*exe);
            infos.push_back(std::unique_ptr<Plugin_ExeInfo>(new_exe));
            return true;
        }else{
            updateConfig(exe);
            return false;
        }
    }
    return false;
}

bool Plugin_HistoricalHelper::updateConfig(const Plugin_Info* r){
    if(r && r->inner_type() == Plugin_Info::EXE)
    {
        auto res = dynamic_cast<const Plugin_ExeInfo*>(r);
        for(auto& each : infos)
        {
            Plugin_ExeInfo* exe = dynamic_cast<Plugin_ExeInfo*>(each.get());
            if(!exe)
                continue;
            if(exe->PluginType == res->PluginType)
            {
                exe->exe = res->exe;
                exe->readAt = res->readAt;
                return true;
            }
        }
    }
    else
    {
        auto res = dynamic_cast<const Plugin_DLLInfo*>(r);
        if(!res)
            return false;
        for(auto& each : infos)
        {
            Plugin_DLLInfo* dll = dynamic_cast<Plugin_DLLInfo*>(each.get());
            if(!dll)
                continue;
            if(dll->PluginType == res->PluginType)
            {
                dll->PluginDLLPath = res->PluginDLLPath;
                dll->PluginDependencyDir = dll->PluginDependencyDir;
                return true;
            }
        }
    }
    return false;
}


const Plugin_Info* Plugin_HistoricalHelper::fetchAccordingType(const char* type){
    for(const auto& each : infos)
    {
        if(!each)
            continue;
        if(each->inner_type() == Plugin_Info::EXE)
        {
            const Plugin_ExeInfo* exe = dynamic_cast<const Plugin_ExeInfo*>(each.get());
            if(exe->PluginType == type)
                return exe;
        }
        else{
            const Plugin_DLLInfo* dll = dynamic_cast<const Plugin_DLLInfo*>(each.get());
            if(dll->PluginType == type)
                return dll;
        }
    }
    return nullptr;
}


bool Plugin_HistoricalHelper::setPluginInfo_LoggerPath(QString where)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(where))
    {
        this->PDF_Info_LoggerPath = where;
        return CCPDF_FileUtils::FileUtils::createFileAnyWay(where);
    }
    this->PDF_Info_LoggerPath = where;
    return true;
}



bool ThemeHistoricalHelper::readPluginInfo_HistoricalRecord()
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(PDF_Info_LoggerPath))
    {
        e.e = HistError::Error::LoggerPath_Missing;
        return false;
    }
    QString read = CCPDF_FileUtils::File_ReadWrite::readFile(PDF_Info_LoggerPath);
    loadAccordingReading(read);
    return true;
}

bool ThemeHistoricalHelper::writePluginInfo_HistoricalRecord()
{
    qDebug() << "Write Themes";
    QJsonArray arr;
    for(auto& each_record : themeRecord)
    {
        QJsonValue each_value(each_record.generateJsonObject());
        arr.push_back(each_value);
    }
    QJsonDocument   doc;
    QJsonObject     arr_obj;
    arr_obj.insert(MaintainKey::THEME_RECORD, arr);
    doc.setObject(arr_obj);

    QString final_str = doc.toJson();
    return CCPDF_FileUtils::File_ReadWrite::writeFile(final_str, PDF_Info_LoggerPath);
}

bool ThemeHistoricalHelper::setPluginInfo_LoggerPath(QString where)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(where))
    {
        this->PDF_Info_LoggerPath = where;
        return CCPDF_FileUtils::FileUtils::createFileAnyWay(where);
    }
    this->PDF_Info_LoggerPath = where;
    return true;
}

void ThemeHistoricalHelper::loadAccordingReading(QString& strings)
{
    QJsonDocument doc;
    QJsonParseError err;
    doc = doc.fromJson(strings.toUtf8(), &err);
    if(!doc.isNull() && err.error == QJsonParseError::NoError)
    {
        QJsonObject arr_obj = doc.object();
        if(arr_obj.contains(MaintainKey::THEME_RECORD)){
            QJsonValue v = arr_obj.take(MaintainKey::THEME_RECORD);
            if(v.isArray()){
                QJsonArray arr = v.toArray();
                for(const auto& each : arr)
                {
                    if(each.isObject())
                    {
                        auto res = each.toObject();
                        this->themeRecord.push_back(ThemeRecord(res));
                    }
                }
            }
        }
    }
}
QString ThemeHistoricalHelper::getStyleSheet(const QString& fileName)
{
    for(const auto& each : themeRecord)
    {
        if(each.themeQRC == fileName && CCPDF_FileUtils::FileUtils::isFileExsits(each.themeQRC))
        {
            return CCPDF_FileUtils::File_ReadWrite::readFile(each.themeQRC);
        }
    }
    return {};
}

QString ThemeHistoricalHelper::getInUsedOne()
{
    if(!themeRecord.empty() && CCPDF_FileUtils::FileUtils::
        isFileExsits(themeRecord.last().themeQRC))
    {
        return CCPDF_FileUtils::File_ReadWrite::readFile(themeRecord.last().themeQRC);
    }
    return {};
}

void ThemeHistoricalHelper::enRecord(const QString& filePath)
{
    const auto _paths = paths();
    if(!_paths.contains(filePath))
        themeRecord.push_back({filePath});
}

QStringList ThemeHistoricalHelper::paths()
{
    QStringList l;
    for(const auto& each : themeRecord)
    {
        l << each.themeQRC;
    }
    return l;
}

void ThemeHistoricalHelper::deRecord(const QString& name)
{
    int idx = 0;
    for(const auto& each : themeRecord)
    {
        if(each.themeQRC == name)
        {
            themeRecord.removeAt(idx);
        }
        idx++;
    }
}








