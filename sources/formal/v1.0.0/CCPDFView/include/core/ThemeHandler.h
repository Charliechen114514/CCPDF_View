#ifndef THEMEHANDLER_H
#define THEMEHANDLER_H
#include <QObject>
#include "qssmanager.h"
class ThemeHandle : public QObject
{
public:
    using       QSSIndex = int;
    explicit    ThemeHandle(QObject* parent = nullptr);
    ThemeHandle(const ThemeHandle&) = delete;
    const ThemeHandle& operator=(const ThemeHandle&) = delete;
    void        setConfigTheWidget(QWidget* w);
    QStringList getTheAcceptableThemes();
    void        setQSSByGivenIndex(QSSIndex i);
    QSSIndex    getCurrentIndex(){return index;}
public slots:
    /*        QSS_ConsoleStyle,
        QSS_ElegantDark,
        QSS_MacOS,
        QSS_ManjaroMix,
        QSS_MaterialDark,
        QSS_NeonButtons,
        QSS_Ubuntu,*/
    void        brightTheme();
    void        darkTheme();

    void        AMOLEDTheme();
    void        AQUATheme();
    void        ConsoleTheme();
    void        ElegantDarkTheme();
    void        MacOSTheme();
    void        ManjaroMixTheme();
    void        MaterialDarkTheme();
    void        NeonButtonsTheme();
    void        UbuntuTheme();
    void        noTheme();
private:
    QSSManager  m;
    QWidget*    config = nullptr;
    QSSIndex    index;
};


#endif // THEMEHANDLER_H
