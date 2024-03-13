#ifndef NOTEHANDLE_H
#define NOTEHANDLE_H
#include <QStringList>
#include <QMap>

class NoteHandle
{
public:
    using ExePath               = QString;
    using HandleSuffix          = QString;
    NoteHandle() = default;
    bool setHandler(QString handleSuffix, QString exePath);
    bool switchHandle(QString exePath, QString handleSuffix, bool cover);
    void removeHandler(QString handleSuffix);
    QString getHandleExe(QString path);
    QMap<HandleSuffix, ExePath>& getMap(){return mapfix;}
    QStringList getCurrentRegisterSuffix();
    QStringList getCurrentHandles();
    QString     getDes();
private:
    QMap<HandleSuffix, ExePath> mapfix;
};

#endif // NOTEHANDLE_H
