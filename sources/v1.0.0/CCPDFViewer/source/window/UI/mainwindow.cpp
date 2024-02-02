#include <QMimeData>
#include <QFileSystemModel>
#include <QPushButton>
#include <QLineEdit>
#include <QInputDialog>
#include <QProcess>
#include "ThemeHandler.h"
#include "editpdf_mainwindow.h"
#include "helpmainwindow.h"
#include "mainwindow.h"
#include "PDF_MessageBox.h"
#include "notehandle.h"
#include "ocr_mainwindow.h"
#include "pdf_Reactor.h"
#include "qclipboard.h"
#include "qevent.h"
#include "qlabel.h"
#include "ui_mainwindow.h"
#include "pdf_historicalrecord.h"
#include "eventhandler.h"
#include "PDF_Utils.h"
#include "pdf_fileviewmanager.h"
const char* MAIN_WINDOW_NAME = "CC_PDF阅读器";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    initToolBar();
    initCore();
    initConnection();
    initEventHandle();
    loadLastOpenFile();
    windowTitleSetterAccordingPDF();
    operateHyperWidget();
    initIcon();
    initNotehandle();
    setEdited_HyperW();
    initThemeMenu();
    loadQSS();
}

bool MainWindow::loadQSS()
{
    themeHandle->setQSSByGivenIndex(histManager->getThemeIndex());
    return true;
}

void MainWindow::initThemeMenu()
{
    QStringList m = themeHandle->getTheAcceptableThemes();
    for(int i = 0; i < m.size(); i++)
    {
        QAction* act = new QAction(ui->theme_menu);
        QPushButton* btn = new QPushButton(ui->theme_btns_widget);
        btn->setMinimumHeight(50);
        ui->theme_btns_widget->layout()->addWidget(btn);
        ui->theme_menu->addAction(act);
        act->setText(m[i]);
        act->setIcon(QIcon(":/toolbar_icon/pic/styleSwitch.png"));
        btn->setIcon(QIcon(":/toolbar_icon/pic/styleSwitch.png"));
        btn->setText(m[i]);
        switch(i)
        {
            case 0:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::brightTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::brightTheme);
                break;
            case 1:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::darkTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::darkTheme);
                break;
            case 2:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::AMOLEDTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::AMOLEDTheme);
                break;
            case 3:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::AQUATheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::AQUATheme);
                break;
            case 4:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::ConsoleTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::ConsoleTheme);
                break;
            case 5:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::ElegantDarkTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::ElegantDarkTheme);
                break;
            case 6:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::MacOSTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::MacOSTheme);
                break;
            case 7:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::ManjaroMixTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::ManjaroMixTheme);
                break;
            case 8:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::MaterialDarkTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::MaterialDarkTheme);
                break;
            case 9:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::NeonButtonsTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::NeonButtonsTheme);
                break;
            case 10:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::UbuntuTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::UbuntuTheme);
                break;
            case 11:connect(act, &QAction::triggered, themeHandle, &ThemeHandle::noTheme);
                connect(btn, &QPushButton::clicked, themeHandle, &ThemeHandle::noTheme);
                break;
        }
    }
}


bool MainWindow::initCore()
{
    this->statusInfoWidget = new QLabel(this);
    this->grabKeyboard(); // 强监控
    setFocus();
    QPalette pa;
    pa.setColor(QPalette::ColorRole::Window, QColor(255,255,255));
    ui->image_label->setPalette(pa);
    ui->statusbar->addWidget(this->statusInfoWidget);
    histManager = new PDF_HistoricalRecord;
    histManager->readRequired();
    initHyperWidget();
    themeHandle = new ThemeHandle(this);
    themeHandle->setConfigTheWidget(this);
    return true;
}

bool MainWindow::initIcon()
{
    // mainWindow
    this->setWindowIcon(QIcon(":/windowIcon/icon/mainWindow.ico"));
    return true;
}

bool MainWindow::initNotehandle()
{
    this->noteHandle = histManager->configNoteHandle();
    return true;
}

bool MainWindow::initToolBar()
{
    // file open
    QPushButton* open_btn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(open_btn);
    open_btn->setToolTip("加载PDF");
    open_btn->setIcon(QIcon(":/toolbar_icon/icon/open.ico"));
    connect(open_btn, &QPushButton::clicked, this, &MainWindow::loadPDFByFileDialog);
    ui->toolBar->addSeparator();
    // page related
    QPushButton* editGuard = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(editGuard);
    editGuard->setToolTip("保护/开启跳转页码");
    editGuard->setIcon(QIcon(":/toolbar_icon/pic/editGuard.png"));
    connect(editGuard, &QPushButton::clicked, this, &MainWindow::editPageIndexEnable);

    pageIndexEdit = new QLineEdit(ui->toolBar);
    pageIndexEdit->setMaximumWidth(100);
    ui->toolBar->addWidget(pageIndexEdit);
    pageIndexEdit->setValidator(new QIntValidator(pageIndexEdit));
    connect(pageIndexEdit, &QLineEdit::textChanged, this, &MainWindow::handlePageIndexEdit);
    connect(pageIndexEdit, &QLineEdit::returnPressed, this, &MainWindow::editPageIndexEnable);

    QPushButton* to_prev_tn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(to_prev_tn);
    to_prev_tn->setToolTip("前一页");
    to_prev_tn->setIcon(QIcon(":/toolbar_icon/pic/toPrev.png"));
    connect(to_prev_tn, &QPushButton::clicked, this, &MainWindow::toPrevPage);

    QPushButton* to_next_tn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(to_next_tn);
    to_next_tn->setToolTip("后一页");
    to_next_tn->setIcon(QIcon(":/toolbar_icon/pic/toNext.png"));
    connect(to_next_tn, &QPushButton::clicked, this, &MainWindow::toNextPage);
    ui->toolBar->addSeparator();
    // functional
    QPushButton* refresh_btn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(refresh_btn);
    refresh_btn->setToolTip("刷新");
    refresh_btn->setIcon(QIcon(":/toolbar_icon/pic/refresh.png"));
    connect(refresh_btn, &QPushButton::clicked, this, &MainWindow::refresh);

    QPushButton* for_hyper = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(for_hyper);
    for_hyper->setToolTip("更多...");
    for_hyper->setIcon(QIcon(":/toolbar_icon/pic/forMore.png"));
    connect(for_hyper, &QPushButton::clicked, this, &MainWindow::operateHyperWidget);
    ui->toolBar->addSeparator();

    // zooming
    QPushButton* btn_zoomIn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_zoomIn);
    btn_zoomIn->setToolTip("放大");
    btn_zoomIn->setIcon(QIcon(":/toolbar_icon/pic/zoomIn.png"));
    connect(btn_zoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);

    QPushButton* btn_zoomOut = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_zoomOut);
    btn_zoomOut->setToolTip("缩小");
    btn_zoomOut->setIcon(QIcon(":/toolbar_icon/pic/zoomOut.png"));
    connect(btn_zoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);
    ui->toolBar->addSeparator();
    // page mode view
    QPushButton* btn_changePageMode = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_changePageMode);
    btn_changePageMode->setToolTip("改变页模式");
    btn_changePageMode->setIcon(QIcon(":/toolbar_icon/pic/pageMode.png"));
    connect(btn_changePageMode, &QPushButton::clicked, this, &MainWindow::changePageMode);
    ui->toolBar->addSeparator();
    // edit
    QPushButton* btn_editPDF = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_editPDF);
    btn_editPDF->setToolTip("编辑当前页");
    btn_editPDF->setIcon(QIcon(":/toolbar_icon/pic/editPDF.png"));
    connect(btn_editPDF, &QPushButton::clicked, this, &MainWindow::openEditWindow);
    ui->toolBar->addSeparator();
    // OCR
    QPushButton* ocrSettings = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(ocrSettings);
    ocrSettings->setToolTip("打开OCR配置窗口");
    ocrSettings->setIcon(QIcon(":/toolbar_icon/pic/ocr_settings.png"));
    connect(ocrSettings, &QPushButton::clicked, this, &MainWindow::openOCRWindow);

    QPushButton* ocrCurPage = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(ocrCurPage);
    ocrCurPage->setToolTip("OCR当前页面");
    ocrCurPage->setIcon(QIcon(":/toolbar_icon/pic/OCR_current.png"));
    connect(ocrCurPage, &QPushButton::clicked, this, &MainWindow::on_btn_startMissionDirect_clicked);
    ui->toolBar->addSeparator();

    // noteBook
    QPushButton* btn_addOrOpenNote = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_addOrOpenNote);
    btn_addOrOpenNote->setToolTip("打开或者创建笔记");
    btn_addOrOpenNote->setIcon(QIcon(":/toolbar_icon/pic/notebookOpenAdd.png"));
    connect(btn_addOrOpenNote, &QPushButton::clicked, this, &MainWindow::openAddNoteBook);

    QPushButton* btn_releaseNote = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_releaseNote);
    btn_releaseNote->setToolTip("解绑笔记");
    btn_releaseNote->setIcon(QIcon(":/toolbar_icon/pic/notebookRelease.png"));
    connect(btn_releaseNote, &QPushButton::clicked, this, &MainWindow::removeNoteBook);

    QPushButton* btnSwitch = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btnSwitch);
    btnSwitch->setToolTip("更换绑定笔记");
    btnSwitch->setIcon(QIcon(":/toolbar_icon/pic/switchNoteBook.png"));
    connect(btnSwitch, &QPushButton::clicked, this, &MainWindow::switchNoteBook);
    ui->toolBar->addSeparator();

    // notebookTarget
    QPushButton* btn_addTarget = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_addTarget);
    btn_addTarget->setToolTip("增加笔记工具");
    btn_addTarget->setIcon(QIcon(":/toolbar_icon/pic/editTargetHandleAdd.png"));
    connect(btn_addTarget, &QPushButton::clicked, this, &MainWindow::addHandle);

    QPushButton* btn_removeTarget = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_removeTarget);
    btn_removeTarget->setToolTip("去除笔记工具");
    btn_removeTarget->setIcon(QIcon(":/toolbar_icon/pic/editTargetHandleShowRemove.png"));
    connect(btn_removeTarget, &QPushButton::clicked, this, &MainWindow::removeHandle);

    QPushButton* btn_showTarget = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_showTarget);
    btn_showTarget->setToolTip("查看当前的笔记工具");
    btn_showTarget->setIcon(QIcon(":/toolbar_icon/pic/editTargetHandleShow.png"));
    connect(btn_showTarget, &QPushButton::clicked, this, &MainWindow::showhandles);
    ui->toolBar->addSeparator();

    // style
    QPushButton* btn_styleshift = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_styleshift);
    btn_styleshift->setToolTip("切换主题");
    btn_styleshift->setIcon(QIcon(":/toolbar_icon/pic/styleSwitch.png"));
    connect(btn_styleshift, &QPushButton::clicked, this, &MainWindow::changeStyleDirect);
    ui->toolBar->addSeparator();

    // about
    QPushButton* btn_about = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_about);
    btn_about->setToolTip("关于这个软件...");
    btn_about->setIcon(QIcon(":/toolbar_icon/pic/btn_about.png"));
    connect(btn_about, &QPushButton::clicked, this, &MainWindow::viewAbout);
    ui->toolBar->addSeparator();

    // help
    QPushButton* btn_help = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(btn_help);
    btn_help->setToolTip("关于这个软件...");
    btn_help->setIcon(QIcon(":/toolbar_icon/pic/help.png"));
    connect(btn_help, &QPushButton::clicked, this, &MainWindow::viewHelp);
    ui->toolBar->addSeparator();


    return true;
}


bool MainWindow::initHyperWidget()
{
    fileViewManager = new PDF_FileViewManager(ui->tableWidget_filehist);
    configHistoryWidget_hyperW();
    this->libraryModel = new PDF_FileSystemModel(this);
    configLibraryModel_hyperW();
    return true;
}

bool MainWindow::configHistoryWidget_hyperW()
{
    ui->tableWidget_filehist->setContextMenuPolicy(Qt::CustomContextMenu);
    // menus
    histFileViewMenu = new QMenu(ui->tableWidget_filehist);

    QAction* delHist = new QAction(ui->tableWidget_filehist);
    histFileViewMenu->addAction(delHist);
    connect(delHist, &QAction::triggered, this, &MainWindow::removeHistory);
    delHist->setText("删除这个历史记录");
    return true;
}

bool MainWindow::configLibraryModel_hyperW()
{
    QString path = histManager->getBookModeFileDirPath();
    path = path.remove("\n");
    if(path.isEmpty())
        return false;

    this->libraryModel->setRootPath(path);
    auto rootModelIndex = this->libraryModel->index(path);
    this->libraryModel->setNameFilters(QStringList("*.pdf"));
    this->libraryModel->setReadOnly(true);
    ui->treeView_library->setModel(this->libraryModel);
    ui->treeView_library->setRootIndex(rootModelIndex);
    return true;
}


bool MainWindow::initConnection()
{
    this->actionHandler = new ActionHandler<MainWindow>;
    actionHandler->insertConnections(ui->action_loadPDF, &MainWindow::loadPDFByFileDialog);
    actionHandler->insertConnections(ui->action_zoomin, &MainWindow::zoomIn);
    actionHandler->insertConnections(ui->action_zoomout, &MainWindow::zoomOut);
    actionHandler->insertConnections(ui->action_show_or_hide_advamced, &MainWindow::operateHyperWidget);
    actionHandler->insertConnections(ui->action_setLibraryPath, &MainWindow::loadLibraryPath);
    actionHandler->insertConnections(ui->action_clearHistory, &MainWindow::clearHistory);
    actionHandler->insertConnections(ui->action_createNewNote, &MainWindow::openAddNoteBook);
    actionHandler->insertConnections(ui->action_bindNote, &MainWindow::bindNoteBook);
    actionHandler->insertConnections(ui->action_openNote_2, &MainWindow::openAddNoteBook);
    actionHandler->insertConnections(ui->action_switchNote, &MainWindow::switchNoteBook);
    actionHandler->insertConnections(ui->action_removeNote, &MainWindow::removeNoteBook);
    actionHandler->insertConnections(ui->action_addHandleType, &MainWindow::addHandle);
    actionHandler->insertConnections(ui->action_removeHandleType, &MainWindow::removeHandle);
    actionHandler->insertConnections(ui->action_checkhandle, &MainWindow::showhandles);
    actionHandler->insertConnections(ui->action_viewAbout,  &MainWindow::viewAbout);
    actionHandler->insertConnections(ui->action_ocrsettingWindow, &MainWindow::openOCRWindow);
    actionHandler->insertConnections(ui->action_ocrCurPage, &MainWindow::on_btn_startMissionDirect_clicked);
    actionHandler->insertConnections(ui->action_viewhelp,  &MainWindow::viewHelp);
    actionHandler->insertConnections(ui->action_randStyle, &MainWindow::randStyle);
    actionHandler->insertConnections(ui->action_defaultStyle, &MainWindow::setAsDefaultStyle);
    actionHandler->insertConnections(ui->action_singlePage, &MainWindow::singlePageMode);
    actionHandler->insertConnections(ui->action_multiPage, &MainWindow::multiPageMode);
    actionHandler->connectAll(this);
    return true;
}

void MainWindow::initEventHandle()
{
    // Key Events binding
    keyhandle = new KeyBoardEventHandler;
    this->pageFunctors.push_back((
        new Page_Reactor())->setPageReactor(std::bind(&MainWindow::toNextPage, this)
                                                      )); // [0]
    this->pageFunctors.push_back((
        new Page_Reactor())->setPageReactor(std::bind(&MainWindow::toPrevPage, this)
                                                      )); // [1]

    this->pageFunctors.push_back((
        new Page_Reactor())->setPageReactor(std::bind(&MainWindow::changePageMode, this)
    )); // [2]

    keyhandle->registerEventHandle(Qt::Key::Key_Right, this->pageFunctors[0]);
    keyhandle->registerEventHandle(Qt::Key::Key_D, this->pageFunctors[0]);
    keyhandle->registerEventHandle(Qt::Key::Key_Left, this->pageFunctors[1]);
    keyhandle->registerEventHandle(Qt::Key::Key_A, this->pageFunctors[1]);
    keyhandle->registerEventHandle(Qt::Key::Key_P, this->pageFunctors[2]);

    // view and themes
    this->viewWidgetFunctors.push_back(
    (new ViewWidget_Reactor())
    ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier|Qt::KeyboardModifier::ShiftModifier)
    ->setViewFunctor(std::bind(&MainWindow::operateHyperWidget, this))
    ); // [0]

    this->viewWidgetFunctors.push_back(
        (new ViewWidget_Reactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)
            ->setViewFunctor(std::bind(&MainWindow::viewHelp, this))
        ); // [1]

    this->viewWidgetFunctors.push_back(
        (new ViewWidget_Reactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier|Qt::KeyboardModifier::ShiftModifier)
            ->setViewFunctor(std::bind(&MainWindow::on_btn_startMissionDirect_clicked, this))
        ); // [2]

    this->viewWidgetFunctors.push_back(
        (new ViewWidget_Reactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier|Qt::KeyboardModifier::ShiftModifier)
            ->setViewFunctor(std::bind(&MainWindow::randStyle, this))
        ); // [3]

    this->viewWidgetFunctors.push_back(
        (new ViewWidget_Reactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier|Qt::KeyboardModifier::ShiftModifier)
            ->setViewFunctor(std::bind(&MainWindow::changeStyleDirect, this))
        ); // [4]

    keyhandle->registerEventHandle(Qt::Key::Key_V, this->viewWidgetFunctors[0]);
    keyhandle->registerEventHandle(Qt::Key::Key_H, this->viewWidgetFunctors[1]);
    keyhandle->registerEventHandle(Qt::Key::Key_O, this->viewWidgetFunctors[2]);
    keyhandle->registerEventHandle(Qt::Key::Key_R, this->viewWidgetFunctors[3]);
    keyhandle->registerEventHandle(Qt::Key::Key_T, this->viewWidgetFunctors[4]);

    // mouseWheel's binding
    mouseWheelhandler = new MouseWheelEventHandle;
    this->zoomFunctors.push_back(
        (new Zoom_Reactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)
            ->setZoomReactor(std::bind(&MainWindow::zoomIn, this))
        ); // [0]
    this->zoomFunctors.push_back(
        (new Zoom_Reactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)
            ->setZoomReactor(std::bind(&MainWindow::zoomOut, this))
        ); // [1]

    mouseWheelhandler->registerEventHandle(MouseWheelEventHandle::MouseWheelType::UP, this->zoomFunctors[0]);
    mouseWheelhandler->registerEventHandle(MouseWheelEventHandle::MouseWheelType::DOWN, this->zoomFunctors[1]);

}

void MainWindow::windowTitleSetterAccordingPDF()
{
    QString curPDF = ui->pdf_view->currentPDFPath();
    if(curPDF.isEmpty())
        this->setWindowTitle(MAIN_WINDOW_NAME);
    else
        this->setWindowTitle(PDF_LocationDefaults::getFileNameByPath(curPDF));
}

void MainWindow::refresh()
{
    this->grabWindowKey = !this->grabWindowKey;
    this->grabWindowKey ? this->grabKeyboard() : this->releaseKeyboard();
}

bool MainWindow::removeHistory()
{
    if(!this->currentFocus)
        return false;
    histManager->removeHist(this->currentFocus->text());
    fileViewManager->removeTarget(this->currentFocus);
    this->currentFocus = nullptr;
    return true;
}


int MainWindow::currentPage()
{
    return ui->pdf_view->currentPage();
}

void MainWindow::toNextPage()
{
    if(!toPage(currentPage() + 1))
    {
        if(QMessageBox::Ok == QMessageBox::information(this, "最后一页了","当前已经是最后一页，是否跳转到第一页？"))
        {
            toPage(0);
        }
    }
}

void MainWindow::toPrevPage()
{
    if(!toPage(currentPage() - 1))
    {
        if(QMessageBox::Ok == QMessageBox::information(this, "第一页了","当前已经是第一页，是否跳转到最后一页？"))
        {
            toPage(ui->pdf_view->currentPageCnt() - 1);
        }
    }
}

bool MainWindow::toPage(int page)
{
    if(!ui->pdf_view->isViewerAccessible())
        return false;
    bool state = ui->pdf_view->toPage(page);
    if(state)
    {
        ui->statusbar->setToolTip(ui->pdf_view->getCurruntPDFDescriptions());
        this->statusInfoWidget->setText(ui->pdf_view->getCurruntPDFDescriptions());
        pageIndexEdit->setText(QString::number(currentPage()));
        this->histManager->updateFileIndex(ui->pdf_view->currentPDFPath(), ui->pdf_view->currentPage());
        setEdited_HyperW();
    }
    return state;
}


bool MainWindow::loadPDFByFileDialog()
{
    if(!ui->pdf_view->loadPDF())
        return false;
    return true;
}

bool MainWindow::loadPDF(QString path)
{
    int requiredPage = 0;
    if(!PDF_HistoricalRecord::isPathIndicatesPDF(path))
        return false;
    if(histManager->getHistoryFilePaths().contains(path))
    {
        requiredPage = histManager->getIndex(path);
        histManager->removeHist(path);
    }
    if(!ui->pdf_view->loadPDF(CCPDF_View::LoadingMethod::BY_GIVEN_STR, path))
    {
        LOAD_CRITI_MSGBX(this, ui->pdf_view->getErrorString());
        return false;
    }
    histManager->addHistFile(ui->pdf_view->currentPDFPath(),requiredPage);
    editPageIndexEnable();
    successLoad_windowBehave();
    configNoteBookAddWidget();
    return true;
}

void MainWindow::configNoteBookAddWidget()
{
    if(!histManager->hasNoteBook(ui->pdf_view->currentPDFPath()))
    {
        ui->btn_addOrOpenNotes->setText("创建笔记");
        ui->noteBookPathEdit->setText("尚无笔记");
    }
    else
    {
        ui->btn_addOrOpenNotes->setText("打开笔记");
        ui->noteBookPathEdit->setText("绑定笔记:> " + histManager->getNoteBook(ui->pdf_view->currentPDFPath()));
    }
}


void MainWindow::successLoad_windowBehave()
{
    int currentPageIndex = histManager->getIndex(ui->pdf_view->currentPDFPath());
    ui->pdf_view->toPage(currentPageIndex);
    // config the windowBehavior
    windowTitleSetterAccordingPDF();
    fileViewManager->configFiles(histManager->getHistoryFilePaths());
    ui->statusbar->setToolTip(ui->pdf_view->getCurruntPDFDescriptions());
    pageIndexEdit->setText(QString::number(currentPageIndex));
    this->statusInfoWidget->setText(ui->pdf_view->getCurruntPDFDescriptions());
}


bool MainWindow::loadLibraryPath()
{
    QString path;
    if(PDF_LocationDefaults::getPathDir(path, this))
    {
        histManager->setBookModeFileDirPath(path);
        configLibraryModel_hyperW();
        return true;
    }
    return false;
}

bool MainWindow::clearHistory()
{
    if(QMessageBox::Yes != QMessageBox::question(this, "确定？","你真的要清除历史记录吗？？？真的会失去很久！"))\
        return false;
    histManager->clearHist();
    fileViewManager->configFiles(histManager->getHistoryFilePaths());
    return true;
}

void MainWindow::setEdited_HyperW()
{
    ui->image_label->setPixmap(
        QPixmap::fromImage(this->ui->pdf_view->getImagedFile()).scaled(
            ui->image_label->size(), Qt::KeepAspectRatio
            )
        );
}

bool MainWindow::openEditWindow()
{
    if(!this->ui->pdf_view->isViewerAccessible())
        return false;
    if(!this->editWindow)
    {
        this->editWindow = new EditPDF_MainWindow(this);
    }
    this->editWindow->setCurrentEditingImage(this->ui->pdf_view->getImagedFile(), ui->pdf_view->currentPDFPath());
    this->editWindow->show();
    return true;
}

void MainWindow::initOCRWindow()
{
    if(!this->ui->pdf_view->isViewerAccessible())
        return;
    if(!this->ocrWindow)
    {
        this->ocrWindow = new OCR_MainWindow(this);
    }
    // connect(this->ocrWindow, &OCR_MainWindow::destroyed, this, &MainWindow::handleTheAutoDeletedObject);
    connect(this->ocrWindow, &OCR_MainWindow::handInTheOCRResult, this, &MainWindow::handleOCRRes);
    connect(this->ocrWindow, &OCR_MainWindow::enableStartRecognize, this, &MainWindow::setIsableDirectOCR);
    connect(this->ocrWindow, &OCR_MainWindow::configPathFileChange, this, &MainWindow::configOCRFromChange);
    this->ocrWindow->setOCRtExePath(histManager->getOCREXE());
    this->ocrWindow->setImageSaveDirPath(histManager->getOCRImageDir());
    this->ocrWindow->setResultSaveDirPath(histManager->getOCRResDir());
    this->ocrWindow->refreshPathEdit();
    this->ocrWindow->bindImage(this->ui->pdf_view->getImagedFile(), ui->pdf_view->currentPDFPath());
}

void MainWindow::configOCRFromChange(QStringList *l)
{
    if(l->size() != 3)
    {
        delete l;
        return;
    }
    histManager->setOCREXE((*l)[0]);
    histManager->setOCRImageDir((*l)[1]);
    histManager->setOCRResDir((*l)[2]);
    delete l;
    qDebug() << "configSuccessOCR";
}


bool MainWindow::openOCRWindow()
{
    initOCRWindow();
    this->ocrWindow->show();
    return true;
}

bool MainWindow::zoomIn()
{
    zoomPDF(zoomFactor * eachZoomInPercentage);
    zoomFactor*= eachZoomInPercentage;
    return true;
}

bool MainWindow::zoomOut()
{
    zoomPDF(zoomFactor * eachZoomOutPercentage);
    zoomFactor *= eachZoomOutPercentage;
    return true;
}

void MainWindow::zoomPDF(qreal factor)
{
    if(!ui->pdf_view->isViewerAccessible())
        return;
    ui->pdf_view->zoomPage(factor);
}


bool MainWindow::recordLastHistory()
{
    histManager->setThemeIndex(themeHandle->getCurrentIndex());
    histManager->recordNotehandle(this->noteHandle);
    return histManager->writeRequired();
}


bool MainWindow::loadLastOpenFile()
{
    // file history empty
    if(histManager->getHistoryFilePaths().empty())
        return loadPDFByFileDialog();

    for(int loading_index = histManager->getHistoryFilePaths().size() - 1; loading_index >=0; loading_index--)
    {
        QString histPDF = histManager->getHistoryFilePaths()[loading_index];
        if(histPDF.isEmpty())
            return loadPDFByFileDialog();
        else
        {
            if(loadPDF(histPDF))
                return true;
            else
                histManager->getHistoryFilePaths().removeOne(histPDF);
        }
    }
    return false;
}

bool MainWindow::operateHyperWidget()
{
    this->viewHyperWidget = !this->viewHyperWidget;
    ui->hyperWidget->setVisible(this->viewHyperWidget);
    if(this->viewHyperWidget)
        ui->action_show_or_hide_advamced->setText("隐藏高级模块");
    else
        ui->action_show_or_hide_advamced->setText("显示高级模块");
    return true;
}

void MainWindow::editPageIndexEnable()
{
    this->shallEditPageIndex = !this->shallEditPageIndex;
    pageIndexEdit->setEnabled(this->shallEditPageIndex);
    refresh();
}

bool MainWindow::changePageMode()
{
    if(!this->isSinglePage)
        singlePageMode();
    else
        multiPageMode();
    return true;
}

bool MainWindow::singlePageMode()
{
    ui->pdf_view->setPageMode(CCPDF_View::PageViewingMode::SinglePage);
    isSinglePage = true;
    return true;
}
bool MainWindow::multiPageMode()
{
    ui->pdf_view->setPageMode(CCPDF_View::PageViewingMode::MutliPage);
    // refresh
    toPage(ui->pdf_view->currentPage() + 1);
    toPage(ui->pdf_view->currentPage() - 1);
    isSinglePage = false;
    return true;
}

bool MainWindow::openAddNoteBook()
{
    QString getPath;
    QString pdf = ui->pdf_view->currentPDFPath();
    bool state = false;
    if(!histManager->hasNoteBook(pdf))
    {
        state = PDF_LocationDefaults::getSavingFileName(getPath, this);
        if(!state)
            return false;
        if(!PDF_LocationDefaults::isFileExsits(getPath))
            PDF_NoteCreator::createFile(getPath);
        histManager->setNoteBook(pdf, getPath, true);
    }
    return processNoteBook();
}

bool MainWindow::bindNoteBook()
{
    QString getPath;
    QString pdf = ui->pdf_view->currentPDFPath();
    bool state = false;
    if(!histManager->hasNoteBook(pdf))
    {
        state = PDF_LocationDefaults::getOpenFileName(getPath, this);
        if(!state)
            return false;
        histManager->setNoteBook(pdf, getPath, true);
    }
    else
    {
        QMessageBox::information(this, "产生冲突！",
        "已经绑定了笔记！:> " + histManager->getNoteBook(pdf) + "想要解绑请点击换绑按钮!");
        return false;
    }
    qDebug() << getPath;
    return processNoteBook();
}

bool MainWindow::switchNoteBook()
{
    QString getPath;
    QString pdf = ui->pdf_view->currentPDFPath();
    if(!histManager->hasNoteBook(pdf))
    {
        openAddNoteBook();
        qDebug() << "创建";
        return true;
    }
    else
    {
        histManager->removeNoteBook(pdf);
        if(QMessageBox::Yes == QMessageBox::question(this, "是否打算新建笔记?", "是否打算新建笔记"))
            return openAddNoteBook();
        else
            return bindNoteBook();
    }
}

bool MainWindow::removeNoteBook()
{
    QString pdf = ui->pdf_view->currentPDFPath();
    if(!histManager->hasNoteBook(pdf))
    {
        QMessageBox::critical(this, "错误", "你还没有为这个PDF绑定笔记!");
        return false;
    }

    QString notebook = histManager->getNoteBook(pdf);
    histManager->removeNoteBook(ui->pdf_view->currentPDFPath());
    configNoteBookAddWidget();
    QMessageBox::information(this, "注意","你已经解除了" + ui->pdf_view->currentPDFPath() + "与" + notebook + "的绑定关系");
    return true;
}

bool MainWindow::processNoteBook()
{
     QString pdf = ui->pdf_view->currentPDFPath();
    if(!histManager->hasNoteBook(pdf))
    {
        if(!switchNoteBook())
            return false;
    }
    QString noteBook = histManager->getNoteBook(pdf);
    QString exe = this->noteHandle->getHandleExe(noteBook);
    if(exe.isEmpty())
    {
        auto res = QMessageBox::question(this, "注意！",
        "你尚未配备对应于" + PDF_LocationDefaults::getSuffixOfFile(noteBook) + "的EXE文件,是否指定?");
        if(res != QMessageBox::Yes)
            return false;
        if(!addHandle())
            return false;
        exe = this->noteHandle->getHandleExe(noteBook);
    }
    QProcess::startDetached(exe, QStringList(noteBook));
    qDebug() << exe << "will handle " << noteBook;
    return true;
}

bool MainWindow::addHandle()
{
    QString suf = PDF_LocationDefaults::getDesktopLocation();
    QMessageBox::information(this, "下面选择一个代表的后缀文件","下面选择一个代表的后缀文件");
    bool state = PDF_LocationDefaults::getOpenFileNameSelfDef(suf, this, "选择一个代表后缀文件","","");
    if(!state)
        return false;
    QString suffix = PDF_LocationDefaults::getSuffixOfFile(suf);
    QString exe;
    QMessageBox::information(this, "选择文件","下面选择一个可以显示这个后缀文件的启动文件");
    state = PDF_LocationDefaults::getOpenFileNameSelfDef(exe, this, "选择一个启动文件","","笔记启动文件(*.exe)");
    if(!state)
        return false;
    noteHandle->setHandler(suffix,exe);
    return true;
}

bool MainWindow::removeHandle()
{
    QString suf = QInputDialog::getItem(this,
                                        "选择删除处理的类型文件",
                                        "选择删除处理的类型文件",
                                        noteHandle->getCurrentRegisterSuffix(),
                                        0,false);

    noteHandle->removeHandler(suf);
    return true;
}

bool MainWindow::switchHandle()
{
    if(!addHandle())
        return false;
    return removeHandle();
}

bool MainWindow::showhandles()
{
    QMessageBox::information(this, "展示", noteHandle->getDes());
    return true;
}


void MainWindow::keyPressEvent(QKeyEvent* env)
{
    keyhandle->setCurrentModifiers(env->modifiers());
    mouseWheelhandler->setCheckModifiers(env->modifiers());
    keyhandle->doProcess(env->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent*)
{
    keyhandle->clearModifiers();
    mouseWheelhandler->clearModifiers();
}


void MainWindow::wheelEvent(QWheelEvent* env)
{
    mouseWheelhandler->doProcess(
        env->angleDelta().y() > 0 ?
            MouseWheelEventHandle::MouseWheelType::UP : MouseWheelEventHandle::MouseWheelType::DOWN);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* env)
{
    env->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return; // for no data's here
    }
    for(auto& url : urls)
    {
        QString mimePath = url.toLocalFile();
        if(PDF_HistoricalRecord::isPathIndicatesPDF(mimePath)) // if is PDF
        {
            loadPDF(mimePath);
        }
    }
    fileViewManager->configFiles(histManager->getHistoryFilePaths());
    fileViewManager->configTableWidget();
}


bool MainWindow::releaseHeapSource()
{
    for(auto& handle : this->pageFunctors)
        delete handle;

    for(auto& handle : this->zoomFunctors)
        delete handle;

    for(auto& handle : this->viewWidgetFunctors)
        delete handle;

    delete this->editWindow;
    delete this->histManager;
    delete this->actionHandler;
    delete this->noteHandle;
    delete this->mouseWheelhandler;
    delete this->keyhandle;
    return true;
}

bool MainWindow::viewAbout()
{
    QMessageBox box;
    box.addButton(QMessageBox::Button::Close);
    box.setText("hello!这里是CCPDF阅读器！");
    box.setIconPixmap(QPixmap::fromImage(QImage(":/toolbar_icon/pic/About.png").scaled(QSize(64, 64))));
    box.exec();
    return true;
}

bool MainWindow::viewHelp()
{
    if(!this->helpWindow)
        this->helpWindow = new HelpMainWindow(this);
    connect(this->helpWindow, &HelpMainWindow::destroyed, this, &MainWindow::handleTheAutoDeletedObject);
    this->helpWindow->show();
    return true;
}

MainWindow::~MainWindow()
{
    recordLastHistory();
    releaseHeapSource();
    delete ui;
}

void MainWindow::handlePageIndexEdit(QString txt)
{
    bool isOk;
    short pageIndex = txt.toShort(&isOk);
    if(!isOk)
    {
        QMessageBox::critical(this, "出错","无法识别" + txt + " 是一个数字！");
        return;
    }
    if(!toPage(pageIndex))
    {
        QMessageBox::critical(this, "出错","无法跳转到：" + txt + "！");
        return;
    }
}

void MainWindow::showOCRPage()
{
    this->viewHyperWidget = false;
    operateHyperWidget();
    ui->OCRPage->show();
}


void MainWindow::handleOCRRes(QString res){
    ui->ocrResultTextEdit->setPlainText(res);
}

void MainWindow::setIsableDirectOCR(bool state)
{
    ui->btn_startMissionDirect->setEnabled(state);
}

void MainWindow::on_tableWidget_filehist_itemPressed(QTableWidgetItem *item)
{
    setCurrentFocusHistView(item);
    loadPDF(item->text());
}

bool MainWindow::changeStyleDirect()
{
    themeHandle->setQSSByGivenIndex(themeHandle->getCurrentIndex() + 1);
    return true;
}

bool MainWindow::setAsDefaultStyle()
{
    themeHandle->setQSSByGivenIndex(0);
    return true;
}

bool MainWindow::randStyle()
{
    srand((unsigned int)clock());
    themeHandle->setQSSByGivenIndex(rand() % themeHandle->getTheAcceptableThemes().size());
    return true;
}

void MainWindow::on_tableWidget_filehist_customContextMenuRequested(const QPoint &pos[[maybe_unused]])
{
    this->histFileViewMenu->exec(QCursor::pos());
}

void MainWindow::on_treeView_library_clicked(const QModelIndex &index)
{
    loadPDF(this->libraryModel->filePath(index));
}


void MainWindow::on_btn_edit_current_clicked()
{
    openEditWindow();
}


void MainWindow::on_btn_configMission_clicked()
{
    openOCRWindow();
}


bool MainWindow::on_btn_startMissionDirect_clicked()
{
    initOCRWindow();
    ocrWindow->startMission();
    showOCRPage();
    return true;
}

void MainWindow::on_btn_clip_clicked()
{
    QApplication::clipboard()->setText(ui->ocrResultTextEdit->toPlainText());
}


void MainWindow::on_btn_addOrOpenNotes_clicked()
{
    openAddNoteBook();
}


void MainWindow::on_btn_releaseNotes_clicked()
{
    removeNoteBook();
}

void MainWindow::on_btn_switch_clicked()
{
    switchNoteBook();
}


void MainWindow::on_btn_bindNote_clicked()
{
    bindNoteBook();
}

void MainWindow::on_btn_addNoteHandle_clicked()
{
    addHandle();
}


void MainWindow::on_btn_checkHandle_clicked()
{
    showhandles();
}


void MainWindow::on_btn_removeBtnHandle_clicked()
{
    removeHandle();
}


void MainWindow::on_btn_randStyle_clicked()
{
    randStyle();
}


void MainWindow::on_btn_setClearTheme_clicked()
{
    setAsDefaultStyle();
}

