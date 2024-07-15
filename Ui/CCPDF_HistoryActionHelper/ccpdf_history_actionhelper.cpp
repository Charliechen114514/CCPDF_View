#include "ccpdf_history_actionhelper.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"

void CCPDF_History_ActionHelper::
registerPaths(const QStringList& paths)
{
    for(const auto& each : paths)
    {
        containers.insert(renderAlg(each), each);
    }
}


QString    CCPDF_History_ActionHelper::
renderAlg(const QString& full_path)
{
    QString render_org = CCPDF_FileUtils::PDF_Info::fetchNameAccordPath(full_path);
    QString render_again = render_org;
    int renderTime = 0;
    while(containers.keys().contains(render_again))
    {
        renderTime++;
        render_again = render_org + "(" + QString::number(renderTime) + ")";
    }
    return render_again;
}
