#ifndef QSSMANAGER_H
#define QSSMANAGER_H
#include <QMap>

class QWidget;
//  *******************************************************************
//  Class Name:> QSSManager
//  Usage and comments:> manager the current style of the widget
//
//  *******************************************************************
class QSSManager{
public:
    const QStringList sheetsSupports{
        "ORIGINAL_LIGHT", "ORIGINAL_DARK", "QSS_AMOLED", "QSS_AQUA", "QSS_ConsoleStyle",
        "QSS_ElegantDark","QSS_MacOS","QSS_ManjaroMix","QSS_MaterialDark",
        "QSS_NeonButtons","QSS_Ubuntu","NO Style"};
    enum class QssType{
        ORIGINAL_LIGHT,
        ORIGINAL_DARK,
        QSS_AMOLED,
        QSS_AQUA,
        QSS_ConsoleStyle,
        QSS_ElegantDark,
        QSS_MacOS,
        QSS_ManjaroMix,
        QSS_MaterialDark,
        QSS_NeonButtons,
        QSS_Ubuntu,
        CLEAR_CLEAR
    };
    QSSManager();
    const QSSManager& operator=(const QSSManager&) = delete;
    QSSManager(const QSSManager&) = delete;
    ~QSSManager(){

    };
    // static:
    // setters:
    bool    setCurrentQSSType(const QssType currentQSSType){
        this->currentQSSType = currentQSSType; return true;
    }
    // getters:
    QssType getCurrentQSSType(){return currentQSSType;}

    // register User QSS
    bool    registerUserQSS(QString Path){
        this->userRegisteredQSS.push_back(Path);
        return true;
    }

    bool    loadUserQSS(QWidget* widget, long index);

    bool    loadDefaulltQSS(QWidget* widget);

protected:
private:
    //  Private Member:>
    QssType                     currentQSSType = QssType::CLEAR_CLEAR;//  currentQSSType
    QMap<QssType, QString>      defaultQssMap;//  the QSSMap
    QStringList                 userRegisteredQSS;

    void registerQss();
    QString getDefaultOne(){
        return this->defaultQssMap.find(currentQSSType).value();
    }

    bool loadQSSPrivate(QWidget* widget, QString path);

    bool checkIndexVadility(long index){
        return index < userRegisteredQSS.size();
    }
};
#endif // QSSMANAGER_H
