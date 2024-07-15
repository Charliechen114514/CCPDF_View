#ifndef CCPDF_INFO_H
#define CCPDF_INFO_H
#include <QString>
class QPdfDocument;
class CCPDF_Loader;
class CCPDF_MainViewWidget;


struct CCPDF_Info
{
private:
    struct CCPDF_Core_Info{
        QString     title;
        int         pageCnt;
    }   coreInfo;

    struct CCPDF_RunTime_Info{
        int         currentPageIndex;
    }   runTimeInfo;

public:
    QString                 title() const{return coreInfo.title;}
    QString                 statuText() const;
    int                     pageCnt() const{return coreInfo.pageCnt;}
    int                     currentPageIndex() const{return runTimeInfo.currentPageIndex;}
    void                    updateCoreInfo(CCPDF_Loader* loader);
    void                    updateRunTimeInfo(CCPDF_MainViewWidget* viewer);
};

#endif // CCPDF_INFO_H
