#ifndef HISTORICAL_RECORD_H
#define HISTORICAL_RECORD_H
#include <QString>
#include <QJsonObject>

struct Historical_Record
{
public:
    enum class InfoType{
        UNKNOWN,
        PDF_Info,
        NoteBookInfo,
        BookLibraryInfo,
        PluginLoad_Info,
        ThemeRecordInfo
    };
    InfoType            getParseType(){return type;}
    virtual QJsonObject generateJsonObject() const = 0;
    virtual QString     generateWritableJsonText()const  = 0;
protected:
    InfoType            type{InfoType::UNKNOWN};
};

struct PDF_Info_Historical_Record : Historical_Record
{
    PDF_Info_Historical_Record(QString pdf_path, int cur_page):pdf_Path(pdf_path), current_page(cur_page){type = InfoType::PDF_Info;}
    PDF_Info_Historical_Record(){type = InfoType::PDF_Info;}
    PDF_Info_Historical_Record(QJsonObject& single_req);

    struct PDF_Info_Key_Name{
        static constexpr const char* PDF_PATH = "PDF_Path";
        static constexpr const char* PDF_CUR_PAGE = "current_page";
    };

    QJsonObject generateJsonObject() const override;
    QString     generateWritableJsonText() const override;

    QString pdf_Path;
    int     current_page;
};


struct PDF_SimpleServer_Record :  Historical_Record
{
    enum class SimpleSercerRecord
    {
        BOOKLIB_INFO
    };
    struct  PDF_SimpleServer_Record_KeyName{
        static constexpr const char* PDF_SIMPLE_SERVER = "PDF_SimpleSercer";
    };
    SimpleSercerRecord      simpleType(){return simple_type;}
protected:
    SimpleSercerRecord      simple_type;
};



struct BookLibrary_Record : PDF_SimpleServer_Record
{
    struct BookLibrary_Record_KeyName{
        static constexpr const char* BOOK_LIB_READ_DEF = "book_lib_load_default";
    };

    BookLibrary_Record(QString lib_path):libPath(lib_path){registerType();}
    BookLibrary_Record(){registerType();}
    BookLibrary_Record(QJsonObject& single_req);
    BookLibrary_Record(const BookLibrary_Record& rec){registerType();libPath = rec.libPath;}
    QJsonObject generateJsonObject() const override;
    QString     generateWritableJsonText() const override;

    QString libPath;
protected:
    void registerType(){type = InfoType::BookLibraryInfo;simple_type = SimpleSercerRecord::BOOKLIB_INFO;}
};


struct Plugin_Info : Historical_Record
{
public:
    enum Type{
        EXE,
        DLL
    };
    virtual ~Plugin_Info() = default;
    struct Common_Key{
        static constexpr const char* LOAD_KEY = "Load_Key";
    };

    struct LoadMethod{
        static constexpr const char* Exe = "exe";
        static constexpr const char* Dll = "dll";
    };

    Type inner_type() const {return t;}
protected:
    Type t;

};


struct Plugin_ExeInfo : Plugin_Info
{
    Plugin_ExeInfo(QString _exePath, QString _readAt)
        :exe(_exePath), readAt(_readAt){type = InfoType::PluginLoad_Info;t = EXE;}
    Plugin_ExeInfo(){type = InfoType::PluginLoad_Info;t = EXE;}
    Plugin_ExeInfo(QJsonObject& single_req);
    ~Plugin_ExeInfo() = default;
    QJsonObject generateJsonObject() const override;
    QString     generateWritableJsonText() const override;
    struct Plugin_Exe_Key_Name{
        static constexpr const char* PluginRead = "ReadAt";
        static constexpr const char* PluginExe  = "ExecutionPath";
        static constexpr const char* PluginType = "PluginType";
    };
    const QString LoadM = LoadMethod::Exe;
    QString PluginType;
    QString exe;
    QString readAt;
};


struct Plugin_DLLInfo : Plugin_Info
{
    Plugin_DLLInfo(QString _PluginDependencyDir, QString _PluginDLLPath,
                QString _PluginType):
        PluginDependencyDir(_PluginDependencyDir),
        PluginDLLPath(_PluginDLLPath),PluginType(_PluginType)
    {type = InfoType::PluginLoad_Info;t = DLL;}
    Plugin_DLLInfo(){type = InfoType::PluginLoad_Info;t = DLL;}
    Plugin_DLLInfo(QJsonObject& single_req);
    ~Plugin_DLLInfo() = default;
    struct Plugin_Info_Key_Name{
        static constexpr const char* PluginDependencyDir = "PluginDependencyDir";
        static constexpr const char* PluginDLLPath = "PluginDLLPath";
        static constexpr const char* PluginType = "PluginType";
    };

    QJsonObject generateJsonObject() const override;
    QString     generateWritableJsonText() const override;
    const QString LoadM = LoadMethod::Dll;
    QString PluginDependencyDir;
    QString PluginDLLPath;
    QString PluginType;
};


struct ThemeRecord : Historical_Record
{
    QString themeQRC;
    struct ThemeRecordKey{
        static constexpr const char* ThemeQRC = "qrc";
    };
    ~ThemeRecord() = default;
    ThemeRecord(QString qrc):themeQRC(qrc){type = InfoType::ThemeRecordInfo;}
    ThemeRecord(){type = InfoType::ThemeRecordInfo;}
    ThemeRecord(QJsonObject& single_req);
    QJsonObject generateJsonObject() const override;
    QString     generateWritableJsonText() const override;
};


#endif // HISTORICAL_RECORD_H
