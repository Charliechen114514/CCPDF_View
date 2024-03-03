#include "notehandle.h"
#include "PDF_Utils.h"

bool NoteHandle::setHandler(QString handleSuffix, QString exePath)
{
    if(this->mapfix.contains(handleSuffix)){
        return false;
    }
    mapfix.insert(handleSuffix, exePath);
    return true;
}

bool NoteHandle::switchHandle(QString exePath, QString handleSuffix, bool cover)
{
    if(!cover && this->mapfix.contains(handleSuffix)){
        return false;
    }

    mapfix.insert(handleSuffix, exePath);
    return true;
}

QStringList NoteHandle::getCurrentRegisterSuffix()
{
    return this->mapfix.keys();
}

QStringList NoteHandle::getCurrentHandles()
{
    return this->mapfix.values();
}

void NoteHandle::removeHandler(QString handleSuffix)
{
    mapfix.remove(handleSuffix);
}

QString NoteHandle::getDes()
{
    QString res;
    auto it = mapfix.cbegin();
    while(it != mapfix.cend())
    {
        res += it.key() + "后缀的文件由:> " + it.value() + "处理\n";
        it++;
    }
    return res;
}

QString NoteHandle::getHandleExe(QString path)
{
    return mapfix.value(PDF_LocationDefaults::getSuffixOfFile(path));
}
