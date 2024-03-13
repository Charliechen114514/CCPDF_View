#include "qssmanager.h"
#include <QFile>
#include <QWidget>
#define REGISTER_QSS(Region, Style, Path_Base, whatStyle) \
    defaultQssMap.insert( \
        QssType::Region##_##Style, QString(Path_Base) + whatStyle+ ".qss" \
    )

void QSSManager::registerQss()
{
    // register the qssfiles
    REGISTER_QSS(ORIGINAL, DARK, ":/qdarkstyle/dark/", "darkstyle");
    REGISTER_QSS(ORIGINAL, LIGHT, ":/qdarkstyle/light/", "lightstyle");
    REGISTER_QSS(QSS, AMOLED, ":/qss/Direct/","AMOLED");
    REGISTER_QSS(QSS, AQUA, ":/qss/Direct/", "Aqua");
    REGISTER_QSS(QSS, ConsoleStyle, ":/qss/Direct/", "ConsoleStyle");
    REGISTER_QSS(QSS, ElegantDark, ":/qss/Direct/", "ElegantDark");
    REGISTER_QSS(QSS, MacOS, ":/qss/Direct/", "MacOS");
    REGISTER_QSS(QSS, ManjaroMix, ":/qss/Direct/", "ManjaroMix");
    REGISTER_QSS(QSS, MaterialDark, ":/qss/Direct/", "MaterialDark");
    REGISTER_QSS(QSS, NeonButtons, ":/qss/Direct/", "NeonButtons");
    REGISTER_QSS(QSS, Ubuntu, ":/qss/Direct/", "Ubuntu");
    REGISTER_QSS(CLEAR, CLEAR, "", "");
}


QSSManager::QSSManager()
{
    registerQss();
}

bool QSSManager::loadDefaulltQSS(QWidget* widget)
{
    if(this->currentQSSType == QssType::CLEAR_CLEAR)
    {
        widget->setStyleSheet("");
        return true;
    }
    QString path = this->getDefaultOne();
    return loadQSSPrivate(widget, path);
}

bool QSSManager::loadUserQSS(QWidget* widget, long index)
{
    if(!checkIndexVadility(index) || !widget)
        return false;

    return loadQSSPrivate(widget, this->userRegisteredQSS[index]);
}

bool QSSManager::loadQSSPrivate(QWidget* widget, QString path)
{
    if(!widget)
        return false;
    QString qss;
    QFile qssFile(path);
    qssFile.open(QIODevice::ReadOnly);

    if(qssFile.isOpen())
    {
        qss = qssFile.readAll();
    }
    else
    {
        return false;
    }

    widget->setStyleSheet(qss);
    return true;
}

