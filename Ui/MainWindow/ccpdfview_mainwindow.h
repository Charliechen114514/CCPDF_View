#ifndef CCPDFVIEW_MAINWINDOW_H
#define CCPDFVIEW_MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include "CCPDF_Global.h"
#include "CCPDF_Historical/Historical/historical_record.h"

// Pre-announcements
class   QMdiSubWindow;
class   QTableWidgetItem;
class   CCPDF_SinglePDF_Widget;
class   WindowEventHelper;
class   CCPDF_MdiArea;
class   CCPDF_HistoricalRecordHelper;
struct  CCPDF_PdfServer;
class   CCPDF_History_ActionHelper;
struct  CCPDF_ExternalPlugins;
class   CCPDF_HistoryTableWidgetController;
class   CCPDF_Other_Simple_Server_HistoricalHelper;
class   ThemeHistoricalHelper;
class   CCPDF_ThemeActionHelper;
class   CCPDF_HelpWindow;
QT_BEGIN_NAMESPACE
namespace Ui { class CCPDFView_MainWindow; }
QT_END_NAMESPACE


class CCPDFView_MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum class PageNavigateCommand{
        PAGE_NEXT,
        PAGE_PREV,
        PAGE_BEG,
        PAGE_END
    };

    enum class PageModeBrowseCommand{
        SINGLE_PAGE,
        MULTI_PAGE
    };

    enum class PageZoomCommand{
        ZOOM_IN,
        ZOOM_OUT
    };
    enum PAGE_INDEX{
        HISTMENU     ,
        PAGE_NAV     ,
        OCR_TEXT     ,
        TRANSLATE    ,
        LIBRARY      ,
        LINK         ,
        SEARCHIN     ,
    };

    CCPDFView_MainWindow(QWidget *parent = nullptr);
// ------------------------------------------------------
//  Public PDF Load Interface:
// ------------------------------------------------------
    bool    loadPDFFromFileDialog();
    bool    loadPDF(const QString &str);

// ------------------------------------------------------
//  Public PDF Text Fetcher
// ------------------------------------------------------
    bool    setCurrentPageText();
    bool    copyPdfTextToClipBoard();
// ------------------------------------------------------
//  Public PDF Page Navigations
// ------------------------------------------------------
    bool    pageNavigate(int page);
    bool    pageNavigate(const QString& page);
    bool    pageNavigate(int page, QPointF p);
    bool    pageNavigate(PageNavigateCommand m);
// ------------------------------------------------------
//  Public PDF Zoom Controll Interface
// ------------------------------------------------------
    bool    zoom(PageZoomCommand command);
    bool    zoom(const double zoomPercentage);
// ------------------------------------------------------
//  Public PDF Page Mode Control
// ------------------------------------------------------
    bool    setPageMode(PageModeBrowseCommand comm);
// ------------------------------------------------------
//  Public Refresh Main Ui
// ------------------------------------------------------
    void    opposeHyperWidgetVisible();
    void    opposeBookModelVisible();
// ------------------------------------------------------
//  handleRunTime Ui Change Required
// ------------------------------------------------------
    void    updateHistWidget();
    void    updateLinkModel();
// ------------------------------------------------------
//  routePage
// ------------------------------------------------------
    void    routeTo(PAGE_INDEX i);
// ------------------------------------------------------
//  routePage
// ------------------------------------------------------
    void    addTheme();
// ------------------------------------------------------
//  showAbout And Help
// ------------------------------------------------------
    void    showAbout();
    void    showHelp();

    ~CCPDFView_MainWindow();




public slots:
    __BIND_Ui_Widgets   void    pageForward(){pageNavigate(PageNavigateCommand::PAGE_NEXT);}
    __BIND_Ui_Widgets   void    pageBackward(){pageNavigate(PageNavigateCommand::PAGE_PREV);}
    __BIND_Ui_Widgets   void    pageBegin(){pageNavigate(PageNavigateCommand::PAGE_BEG);}
    __BIND_Ui_Widgets   void    pageEnd(){pageNavigate(PageNavigateCommand::PAGE_END);}
    __BIND_Ui_Widgets   void    zoomIn(){zoom(PageZoomCommand::ZOOM_IN);}
    __BIND_Ui_Widgets   void    zoomOut(){zoom(PageZoomCommand::ZOOM_OUT);}
    __BIND_Ui_Widgets   void    pageSingle(){setPageMode(PageModeBrowseCommand::SINGLE_PAGE);}
    __BIND_Ui_Widgets   void    pageMulti(){setPageMode(PageModeBrowseCommand::MULTI_PAGE);}
    __BIND_Ui_Widgets   void    routeToHistory(){routeTo(PAGE_INDEX::HISTMENU);}
    __BIND_Ui_Widgets   void    routeToSearching(){routeTo(PAGE_INDEX::SEARCHIN);}
    __BIND_Ui_Widgets   void    routeToLibrary(){routeTo(PAGE_INDEX::LIBRARY);}
    __BIND_Ui_Widgets   void    routeToTranslate(){routeTo(PAGE_INDEX::TRANSLATE);}
    __BIND_Ui_Widgets   void    routeToLink(){routeTo(PAGE_INDEX::LINK);};
    __BIND_Ui_Widgets   void    routeToOCR(){routeTo(PAGE_INDEX::OCR_TEXT);}
    void                        closeEvent(QCloseEvent*);
    void                        keyPressEvent(QKeyEvent*);
    void                        keyReleaseEvent(QKeyEvent*);
    void                        wheelEvent(QWheelEvent*);
    void                        dragEnterEvent(QDragEnterEvent* env);
    void                        dropEvent(QDropEvent*);

private slots:
    __BIND_Ui_Widgets   void        on_btn_pageBack_clicked(){pageBackward();}
    __BIND_Ui_Widgets   void        on_btn_pageForward_clicked(){pageForward();}
    __BIND_Ui_Widgets   void        on_btn_copyText2ClipBoard_clicked(){copyPdfTextToClipBoard();}
    __BIND_Ui_Widgets   void        on_btn_toBegin_clicked(){pageBegin();}
    __BIND_Ui_Widgets   void        on_btn_toEnd_clicked(){pageEnd();}
    __BIND_Ui_Widgets   void        on_btn_sigPage_clicked(){pageSingle();}
    __BIND_Ui_Widgets   void        on_btn_multiPage_clicked(){pageMulti();}
    __BIND_Ui_No_Inline void        on_historical_tableWidget_customContextMenuRequested(const QPoint &pos);
    __BIND_Ui_No_Inline void        on_historical_tableWidget_itemClicked(QTableWidgetItem *item);



private:
// ------------------------------------------------------
//  Initialize
// ------------------------------------------------------
    // memories allocations
    // All delayable initialize memories are allocate here
    void                            initMemories();
    void                            initCoreMemories();
    void                            initPluginMemory();
    // config Ui According to Set
    void                            configUi();
    void                            configWidgetsVisible();
    void                            loadTheme();
    void                            loadNoTheme();
    // self signal bingings
    void                            initMainWindowConnections();
    // Menu init
    void                            initMenu();
    void                            initMenuUi();
    void                            initToolBar();
    void                            initHistoryMenuUi();
    void                            initPluginMenuUi();
    void                            initThemeMenuUi();
    void                            initStatusBar();
    void                            initMenuConnections();
    // init HyperWidegt
    void                            initHyperWidget();
    void                            initHW_PageNavigation();
    void                            initHW_HistPage();
    void                            initHW_BookLibrary();
    // registerKeys And Mouses
    void                            registerKeyEvents();
    void                            registerMouseEvents();
    // logging and historical records
    void                            initLoggingHistoricalRecord();
    void                            loadLoggingHistoricalRecord();
    void                            loadHistoricalPDF();
    void                            initLoadHistoricalWidget();
    // Plugins Activate
    void                            initPluginHistAndConfig();
    void                            activateAllPlugin();

// ------------------------------------------------------
//  Private Functionality
// ------------------------------------------------------

// ------------------------------------------------------
//  Private PDF Load Impl:
//  Load According PDF_Record : At init
//  Load According PDF_Record : At RunTime
//  Load According PDF_Record : Brand New
// ------------------------------------------------------
    bool                            loadPdfAccordRecord(const PDF_Info_Historical_Record &rec);
    void                            doAddNewWindow(CCPDF_SinglePDF_Widget* w);
    CCPDF_SinglePDF_Widget*         createNewSingle(const QString &path);
    bool                            init_loadRecordPDF(const PDF_Info_Historical_Record &rec, bool if_isLastOne);
    void                            loadNewPDF_impl(const QString &path);
    // switch operating
    void                            switch_activate_window(QMdiSubWindow *);

    void                            handlePageNavigateChange();

// ------------------------------------------------------
//  Load New PDF Hook
// ------------------------------------------------------
    void                            doloadNewPdfCallBack(CCPDF_SinglePDF_Widget *);
    void                            addNewPdfRecord(CCPDF_SinglePDF_Widget *w);

// ------------------------------------------------------
//  Handle PDF Close
// ------------------------------------------------------
    void                            handlePdfClose(QString path_close);
    void                            removeOnePdfHistory(const QString& pdf_Path);
    void                            removeOnePdfHistoryInCore(const QString& pdf_Path);
    void                            removeOnePdfHistoryInMenu(const QString& pdf_Path);
// ------------------------------------------------------
// Handle Errors
// ------------------------------------------------------
    void                            handlePageNavigationError();
    void                            handleZoomError();
// ------------------------------------------------------
//  Update Recorders
// ------------------------------------------------------
    void                            updateOldRecord(CCPDF_SinglePDF_Widget* oldWidget);
    void                            updateBookLibRecord(QString atWhere);
// ------------------------------------------------------
//  Update current_focus_widgets
// ------------------------------------------------------
    void                            udpateCurrentFocusWidgets(CCPDF_SinglePDF_Widget* newWidgets);

// ------------------------------------------------------
//  handle BookMark Jump
// ------------------------------------------------------
    void                            handleBookMarkJump(const int page, const qreal zoomLevel);

// ------------------------------------------------------
//  handle Search Jump
// ------------------------------------------------------
    void                            handleSearchJump(const int page, QPointF location, const QModelIndex& index);

// ------------------------------------------------------
//  handle Themes
// ------------------------------------------------------
    void                            handleNewTheme(const QString name);
    void                            switchToTheme(const QString name);
    void                            handleRemoveTheme(const QString name);

// ------------------------------------------------------
//  Page Modes
// ------------------------------------------------------
    void                            handleMultiPageChange();

// ------------------------------------------------------
// Private Members
// ------------------------------------------------------

    // containers
    Ui::CCPDFView_MainWindow*                       ui;
    bool                                            hyperWidgetVisible {INIT_PARAMS::HYPER_WID_VISIBLE};
    bool                                            bookModelVisible{INIT_PARAMS::BOOKMODEL_VISIBLE};
    __MEMEROY_HOLD_BY_OBJ_TREE
    QLabel*                                         statusLabel;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<WindowEventHelper>              windowEventHelper;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_HistoricalRecordHelper>   histRecorder;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<ThemeHistoricalHelper>          themeHolder;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_Other_Simple_Server_HistoricalHelper>   otherServerRecorder;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_PdfServer>                pdfServer;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_ExternalPlugins>          pdfPlugins;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_History_ActionHelper>     histMenuHelper;
    __MEMEROY_HOLD_BY_OBJ_TREE
    std::unique_ptr<
        CCPDF_HistoryTableWidgetController>         histtableWidgetController;
    std::unique_ptr<
        CCPDF_ThemeActionHelper>                    themeActionHelper;
    __MEMEROY_HOLD_BY_OBJ_TREE
        CCPDF_HelpWindow*                           helpWindow{nullptr};
};
#endif // CCPDFVIEW_MAINWINDOW_H
