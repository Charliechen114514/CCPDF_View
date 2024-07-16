#include <QMdiSubWindow>
#include <QEvent>
#include <QValidator>
#include <QMimeData>
#include "CCPDF_ThemeAction/ccpdf_theme_action.h"
#include "CCPDF_ThemeActionHelper/ccpdf_themeactionhelper.h"
#include "CCPDF_BookMarkManager/ccpdf_bookmarkmanager.h"
#include "CCPDF_SearchManager/ccpdf_searchmanager.h"
#include "WindowBuild/CCPDF_ToolBarConfigure/ccpdf_toolbarconfigure.h"
#include "CCPDF_BookLibraryWidget/ccpdf_booklibrarywidget.h"
#include "External/ccpdf_externalplugins.h"
#include "CCPDF_HistoryAction/ccpdf_historyaction.h"
#include "CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.h"
#include "CCPDF_Info/ccpdf_info.h"
#include "CCPDF_PDFPageNavigator/ccpdf_pdfpagenavigator.h"
#include "CCPDF_TextHelper/ccpdf_texthelper.h"
#include "CCPDF_ZoomController/ccpdf_zoomcontroller.h"
#include "WindowEventHelper/windoweventhelper.h"
#include "ccpdfview_mainwindow.h"
#include "ui_ccpdfview_mainwindow.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"
#include "CCPDF_Utils/CCPDF_StringParseUtil.h"
#include "CCPDF_Utils/ccpdf_messgaeboxutils.h"
#include "CCPDF_Error_Helper/CCPDF_ErrorHelper.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDF_MdiSubWindow/ccpdf_mdisubwindow.h"
#include "CCPDF_PdfServer/ccpdf_pdfserver.h"
#include "CCPDF_HistoryActionHelper/ccpdf_history_actionhelper.h"
#include "CCPDF_HistoryTableWidgetContorller/ccpdf_historytablewidgetcontroller.h"
#include "CCPDF_LinkListWidgetManager/ccpdf_pdflinkwidgetmanager.h"
#ifdef SUPPORT_TESS_OCR
#include "Plugins/ocr/plugin_ocruimanager.h"
#endif

// ------------------------------------------------------
//  Initialize
//  Init as followings:
//  Memories Buffers [Must be first]
//  MainWindow Connections
//
//  Menu Inits
//
//  HyperWidget Initialization
//
//  EventHandle Registers
//  Mouse Interactives
//  KeyBoard Interactives
// ------------------------------------------------------

CCPDFView_MainWindow::CCPDFView_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CCPDFView_MainWindow)
{
    // MainWindowInit
    // init Ui
    ui->setupUi(this);
    // init MemoryBuffers
    initMemories();
    // init Reading
    initLoggingHistoricalRecord();
    // init Self signals Connections
    initMainWindowConnections();
    // Init StatusBar
    initStatusBar();
    // Init HyperWidget
    initHyperWidget();
    // Init Menu Stuffs
    initMenu();
    // Activate Plugins
    initPluginHistAndConfig();
    // init Logging and registering
    loadLoggingHistoricalRecord();
    activateAllPlugin();
    // register events
    // Init Mouse Interactives
    registerMouseEvents();
    // Init KeyBoard Interactives
    registerKeyEvents();

    // Ui control
    configUi();
    loadTheme();
}

void CCPDFView_MainWindow::initMemories()
{
    initCoreMemories();
    initPluginMemory();
}

void CCPDFView_MainWindow::initCoreMemories()
{
    // Init PDF Server
    pdfServer = std::make_unique<CCPDF_PdfServer>();
    pdfServer->pageNavigator = new CCPDF_PDFPageNavigator(this);
    pdfServer->zoomController = std::make_unique<CCPDF_ZoomController>(INIT_PARAMS::ZOOM_INIT);
    pdfServer->textHelper = std::make_unique<CCPDF_TextHelper>();
    pdfServer->bookMarkManager = std::make_unique<CCPDF_BookMarkManager>(ui->bookMarkWidget);
    pdfServer->searchManager = std::make_unique<CCPDF_SearchManager>(ui->searchWidget);
    pdfServer->linkModelManager = std::make_unique<CCPDF_PDfLinkWidgetManager>(ui->linkListWidget);
    // Recorders Init
    histRecorder = std::make_unique<CCPDF_HistoricalRecordHelper>();
    themeHolder = std::make_unique<ThemeHistoricalHelper>();
    otherServerRecorder = std::make_unique<CCPDF_Other_Simple_Server_HistoricalHelper>();

    windowEventHelper = std::make_unique<WindowEventHelper>();
    histMenuHelper = std::make_unique<CCPDF_History_ActionHelper>();
    themeActionHelper = std::make_unique<CCPDF_ThemeActionHelper>();
}

void CCPDFView_MainWindow::initPluginMemory()
{
    pdfPlugins = std::make_unique<CCPDF_ExternalPlugins>();
}

void CCPDFView_MainWindow::configUi()
{
    configWidgetsVisible();
    loadTheme();
}
void CCPDFView_MainWindow::configWidgetsVisible()
{
    ui->bookMarkWidget->setVisible(bookModelVisible);
    ui->hyper_operate_widget->setVisible(hyperWidgetVisible);
}

void CCPDFView_MainWindow::loadTheme()
{
    setStyleSheet(themeHolder->getInUsedOne());
}

void CCPDFView_MainWindow::loadNoTheme()
{
    setStyleSheet("");
}

//  Global Init
//  init self signals Connections: initMainWindowConnections()
void CCPDFView_MainWindow::initMainWindowConnections()
{
    connect(pdfServer->pageNavigator, &CCPDF_PDFPageNavigator::updatePage,
            this, &CCPDFView_MainWindow::updateOldRecord);
    connect(ui->bookMarkWidget, &CCPDF_BookMarkWidget::navigateTo,
            this, &CCPDFView_MainWindow::handleBookMarkJump);
    connect(ui->searchWidget, &CCPDF_SearchWidget::tellPageNavigate,
            this, &CCPDFView_MainWindow::handleSearchJump);
    connect(ui->main_mdi_widget, &QMdiArea::subWindowActivated,
            this, &CCPDFView_MainWindow::switch_activate_window);
    connect(ui->linkListWidget, &CCPDF_LinkWidget::navigateTo,
            this, qOverload<int>(&CCPDFView_MainWindow::pageNavigate));
}

void CCPDFView_MainWindow::initLoggingHistoricalRecord()
{
    histRecorder->setPDF_InfoLoggerPath(__DEF_LOG_PDF_REC);
    histRecorder->readPDF_HistoricalRecord();
    otherServerRecorder->setPDF_InfoLoggerPath(__DEF_OTHER_SERVER_LOG);
    otherServerRecorder->readPDF_HistoricalRecord();
    themeHolder->setPluginInfo_LoggerPath(__DEF_THEME_INITIALIZE);
    themeHolder->readPluginInfo_HistoricalRecord();
}

// ------------------------------------------------------
// Menu Inits
// ------------------------------------------------------

// Init Menus
void CCPDFView_MainWindow::initMenu()
{
    // init Ui
    initMenuUi();
    // init Connections
    initMenuConnections();
}

void CCPDFView_MainWindow::initMenuUi()
{
    initToolBar();
    initHistoryMenuUi();
    initPluginMenuUi();
    initThemeMenuUi();
}

void CCPDFView_MainWindow::initToolBar()
{
    CCPDF_MainWindowToolBarConfigure configure(this);
    configure.doConfig(ui->toolBar);
}

void CCPDFView_MainWindow::initHistoryMenuUi()
{
    histMenuHelper->registerPaths(histRecorder->current_pdf_paths());
    const auto pdfNames = histMenuHelper->renderedFileNames();
    for(const auto& eachName : pdfNames)
    {
        QString path = histMenuHelper->fetchAccordingFileName(eachName);
        CCPDF_HistoryAction* tmpAct = new CCPDF_HistoryAction(path, eachName, this);
        ui->history_menu->addAction(tmpAct);
        connect(tmpAct, &CCPDF_HistoryAction::tellSelfPdfPath,
                this, &CCPDFView_MainWindow::loadPDF);
    }

}



void CCPDFView_MainWindow::initThemeMenuUi()
{
    const auto paths = themeHolder->paths();
    themeActionHelper->registerPaths(paths);
    for(const auto& eachPath : paths)
    {
        handleNewTheme(eachPath);
    }
}


void CCPDFView_MainWindow::initStatusBar()
{
    statusLabel = new QLabel(this);
    ui->statusbar->addWidget(statusLabel);
}

void CCPDFView_MainWindow::initMenuConnections()
{
    connect(ui->action_load_PDF, &QAction::triggered,
            this, &CCPDFView_MainWindow::loadPDFFromFileDialog);
    connect(ui->action_addTheme, &QAction::triggered,
            this, &CCPDFView_MainWindow::addTheme);

}

// ------------------------------------------------------
// HyperWidgets Inits
// ------------------------------------------------------

void CCPDFView_MainWindow::initHyperWidget()
{
    initHW_PageNavigation();
    initHW_HistPage();
    initHW_BookLibrary();
}

void CCPDFView_MainWindow::initHW_PageNavigation()
{
    ui->page_navigate_lineEdit->setValidator
        (new QIntValidator(ui->page_navigate_lineEdit));
}

void CCPDFView_MainWindow::initHW_HistPage()
{
    histtableWidgetController = std::make_unique<CCPDF_HistoryTableWidgetController>(ui->historical_tableWidget, this);

    connect(histtableWidgetController.get(),
            &CCPDF_HistoryTableWidgetController::emitTellRemovePdfPath,
            this, &CCPDFView_MainWindow::removeOnePdfHistory);
    connect(histtableWidgetController.get(),
            &CCPDF_HistoryTableWidgetController::emitTellLoadPdf,
            this, &CCPDFView_MainWindow::loadPDF);

}

void CCPDFView_MainWindow::initHW_BookLibrary()
{
    BookLibrary_Record* rec = otherServerRecorder->bookRecord();
    if(rec)
    {
        ui->book_lib_searching_widget->setRootPath(rec->libPath);
    }
    connect(ui->book_lib_searching_widget, &CCPDF_BookLibraryWidget::tellLoadWhat,
            this, &CCPDFView_MainWindow::loadPDF);
    connect(ui->book_lib_searching_widget, &CCPDF_BookLibraryWidget::tellShellRecord,
            this, &CCPDFView_MainWindow::updateBookLibRecord);
    connect(ui->searchWidget, &CCPDF_SearchWidget::tellPageNavigate,
            this, &CCPDFView_MainWindow::handleSearchJump);
}

// ------------------------------------------------------
// Logger Inits
// ------------------------------------------------------

void CCPDFView_MainWindow::loadLoggingHistoricalRecord()
{
    loadHistoricalPDF();
    initLoadHistoricalWidget();
}

void CCPDFView_MainWindow::loadHistoricalPDF()
{
    auto rec = histRecorder->getRecords();
    const int size = rec.size();
    for(int i = 0; i < size; i++)
    {
        init_loadRecordPDF(rec[i], (i == size - 1));
    }
}

void CCPDFView_MainWindow::initLoadHistoricalWidget()
{
    auto records = histRecorder->getRecords();
    histtableWidgetController->setBindHistLists(records);
}



void CCPDFView_MainWindow::activateAllPlugin()
{
     pdfPlugins->activateAccordingToPluginHist();
}

void CCPDFView_MainWindow::registerKeyEvents()
{
// Page Navigations
    windowEventHelper->registerKeyEvents(
        Qt::Key_Right, std::bind(&CCPDFView_MainWindow::pageForward, this));
    windowEventHelper->registerKeyEvents(
        Qt::Key_Left,  std::bind(&CCPDFView_MainWindow::pageBackward, this)
        );
    windowEventHelper->registerKeyEvents(
        Qt::Key_D, std::bind(&CCPDFView_MainWindow::pageForward, this));
    windowEventHelper->registerKeyEvents(
        Qt::Key_A,  std::bind(&CCPDFView_MainWindow::pageBackward, this)
        );
// Ui Controlls
    windowEventHelper->registerKeyEvents(
        Qt::Key_V, std::bind(&CCPDFView_MainWindow::opposeHyperWidgetVisible, this),
        Qt::Modifier::CTRL | Qt::Modifier::SHIFT
    );
    windowEventHelper->registerKeyEvents(
        Qt::Key_M, std::bind(&CCPDFView_MainWindow::opposeBookModelVisible, this),
        Qt::Modifier::CTRL | Qt::Modifier::SHIFT
   );
    windowEventHelper->registerKeyEvents(
        Qt::Key_R, std::bind(&CCPDF_MdiArea::activateNextSubWindow, ui->main_mdi_widget),
        Qt::Modifier::CTRL
    );
    windowEventHelper->registerKeyEvents(
        Qt::Key_L, std::bind(&CCPDF_MdiArea::activatePreviousSubWindow, ui->main_mdi_widget),
        Qt::Modifier::CTRL
    );
}

void CCPDFView_MainWindow::registerMouseEvents()
{
    windowEventHelper->registerMouseEvents(
        WindowEventHelper::MouseProcess::WHEEL_UP,
        std::bind(&CCPDFView_MainWindow::zoomIn, this), Qt::Modifier::CTRL);

    windowEventHelper->registerMouseEvents(
        WindowEventHelper::MouseProcess::WHEEL_DOWN,
        std::bind(&CCPDFView_MainWindow::zoomOut, this), Qt::Modifier::CTRL);
}

// ------------------------------------------------------
//  Functionalities
//  Publics:
//  loadNewPDF()
//  Privates:
//  switch_activate_window()
//  page_navigates
// ------------------------------------------------------

// Load new PDFs
bool CCPDFView_MainWindow::loadPDFFromFileDialog()
{
    QString pathSelect =
    CCPDF_FileUtils::SelectFileUtils::selectExsitingFile(
        "选择目标PDF",CCPDF_FileUtils::PDF_Info::PDF_SUFFIX_LIST());
    if(pathSelect.isEmpty())
        return false;

    return loadPDF(pathSelect);
}

bool CCPDFView_MainWindow::loadPDF(const QString& path)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(path)){
        return false;
    }
    // check if in history
    if(histRecorder->isPdfInAlready(path)){
        auto record = histRecorder->record(path);
        if(!record.pdf_Path.isEmpty())
        {
            return loadPdfAccordRecord(record);
        }
    }
    // Update Rev infos
    loadNewPDF_impl(path);
    return true;
}

bool CCPDFView_MainWindow::loadPdfAccordRecord(const PDF_Info_Historical_Record &rec)
{
    // first check if is already in!
    auto windows = ui->main_mdi_widget->subWindowList();
    for(const auto& window : windows){
        auto widget = dynamic_cast<CCPDF_SinglePDF_Widget*>(window->widget());
        if(!widget)
            continue;
        if(widget->pdfPath() == rec.pdf_Path)
        {
            ui->main_mdi_widget->setActiveSubWindow(window);
            return true;
        }
    }
    return false;
}

bool CCPDFView_MainWindow::init_loadRecordPDF(const PDF_Info_Historical_Record& rec, bool if_isLastOne)
{
    if(!CCPDF_FileUtils::FileUtils::isFileExsits(rec.pdf_Path))
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::HistoryInvalid(rec.pdf_Path);
        CCPDF_MessgaeBoxUtils::ErrorInform::ErrorInform::tellError(pac.title, pac.details + pac.possible_help, this);
        return false;
    }

    if(if_isLastOne)
    {
        loadNewPDF_impl(rec.pdf_Path);
    }
    else
    {
        auto new_addee = new CCPDF_SinglePDF_Widget(ui->main_mdi_widget);
        new_addee->loadPDF(rec.pdf_Path);
        auto window = new CCPDF_MdiSubWindow(this);
        window->setWidget(new_addee);
        ui->main_mdi_widget->addSubWindow(window);
        window->setWindowTitle(new_addee->pdf_info->title());
        connect(window, &CCPDF_MdiSubWindow::self_close,
                this, &CCPDFView_MainWindow::handlePdfClose);
        window->showMaximized();
        pdfServer->pageNavigator->setOperatingPDF(new_addee);
    }
    bool ops_res = pdfServer->pageNavigator->jump(rec.current_page);
    if(!ops_res)
    {
        handlePageNavigationError();
        return false;
    }
    return true;
}


void CCPDFView_MainWindow::loadNewPDF_impl(const QString& path)
{
    auto new_addee = new CCPDF_SinglePDF_Widget(ui->main_mdi_widget);
    new_addee->loadPDF(path);
    auto window = new CCPDF_MdiSubWindow(this);
    window->setWidget(new_addee);
    ui->main_mdi_widget->addSubWindow(window);
    window->setWindowTitle(new_addee->pdf_info->title());
    connect(window, &CCPDF_MdiSubWindow::self_close,
            this, &CCPDFView_MainWindow::handlePdfClose);
    window->showMaximized();
    udpateCurrentFocusWidgets(new_addee);
    doloadNewPdfCallBack(new_addee);
}

// switch page navigations
void CCPDFView_MainWindow::switch_activate_window(QMdiSubWindow* w)
{
    auto getWindow =
        dynamic_cast<CCPDF_MdiSubWindow*>(w);
    if(!getWindow)
    {
        udpateCurrentFocusWidgets(nullptr);
        return;
    }

//     qDebug() << "valid window";
    auto new_current_focus_pdf_widget =
        dynamic_cast<CCPDF_SinglePDF_Widget*>(getWindow->widget());

    if(new_current_focus_pdf_widget == pdfServer->current_widget())
        return;

    qDebug() << "Switching PDFs...";
    updateOldRecord(pdfServer->current_widget());
    udpateCurrentFocusWidgets(new_current_focus_pdf_widget);
}

// ------------------------------------------------------
//  Load New PDF Hook
// ------------------------------------------------------
void CCPDFView_MainWindow::doloadNewPdfCallBack(CCPDF_SinglePDF_Widget* w)
{
    addNewPdfRecord(w);
    const auto rec = w->getRecord();
    this->histtableWidgetController->addToMenu(rec);
}

void CCPDFView_MainWindow::addNewPdfRecord(CCPDF_SinglePDF_Widget* w)
{
    histRecorder->addPDF_Info_Record(w->getRecord());
}

bool CCPDFView_MainWindow::setCurrentPageText()
{
    qDebug() << "Comming set Text";
    if(!pdfServer->textHelper->setCurrentPdfText(ui->pdftextBrowser))
    {
        switch(pdfServer->textHelper->getError())
        {
        case CCPDF_TextHelper::TextGetterHelperError::Error::NO_ERROR:
            pdfPlugins->setPluginInputFromOutWard(
                ui->pdftextBrowser->toPlainText(),
                CCPDF_ExternalPlugins::CurrentSupportPlugin::TRANSLATION);
            return true;
        case CCPDF_TextHelper::TextGetterHelperError::Error::NO_BIND_PDF:
        {
            auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
            CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
                pac.title, pac.details, this);
            pdfServer->textHelper->clearError();
            break;
        }
        case CCPDF_TextHelper::TextGetterHelperError::Error::NO_DIRECT_GET:
        {
            auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
            ui->pdftextBrowser->setText(pac.details + pac.possible_help);
            pdfServer->textHelper->clearError();
        }break;
        }
        return false;
    }
    else
    {
        return true;
    }
}

bool CCPDFView_MainWindow::copyPdfTextToClipBoard()
{
    if(!pdfServer->current_widget())
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        return false;
    }
    pdfServer->textHelper->copyToClipBoard();
    return true;
}


// ------------------------------------------------------
//  Handle PDF Records
// ------------------------------------------------------
void CCPDFView_MainWindow::handlePdfClose(QString path_close)
{
    QString path = path_close;
    if(CCPDF_MessgaeBoxUtils::AskForQuery::query(
            "是否打算删除历史记录？", "是否打算删除历史记录？", this
    ))
    {
        qDebug() << "Remove PDF Path:> " << path;
        removeOnePdfHistory(path);
    }
    else
    {
        qDebug() << "Record is saved!";
    }
}

void CCPDFView_MainWindow::removeOnePdfHistory(const QString& pdf_path)
{
    removeOnePdfHistoryInCore(pdf_path);
    removeOnePdfHistoryInMenu(pdf_path);
}

void CCPDFView_MainWindow::removeOnePdfHistoryInCore(const QString& pdf_Path)
{
    histRecorder->remove_Info_record(pdf_Path);
}

void CCPDFView_MainWindow::removeOnePdfHistoryInMenu(const QString& pdf_path)
{
    histMenuHelper->removeRecord(pdf_path);
    auto all_actions = ui->history_menu->actions();
    for(const auto& each : all_actions)
    {
        auto true_action = dynamic_cast<CCPDF_HistoryAction*>(each);
        if(true_action && pdf_path == true_action->holding_path()){
            ui->history_menu->removeAction(true_action);
            break;
        }
    }

    histtableWidgetController->removeFromOutward(pdf_path);
}



void CCPDFView_MainWindow::handlePageNavigationError()
{
    switch(pdfServer->pageNavigator->getError())
    {
    case CCPDF_PDFPageNavigator::PageNav_Error::Error::NO_ERROR:break;
    case CCPDF_PDFPageNavigator::PageNav_Error::Error::NO_BIND_PDF:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->pageNavigator->clearError();
        break;
    }
    case CCPDF_PDFPageNavigator::PageNav_Error::Error::PAGE_OVERFLOW:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::PageOverflowError("是否前往第一页？");;
        if(CCPDF_MessgaeBoxUtils::InfoInform::inform(
                pac.title, pac.details + "\n" + pac.possible_help, this))
        {
            pdfServer->pageNavigator->clearError();
            pageNavigate(PageNavigateCommand::PAGE_BEG);
        }
        else
            pdfServer->pageNavigator->clearError();
        break;
    }
    case CCPDF_PDFPageNavigator::PageNav_Error::Error::PAGE_UNDERFLOW:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::PageUnderflowError("是否前往做后一页？");;
        if(CCPDF_MessgaeBoxUtils::InfoInform::inform(
                pac.title, pac.details + "\n" + pac.possible_help, this))
        {
            pdfServer->pageNavigator->clearError();
            pageNavigate(PageNavigateCommand::PAGE_END);
        }
        else
            pdfServer->pageNavigator->clearError();
        break;
    }
    case CCPDF_PDFPageNavigator::PageNav_Error::Error::PAGE_IDX_FMT_INVALID:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::Invalid_Page_Index_FMT();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->pageNavigator->clearError();
        break;
    }
    }
}

void CCPDFView_MainWindow::handleZoomError()
{
    switch(pdfServer->zoomController->getError())
    {
    case CCPDF_ZoomController::ZoomError::Error::NO_ERROR:
        return;
    case CCPDF_ZoomController::ZoomError::Error::ZOOM_TO_MIN:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::ZoomOutMinOutError();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->zoomController->clearError();
    }break;
    case CCPDF_ZoomController::ZoomError::Error::ZOOM_TO_MAX:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::ZoomInMaxOutError();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->zoomController->clearError();
    }break;
    case CCPDF_ZoomController::ZoomError::Error::NO_BIND_PDF:
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->zoomController->clearError();
    }break;
    }
}


bool CCPDFView_MainWindow::zoom(PageZoomCommand command)
{
    if(!pdfServer->zoomController->widget())
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->zoomController->clearError();
        return false;
    }
    bool op_res = false;
    switch(command)
    {
    case PageZoomCommand::ZOOM_IN:
        op_res = pdfServer->zoomController->zoomIn();break;
    case PageZoomCommand::ZOOM_OUT:
        op_res = pdfServer->zoomController->zoomOut();break;
    }
    if(!op_res)
        handleZoomError();
    return op_res;
}

bool CCPDFView_MainWindow::zoom(const double zoomPercentage)
{
    if(!pdfServer->zoomController->widget())
    {
        auto pac = CCPDF_Error_Helper::ErrorMessgageUtils::No_TargetPDF();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
            pac.title, pac.details, this);
        pdfServer->zoomController->clearError();
        return false;
    }
    return pdfServer->zoomController->setZoomPercentage(zoomPercentage);
}

void CCPDFView_MainWindow::opposeHyperWidgetVisible()
{
    hyperWidgetVisible = !hyperWidgetVisible;
    ui->hyper_operate_widget->setVisible(hyperWidgetVisible);
}

void CCPDFView_MainWindow::opposeBookModelVisible()
{
    bookModelVisible = !bookModelVisible;
    ui->bookMarkWidget->setVisible(bookModelVisible);
}

void CCPDFView_MainWindow::updateHistWidget()
{
    if(pdfServer->current_widget())
        histtableWidgetController->update_ui(pdfServer->current_widget()->getRecord());
}

void CCPDFView_MainWindow::updateLinkModel()
{
    if(pdfServer->current_widget())
        pdfServer->linkModelManager->setPage(
            pdfServer->current_widget()->pdf_info->currentPageIndex());
}


void CCPDFView_MainWindow::routeTo(PAGE_INDEX i)
{
    hyperWidgetVisible = true;
    ui->hyper_operate_widget->setVisible(true);
    ui->hpw_pdf_tool_box->setCurrentIndex(i);
}

void CCPDFView_MainWindow::addTheme()
{
    QString fileSelect = CCPDF_FileUtils::SelectFileUtils::selectExsitingFile(
        "选择QSS样式文件", {"qss"}, ".", this);
    if(fileSelect.isEmpty())
        return;
    handleNewTheme(fileSelect);
}


bool CCPDFView_MainWindow::pageNavigate(int page)
{
    bool ops_res = pdfServer->pageNavigator->jump(page);
    if(!ops_res)
    {
        handlePageNavigationError();
        return false;
    }
    updateHistWidget();
    updateLinkModel();
    setCurrentPageText();
    return true;
}

bool CCPDFView_MainWindow::pageNavigate(int page, QPointF p)
{
    bool ops_res = pdfServer->pageNavigator->jump(page, p);
    if(!ops_res)
    {
        handlePageNavigationError();
        return false;
    }
    updateHistWidget();
    updateLinkModel();
    setCurrentPageText();
    return true;
}

bool CCPDFView_MainWindow::pageNavigate(const QString& page)
{
    if(page.isEmpty())
        return false; // clear Input
    auto res = CCPDF_StringParseUtil::parseToInt(page);
    if(res.first)
        return pageNavigate(res.second - 1);
    else
    {
        auto pack = CCPDF_Error_Helper::ErrorMessgageUtils::Invalid_Page_Index_FMT();
        CCPDF_MessgaeBoxUtils::ErrorInform::tellError(pack.title,pack.details,this);
    }
    return false;
}


bool CCPDFView_MainWindow::pageNavigate(PageNavigateCommand m)
{
    bool operate_res = false;
    auto cur = pdfServer->current_widget();
    if(!cur)
        return false;
    switch (m) {
    case PageNavigateCommand::PAGE_NEXT:
        operate_res = pageNavigate(cur->pdf_info->currentPageIndex() + 1);break;
    case PageNavigateCommand::PAGE_PREV:
        operate_res = pageNavigate(cur->pdf_info->currentPageIndex() - 1);break;
    case PageNavigateCommand::PAGE_BEG:
        operate_res = pageNavigate(0);break;
    case PageNavigateCommand::PAGE_END:
        operate_res = pageNavigate(cur->pdf_info->pageCnt() - 1);break;
    }
    if(!operate_res)
    {
        handlePageNavigationError();
    }
    return operate_res;
}

void CCPDFView_MainWindow::updateOldRecord(CCPDF_SinglePDF_Widget* oldWidget)
{
    if(!oldWidget)
        return;
    auto rec = oldWidget->getRecord();
    qDebug() << "Update Old Logging to page " << rec.current_page;
    histRecorder->update_target_Info_record(rec.pdf_Path, rec);
    pdfServer->setStatusText(statusLabel);
    qDebug() << "Update Finish";
}

void CCPDFView_MainWindow::updateBookLibRecord(QString atWhere)
{
    BookLibrary_Record tmp;
    tmp.libPath = atWhere;
    otherServerRecorder->setRecord(
        PDF_SimpleServer_Record::SimpleSercerRecord::BOOKLIB_INFO, tmp);
}

void CCPDFView_MainWindow::udpateCurrentFocusWidgets(CCPDF_SinglePDF_Widget* newWidgets)
{
    pdfServer->updateGlobal(newWidgets, statusLabel);
    pdfPlugins->updateAllBindPdfWidget(newWidgets);
    setCurrentPageText();
}

void CCPDFView_MainWindow::handleBookMarkJump(const int page, const qreal zoomLevel)
{
    pageNavigate(page);
    zoom(zoomLevel);
}

void CCPDFView_MainWindow::handleSearchJump(const int page,QPointF location, const QModelIndex& index)
{
    pageNavigate(page, location);
    const auto res = pdfServer->current_widget();
    if(res)
        res->setSearchIndex(index.row());
}

void CCPDFView_MainWindow::handleNewTheme(const QString name)
{
    themeHolder->enRecord(name);
    setStyleSheet(themeHolder->getInUsedOne());
    themeActionHelper->addPath(name);
    CCPDF_Theme_Action* action = new CCPDF_Theme_Action(ui->theme_menu);
    action->setText(themeActionHelper->getName(name));
    ui->theme_menu->addAction(action);
    connect(action, &CCPDF_Theme_Action::tellSelfName,
            this, &CCPDFView_MainWindow::switchToTheme);
    connect(action, &CCPDF_Theme_Action::tellRemoveThis,
            this, &CCPDFView_MainWindow::handleRemoveTheme);
    setStyleSheet(themeHolder->getStyleSheet(name));
}


void CCPDFView_MainWindow::switchToTheme(const QString name)
{
    QString path = themeActionHelper->getPath(name);
    setStyleSheet(themeHolder->getStyleSheet(path));
}

void CCPDFView_MainWindow::handleRemoveTheme(const QString name)
{
    QString path = themeActionHelper->getPath(name);
    themeHolder->deRecord(path);
    setStyleSheet(themeHolder->getInUsedOne());
    themeActionHelper->removePath(path);
    auto actions = ui->theme_menu->actions();
    for(auto& action : actions){
        if(name == action->text())
            ui->theme_menu->removeAction(action);
    }
    setStyleSheet(themeHolder->getInUsedOne());
}

void CCPDFView_MainWindow::closeEvent(QCloseEvent* e[[maybe_unused]])
{
    qDebug() << "MainWindow closing, clearing the connections";
}

void CCPDFView_MainWindow::keyPressEvent(QKeyEvent* e)
{
    windowEventHelper->setModifiers(e->modifiers(), WindowEventHelper::Monitor::Global);
    windowEventHelper->doKeyProcess(e->key());
}

void CCPDFView_MainWindow::keyReleaseEvent(QKeyEvent*)
{
    windowEventHelper->clearModifiers(WindowEventHelper::Monitor::Global);
}

void CCPDFView_MainWindow::wheelEvent(QWheelEvent* e)
{
    windowEventHelper->doMouseProcess(
    e->angleDelta().y() > 0 ?
    WindowEventHelper::MouseProcess::WHEEL_UP:  // if y > 0 -> Up
    WindowEventHelper::MouseProcess::WHEEL_DOWN); // else Down
}

void CCPDFView_MainWindow::dragEnterEvent(QDragEnterEvent* env)
{
    env->acceptProposedAction();
}

void CCPDFView_MainWindow::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return; // for no data's here
    }
    for(auto& url : urls)
    {
        QString mimePath = url.toLocalFile();
        if(CCPDF_FileUtils::Prefix_Precheck::isPDFFile(mimePath)) // if is PDF
        {
            loadPDF(mimePath);
            continue;
        }
        QString linkPath = CCPDF_FileUtils::Prefix_Precheck::parseSymbolLinkPdfPath(mimePath);
        if(!mimePath.isEmpty())
        {
            loadPDF(linkPath);
            continue;
        }
    }
}

void CCPDFView_MainWindow::on_page_navigate_lineEdit_returnPressed()
{
    pageNavigate(ui->page_navigate_lineEdit->text());
}

CCPDFView_MainWindow::~CCPDFView_MainWindow()
{
    qDebug() << "MainWindow finish closing, is clearing buffers";
    delete ui;
}

void CCPDFView_MainWindow::on_historical_tableWidget_customContextMenuRequested(
    const QPoint &pos)
{
    histtableWidgetController->setExecutionPoint(pos);
    histtableWidgetController->doMenuShowUp();
}

void CCPDFView_MainWindow::on_historical_tableWidget_itemClicked(QTableWidgetItem *item)
{
    histtableWidgetController->doItemClick(item);
}

// Plugins Related
void CCPDFView_MainWindow::initPluginMenuUi()
{
#ifdef SUPPORT_TESS_OCR
    pdfPlugins->OCRUiManager->initOCR_Ui(ui->textFetch_tabWidget);
#endif
    return;
}

void CCPDFView_MainWindow::initPluginHistAndConfig()
{
    pdfPlugins->setPluginExeWidgets(ui->translation_widget, CCPDF_ExternalPlugins::CurrentSupportPlugin::TRANSLATION);
#ifdef SUPPORT_TESS_OCR
    pdfPlugins->OCRUiManager->setOCR(pdfPlugins->tessHandle.get());
#endif
    pdfPlugins->pluginHist->setPluginInfo_LoggerPath(__DEF_PLUGIN_PDF_LOG);
    pdfPlugins->pluginHist->readPluginInfo_HistoricalRecord();
}
