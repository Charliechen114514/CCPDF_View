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
class PDF_FileViewManager;
class PDF_FileSystemModel;
class EditPDF_MainWindow;
class OCR_MainWindow;
class HelpMainWindow;
class NoteHandle;
class ThemeHandle;

template<typename T>
class ActionHandler;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const   qreal eachZoomInPercentage      = 1.1;
    const   qreal eachZoomOutPercentage     = 0.8;

    explicit MainWindow(QWidget *parent = nullptr);

    // loadPDF API
    bool    loadPDFByFileDialog();
    bool    loadPDF(QString path);
    bool    loadLibraryPath();
    bool    clearHistory();

    bool    loadQSS();

    void    toNextPage();
    void    toPrevPage();
    bool    toPage(int page);
    int     currentPage();
    bool    removeHistory();

    void    refresh();

    bool    zoomIn();
    bool    zoomOut();

    bool    operateHyperWidget();

    void    editPageIndexEnable();
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

    void    keyPressEvent(QKeyEvent*);
    void    keyReleaseEvent(QKeyEvent*);
    void    wheelEvent(QWheelEvent*);
    void    dragEnterEvent(QDragEnterEvent*);
    void    dropEvent(QDropEvent*);

    bool    viewAbout();
    bool    viewHelp();
    ~MainWindow();

private slots:
    void handleTheAutoDeletedObject(QObject* o[[maybe_unused]]){o = nullptr;}

    bool openOCRWindow();

    void handlePageIndexEdit(QString txt);

    void handleOCRRes(QString txt);

    void showOCRPage();

    void configOCRFromChange(QStringList* l);

    void setIsableDirectOCR(bool state);

    bool changeStyleDirect();

    bool setAsDefaultStyle();

    bool randStyle();

    void on_tableWidget_filehist_itemPressed(QTableWidgetItem *item);

    void on_tableWidget_filehist_customContextMenuRequested(const QPoint &pos);

    void on_treeView_library_clicked(const QModelIndex &index);

    void on_btn_edit_current_clicked();

    void on_btn_configMission_clicked();

    bool on_btn_startMissionDirect_clicked();

    void on_btn_clip_clicked();

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
    bool                            configHistoryWidget_hyperW();
    bool                            configLibraryModel_hyperW();
    bool                            initConnection();
    void                            initEventHandle();
    void                            windowTitleSetterAccordingPDF();
    bool                            loadLastOpenFile();
    // close when the exe stops
    bool                            recordLastHistory();
    bool                            releaseHeapSource();
    void                            setEdited_HyperW();
    // load
    void                            successLoad_windowBehave();
    void                            configNoteBookAddWidget();
    // zoomPDF as private currently
    void                            zoomPDF(qreal factor);
    void                            setCurrentFocusHistView(QTableWidgetItem* i){currentFocus = i;}
    void                            initThemeMenu();
    void                            initOCRWindow();
    bool                            openEditWindow();

    // functional
    KeyBoardEventHandler*           keyhandle = nullptr;
    MouseWheelEventHandle*          mouseWheelhandler = nullptr;

    QList<Page_Reactor*>            pageFunctors;
    QList<Zoom_Reactor*>            zoomFunctors;
    QList<ViewWidget_Reactor*>      viewWidgetFunctors;

    // QAction Menu Handler
    ActionHandler<MainWindow>*      actionHandler = nullptr;
    QMenu*                          histFileViewMenu = nullptr; // no need del
    QTableWidgetItem*               currentFocus = nullptr; // no need del
    // MainWindowSources
    qreal                           zoomFactor = 1;
    bool                            viewHyperWidget = true;
    bool                            shallEditPageIndex = true;
    bool                            isSinglePage = true;
    bool                            grabWindowKey = false;
    PDF_FileSystemModel*            libraryModel;

    // statuebar info
    QLabel*                         statusInfoWidget = nullptr;
    QLineEdit*                      pageIndexEdit;
    // OCR

    // Editing
    EditPDF_MainWindow*             editWindow  = nullptr;
    OCR_MainWindow*                 ocrWindow   = nullptr;
    HelpMainWindow*                 helpWindow  = nullptr;
};
#endif // MAINWINDOW_H
