#include <QFileInfo>
#include "CCPDFView_Loader/ccpdf_loader.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "ccpdf_info.h"
#include "CCPDF_MainView/ccpdf_mainviewwidget.h"

void CCPDF_Info::updateCoreInfo(CCPDF_Loader* loader)
{
    coreInfo.title = CCPDF_FileUtils::PDF_Info::
        fetchNameAccordPath(loader->loadPath);

    coreInfo.pageCnt = loader->pageCount();
}

QString CCPDF_Info::statuText() const
{
    return QString("当前页: %1 : 共 %2 页")
        .arg(QString::number(runTimeInfo.currentPageIndex + 1))
        .arg(QString::number(coreInfo.pageCnt));
}


void CCPDF_Info::updateRunTimeInfo(CCPDF_MainViewWidget* viewer)
{
    runTimeInfo.currentPageIndex = viewer->currentPageIndex();
}
