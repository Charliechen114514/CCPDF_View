#include <QJsonDocument>
#include "historical_record.h"

#define INIT_BY_OFFER_KEY_NAME_STR(KEY, VAR) \
    if(single_req.contains(KEY)){ \
    QJsonValue v = single_req.take(KEY); \
    if(v.isString()){ \
        VAR = v.toString(); \
    } \
}

#define INIT_BY_OFFER_KEY_NAME_INT(KEY, VAR) \
if(single_req.contains(KEY)){ \
        QJsonValue v = single_req.take(KEY); \
        if(v.isDouble()){ \
            VAR = v.toInt(); \
    } \
}

PDF_Info_Historical_Record::PDF_Info_Historical_Record(QJsonObject &single_req)
{
    type = InfoType::PDF_Info;
    INIT_BY_OFFER_KEY_NAME_STR(PDF_Info_Key_Name::PDF_PATH, pdf_Path);
    INIT_BY_OFFER_KEY_NAME_INT(PDF_Info_Key_Name::PDF_CUR_PAGE, current_page);
}

QJsonObject
PDF_Info_Historical_Record::generateJsonObject() const
{
    QJsonObject obj;
    obj.insert(PDF_Info_Key_Name::PDF_PATH, pdf_Path);
    obj.insert(PDF_Info_Key_Name::PDF_CUR_PAGE, current_page);
    return obj;
}


QString
PDF_Info_Historical_Record::generateWritableJsonText() const
{
    QJsonObject obj = generateJsonObject();
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson() + "\n";
}

BookLibrary_Record::BookLibrary_Record(QJsonObject &single_req)
{
    registerType();
    INIT_BY_OFFER_KEY_NAME_STR(BookLibrary_Record_KeyName::BOOK_LIB_READ_DEF, libPath);
}


QJsonObject
BookLibrary_Record::generateJsonObject() const
{
    QJsonObject obj;
    obj.insert(BookLibrary_Record_KeyName::BOOK_LIB_READ_DEF, libPath);
    return obj;
}

QString
BookLibrary_Record::generateWritableJsonText() const
{
    QJsonObject obj = generateJsonObject();
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson() + "\n";
}

Plugin_ExeInfo::Plugin_ExeInfo(QJsonObject &single_req)
{
    type = InfoType::PluginLoad_Info;
    t = EXE;
    INIT_BY_OFFER_KEY_NAME_STR(Plugin_Exe_Key_Name::PluginType, PluginType);
    INIT_BY_OFFER_KEY_NAME_STR(Plugin_Exe_Key_Name::PluginExe, exe);
    INIT_BY_OFFER_KEY_NAME_STR(Plugin_Exe_Key_Name::PluginRead, readAt);
}

QJsonObject Plugin_ExeInfo::generateJsonObject() const
{
    QJsonObject obj;
    obj.insert(Common_Key::LOAD_KEY, LoadM);
    obj.insert(Plugin_Exe_Key_Name::PluginType, PluginType);
    obj.insert(Plugin_Exe_Key_Name::PluginExe, exe);
    obj.insert(Plugin_Exe_Key_Name::PluginRead, readAt);
    return obj;
}
QString Plugin_ExeInfo::generateWritableJsonText() const
{
    QJsonObject obj = generateJsonObject();
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson() + "\n";
}



Plugin_DLLInfo::Plugin_DLLInfo(QJsonObject &single_req)
{
    type = InfoType::PluginLoad_Info;
    t = DLL;
    INIT_BY_OFFER_KEY_NAME_STR(Plugin_Info_Key_Name::PluginType, PluginType);
    INIT_BY_OFFER_KEY_NAME_STR(Plugin_Info_Key_Name::PluginDependencyDir, PluginDependencyDir);
    INIT_BY_OFFER_KEY_NAME_STR(Plugin_Info_Key_Name::PluginDLLPath, PluginDLLPath);
}

QJsonObject
Plugin_DLLInfo::generateJsonObject() const
{
    QJsonObject obj;
    obj.insert(Common_Key::LOAD_KEY, LoadM);
    obj.insert(Plugin_Info_Key_Name::PluginType, PluginType);
    obj.insert(Plugin_Info_Key_Name::PluginDependencyDir, PluginDependencyDir);
    obj.insert(Plugin_Info_Key_Name::PluginDLLPath, PluginDLLPath);
    return obj;
}

QString
Plugin_DLLInfo::generateWritableJsonText() const
{
    QJsonObject obj = generateJsonObject();
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson() + "\n";
}

ThemeRecord::ThemeRecord(QJsonObject& single_req)
{
    type = InfoType::ThemeRecordInfo;
    INIT_BY_OFFER_KEY_NAME_STR(ThemeRecordKey::ThemeQRC, themeQRC);
}

QJsonObject ThemeRecord::generateJsonObject() const
{
    QJsonObject obj;
    obj.insert(ThemeRecordKey::ThemeQRC, themeQRC);
    return obj;
}

QString     ThemeRecord::generateWritableJsonText() const
{
    QJsonObject obj = generateJsonObject();
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson() + "\n";
}



