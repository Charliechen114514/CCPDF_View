#ifndef CCPDF_THEMEACTIONHELPER_H
#define CCPDF_THEMEACTIONHELPER_H
#include "CCPDF_Global.h"
#include <QMap>
class CCPDF_ThemeActionHelper
{
public:
    using Name = QString;
    using Path = QString;
    CCPDF_ThemeActionHelper() = default;
    DISABLE_COPY(CCPDF_ThemeActionHelper);
    ~CCPDF_ThemeActionHelper() = default;
    void    registerPaths(const QStringList& paths){for(const auto&each : paths) addPath(each);}
    inline  void    addPath(const QString& filePath){map.insert(filePath, renderAlg(filePath));}
    inline  void    removePath(const QString& filePath){map.remove(filePath);}
    inline  QString getName(const QString& filePath){return map.value(filePath);}
    inline  QString getPath(const QString& name){return map.key(name);}
    inline  QStringList renderNames(){return map.values();}
private:
    Name                   renderAlg(const Path& p);
    QMap<Path,Name>        map;
};

#endif // CCPDF_THEMEACTIONHELPER_H
