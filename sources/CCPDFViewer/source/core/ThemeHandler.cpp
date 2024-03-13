#include "ThemeHandler.h"
#include "qssmanager.h"
ThemeHandle::ThemeHandle(QObject* parent):QObject(parent){
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}

void ThemeHandle::setConfigTheWidget(QWidget* w)
{
    this->config = w;
}

QStringList ThemeHandle::getTheAcceptableThemes()
{
    return this->m.sheetsSupports;
}

void ThemeHandle::setQSSByGivenIndex(QSSIndex i)
{
    QSSManager::QssType t = QSSManager::QssType::CLEAR_CLEAR;
    switch(i)
    {
    case 0:
        t = QSSManager::QssType::ORIGINAL_LIGHT;break;
    case 1:
        t= QSSManager::QssType::ORIGINAL_DARK;break;
    case 2:
        t = QSSManager::QssType::QSS_AMOLED;break;
    case 3:
        t = QSSManager::QssType::QSS_AQUA;break;
    case 4:
        t = QSSManager::QssType::QSS_ConsoleStyle;break;
    case 5:
        t = QSSManager::QssType::QSS_ElegantDark;break;
    case 6:
        t = QSSManager::QssType::QSS_MacOS;break;
    case 7:
        t = QSSManager::QssType::QSS_ManjaroMix;break;
    case 8:
        t = QSSManager::QssType::QSS_MaterialDark;break;
    case 9:
        t = QSSManager::QssType::QSS_NeonButtons;break;
    case 10:
        t = QSSManager::QssType::QSS_Ubuntu;break;
    case 11:
        t = QSSManager::QssType::CLEAR_CLEAR;break;
    }
    if(i > static_cast<QSSIndex>(t))
    {
        t = QSSManager::QssType::ORIGINAL_LIGHT;
        i = 0;
    }
    m.setCurrentQSSType(t);
    index = i;
    m.loadDefaulltQSS(config);
}

void ThemeHandle::brightTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::ORIGINAL_LIGHT);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}

void ThemeHandle::darkTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::ORIGINAL_DARK);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}

void ThemeHandle::noTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::CLEAR_CLEAR);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}

void ThemeHandle::AMOLEDTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_AMOLED);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::AQUATheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_AQUA);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::ConsoleTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_ConsoleStyle);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::ElegantDarkTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_ElegantDark);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::MacOSTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_MacOS);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::ManjaroMixTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_ManjaroMix);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::MaterialDarkTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_MaterialDark);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}

void ThemeHandle::NeonButtonsTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_NeonButtons);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
void ThemeHandle::UbuntuTheme()
{
    m.setCurrentQSSType(QSSManager::QssType::QSS_Ubuntu);
    m.loadDefaulltQSS(config);
    index = static_cast<QSSIndex>(m.getCurrentQSSType());
}
