#ifndef CCPDF_VIEW_H
#define CCPDF_VIEW_H

#include <QWidget>


class CCPDF_Loader;
class QPdfView;
class QPdfSearchModel;
class QPdfBookmarkModel;
class QGridLayout;
class QPdfDocument;
class QAbstractItemView;
class CCPDF_View : public QWidget
{
    Q_OBJECT
public:
    CCPDF_View(QWidget* parent);
    CCPDF_View(const CCPDF_View&) = delete;
    const CCPDF_View& operator=(const CCPDF_View&) = delete;
    ~CCPDF_View();

    enum class PageViewingMode
    {
        MutliPage,
        SinglePage
    };

    // loading
    enum class LoadingMethod
    {
        BY_GIVEN_STR,
        BY_FILE_DIALOG
    };

    bool                loadPDF(LoadingMethod m = LoadingMethod::BY_FILE_DIALOG, QString givenPath = "");
    bool                loadTempPDF(QString givenPath);

    bool                isViewerAccessible();

    QString             currentPDFPath();
    QString             currentPDFName();
    // page navigator
    int                 currentPageCnt();
    int                 currentPage();
    bool                toPage(int page);
    QString             getCurrentPageText() const;
    QString             getCurruntPDFDescriptions();

    // zoom
    const qreal         ZOOM_MIN = 0.1;
    const qreal         ZOOM_MAX = 1000.0;

    bool                zoomPage(const qreal pageZoomFactor);
    qreal               zoomFactor() const;

    void                setPageMode(PageViewingMode m);

    QString             getErrorString();

    QImage              getImagedFile();
    QImage              getTmpPDFImage();

    QPdfDocument*       getDocForExport();
    QPdfSearchModel*    getSearchModel(){return searchingModel;}

    void                setSearchingString(const QString& res);
    void                jumpToSearching(int page, QPointF link, const QModelIndex &current);
    int                 jumpToChapter(const QModelIndex &index);
    void                bindBookmarkModel(QAbstractItemView* view);
    void                bindSearchingModel(QAbstractItemView* view);

private:
    QPdfView*           coreView = nullptr;
    QPdfSearchModel*    searchingModel = nullptr;
    QPdfSearchModel*    tmpSearchingModel = nullptr;
    QPdfBookmarkModel*  bookMarkModel;
    CCPDF_Loader*       loader = nullptr;
    // load Edited
    CCPDF_Loader*       tmpLoader = nullptr;
    QGridLayout*        pdfLayOut = nullptr;
    int                 currentReadingPage = 0;
    bool                isPageAccessible(int page);
    void                closeView();
};

#endif // CCPDF_VIEW_H
