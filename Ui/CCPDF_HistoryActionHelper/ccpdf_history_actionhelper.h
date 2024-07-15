#ifndef CCPDF_HISTORY_ACTIONHELPER_H
#define CCPDF_HISTORY_ACTIONHELPER_H
#include "CCPDF_Global.h"
#include <QMap>
class CCPDF_History_ActionHelper
{
public:
    using PDF_Full_Path = QString;
    using PDF_FileName  = QString;
    CCPDF_History_ActionHelper() = default;
    DISABLE_COPY(CCPDF_History_ActionHelper);
    void       registerPaths(const QStringList& paths);
    QString    fetchAccordingFileName(const PDF_FileName& fileName){return containers.value(fileName);}
    QString    renderedFileName(const PDF_Full_Path& full_path){return containers.key(full_path);}
    void       removeRecord(const PDF_Full_Path& full_path){containers.remove(containers.value(full_path));};
    QList<PDF_FileName> renderedFileNames() const {return containers.keys();}

private:
    QString                             renderAlg(const QString& full_path);
    QMap<PDF_FileName, PDF_Full_Path>   containers;
};

#endif // CCPDF_HISTORY_ACTIONHELPER_H
