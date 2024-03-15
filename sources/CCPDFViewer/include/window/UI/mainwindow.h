#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qtablewidget.h"
#include <QMainWindow>
class QLabel;
class CCPDF_View; // Import Important View
class PDF_HistoricalRecord;
class KeyBoardEventHandler;
class MouseWheelEventHandle;
class Page_Reactor;
class Zoom_Reactor;
class ViewWidget_Reactor;
class SaveReactor;
class EditReactor;
class HistoricalOperation_Reactor;
class PDF_FileViewManager;
class PDF_FileSystemModel;
class EditPDF_MainWindow;
class OCR_MainWindow;
class HelpMainWindow;
class NoteHandle;
class ThemeHandle;
class PDF_ExporterAndImageHolder;
class ReminderOfExportsMainWindow;
class ReminderProcessWindow;
class PDF_EditedPageManager;
class PDF_Window_SavingConfig;
class PDF_ExportPDFEx;
class PDF_SpecialAction;
class PDF_SpecialActionManager;
template<typename T>
class ActionHandler;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class ReadingFlags{
        SHOWING_ORG,
        SHOWING_EDIT
    };
    enum class PageIndex{
        HISTORY,
        TEXT_OCR,
        NOTE,
        LIBRARY,
        SEARCHING,
        THEME,
        EDITED,
        SAVE,
        RESUME
    };

    const   qreal eachZoomInPercentage      = 1.1;
    const   qreal eachZoomOutPercentage     = 0.8;

    explicit MainWindow(QWidget *parent = nullptr);

    // loadPDF API
    bool    loadPDFByFileDialog();
    bool    loadPDF(QString path);
    bool    loadTemporaryPath(QString path);
    bool    loadLibraryPath();
    bool    clearHistory();

    bool    loadQSS();

    // page change related
    void    toNextPage();
    void    toPrevPage();
    bool    toPage(int page);
    void    updateUiandHistWhenPaging();
    int     currentPage();

    // remove the selected history
    bool    removeHistory();
    bool    removeHistory(QString path);

    // zooming
    bool    zoomIn();
    bool    zoomOut();

    // view or hide the hyper Widget
    bool    operateHyperWidget();
    // view or hide the bookmark widget
    bool    operateBookMarkWidget();

    // QLineEdited changed the pageIndex
    void    editPageIndexEnable();

    // pageMode
    bool    isPageModeAccessible();
    bool    changePageMode();
    bool    singlePageMode();
    bool    multiPageMode();

    // notebook
    bool    openAddNoteBook();
    bool    bindNoteBook();
    bool    switchNoteBook();
    bool    removeNoteBook();
    bool    processNoteBook();

    // noteBookHandle
    bool    addHandle();
    bool    removeHandle();
    bool    switchHandle();
    bool    showhandles();

    // windows special events
    void    closeEvent(QCloseEvent*);
    void    keyPressEvent(QKeyEvent*);
    void    mousePressEvent(QMouseEvent*);
    void    keyReleaseEvent(QKeyEvent*);
    void    wheelEvent(QWheelEvent*);
    void    dragEnterEvent(QDragEnterEvent*);
    void    dropEvent(QDropEvent*);

    // help and about
    bool    viewAbout();
    bool    viewHelp();

    // open searching block
    bool    openSearchingBlock();

    // editControl API
    bool    backToBeforeEditedCurPage();
    bool    backToTheBeforeAll();
    bool    backToThePrevious();
    bool    saveForOtherCopy();
    void    cancelTheSave();
    void    handleCancelFinish();

    // quit
    bool    quit();
    ~MainWindow();
signals:
    // for export reminder
    void    shellshowReminder(); // to the showReminderOfExport();
    void    updatePageValue(int pg);
    void    updateRenderPageVal(int pg);
    void    updateExportPageVal(int pg);
    void    updateToTellFinishRender();
    void    updateToTellFinishExport();
    void    updateToTellCancelFinish();
private slots:
    void handleTheAutoDeletedObject(QObject* o[[maybe_unused]]){o = nullptr;}

    bool openOCRWindow();

    bool openEditWindow();

    void handlePageIndexEdit(QString txt);

    void handleOCRRes(QString txt);

    void showOCRPage();

    void showReminderOfExport();

    void configOCRFromChange(QStringList* l);

    void setIsableDirectOCR(bool state);

    bool changeStyleDirect();

    bool setAsDefaultStyle();

    bool randStyle();

    void showRenderProcess(int pg);

    void showRenderFinish();

    void showExportProcess(int pg);

    void showExportFinish();

    void on_tableWidget_filehist_itemPressed(QTableWidgetItem *item);

    void on_tableWidget_filehist_customContextMenuRequested(const QPoint &pos);

    void on_treeView_library_clicked(const QModelIndex &index);

    void on_btn_edit_current_clicked();

    void on_btn_configMission_clicked();

    bool on_btn_startMissionDirect_clicked();

    void on_btn_clip_clicked();

    void copyTheDirectText();

    void on_btn_addOrOpenNotes_clicked();

    void on_btn_releaseNotes_clicked();

    void on_btn_switch_clicked();

    void on_btn_bindNote_clicked();

    void on_btn_addNoteHandle_clicked();

    void on_btn_checkHandle_clicked();

    void on_btn_removeBtnHandle_clicked();

    void on_btn_randStyle_clicked();

    void on_btn_setClearTheme_clicked();



private:
    Ui::MainWindow*                 ui;
    PDF_HistoricalRecord*           histManager     = nullptr;
    PDF_FileViewManager*            fileViewManager = nullptr;
    NoteHandle*                     noteHandle      = nullptr;
    ThemeHandle*                    themeHandle     = nullptr;
    // init, call once only
    bool                            initCore();
    bool                            initHyperWidget();
    bool                            initIcon();
    bool                            initToolBar();
    bool                            initNotehandle();
    bool                            initSearchingWidget();
    bool                            initBookmarkWidget();
    bool                            configHistoryWidget_hyperW();
    bool                            configLibraryModel_hyperW();
    bool                            initConnection();
    void                            initEventHandle();
    void                            initExportConnection();
    void                            initExportReminder();
    void                            initTheEditedManager();
    void                            initHistoryMenu();
    void                            windowTitleSetterAccordingPDF();
    bool                            loadLastOpenFile();
    // close when the exe stops
    bool                            recordLastHistory();
    bool                            releaseHeapSource();
    void                            setEdited_HyperW();
    // load
    void                            successLoad_windowBehave();
    void                            configNoteBookAddWidget();
    PDF_SpecialAction*              createHistoryAction(QString pdfPath);
    void                            removeHistoryAction(QString pdfPath);
    // zoomPDF as private currently
    void                            zoomPDF(qreal factor);
    void                            setCurrentFocusHistView(QTableWidgetItem* i){currentFocus = i;}
    void                            initThemeMenu();

    bool                            initOCRWindow();
    bool                            initEditWindow();

    // handle when the editing happen
    void                            handlingsAftertheEditingClose();
    void                            handleTheShownEditedOne(int pg);
    void                            saveForTheNormalReading();
    void                            resumeToNormalReading();
    // search related
    void                            searchBookInBookLibrary();
    void                            searchTextInPDF();
    void                            searchResultSelected(
                                    const QModelIndex &current,
                                    const QModelIndex &previous);
    void                            bookmarkSelected(const QModelIndex &index);
    // functional
    KeyBoardEventHandler*               keyhandle = nullptr;
    MouseWheelEventHandle*              mouseWheelhandler = nullptr;

    QList<Page_Reactor*>                pageFunctors;
    QList<Zoom_Reactor*>                zoomFunctors;
    QList<ViewWidget_Reactor*>          viewWidgetFunctors;
    QList<HistoricalOperation_Reactor*> historyFunctor;
    QList<SaveReactor*>                 saveFunctor;
    QList<EditReactor*>                 editFunctor;
    // QAction Menu Handler
    ActionHandler<MainWindow>*          actionHandler = nullptr;
    QMenu*                              histFileViewMenu = nullptr; // no need del
    QTableWidgetItem*                   currentFocus = nullptr; // no need del
    // MainWindowSources
    qreal                               zoomFactor = 1;
    bool                                viewHyperWidget = true;
    bool                                viewBookMarkModelWidget = true;
    bool                                shallEditPageIndex = true;
    bool                                isSinglePage = true;
    bool                                grabWindowKey = false;
    bool                                isLeavingForSave = false;
    PDF_FileSystemModel*                libraryModel;

    // statuebar info
    QLabel*                             statusInfoWidget = nullptr;
    QLineEdit*                          pageIndexEdit = nullptr;

    // SubWindows
    EditPDF_MainWindow*                 editWindow  = nullptr;
    OCR_MainWindow*                     ocrWindow   = nullptr;
    HelpMainWindow*                     helpWindow  = nullptr;
    ReminderProcessWindow*              reminderWindow = nullptr;
    // ReminderOfExportsMainWindow*        reminderWindow = nullptr;
    // saving
    // PDF_ExporterAndImageHolder*         exporterAndImageHolder = nullptr;
    PDF_ExportPDFEx*                    exporterAndImageHolder = nullptr;
    PDF_EditedPageManager*              editedPageManager = nullptr;
    PDF_Window_SavingConfig*            savingManager = nullptr;
    QMap<int, QImage*>                  editedImages;
    bool                                isSaving = false;
    // switch in readings
    QString                             currentInReading;
    int                                 lastEditingPage = -1;
    ReadingFlags                        readingFlags = ReadingFlags::SHOWING_ORG;

    // history
    PDF_SpecialActionManager*           histMenuManager = nullptr;
};
#endif // MAINWINDOW_H
