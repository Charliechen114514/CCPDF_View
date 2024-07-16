#include <QPushButton>
#include <QLineEdit>
#include <QToolBar>
#include <MainWindow/ccpdfview_mainwindow.h>
#include <QIntValidator>
#include "ccpdf_toolbarconfigure.h"

void CCPDF_MainWindowToolBarConfigure::doConfig(QToolBar* bar)
{
    QPushButton* open_btn = new QPushButton(bar);
    bar->addWidget(open_btn);
    open_btn->setToolTip("加载PDF");
    open_btn->setIcon(QIcon(":/toolbar_icon/icons/open.ico"));
    connect(open_btn, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::loadPDFFromFileDialog);
    bar->addSeparator();

    // book model
    QPushButton* bookMarkModel_btn = new QPushButton(bar);
    bar->addWidget(bookMarkModel_btn);
    bookMarkModel_btn->setToolTip("操作目录模块");
    bookMarkModel_btn->setIcon(QIcon(":/toolbar_icon/icons/bookmarkModel.png"));
    connect(bookMarkModel_btn,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::opposeBookModelVisible);
    bar->addSeparator();


    // searching model
    QPushButton* searching_btn = new QPushButton(bar);
    bar->addWidget(searching_btn);
    searching_btn->setToolTip("操作目录模块");
    searching_btn->setIcon(QIcon(":/toolbar_icon/icons/searching.png"));
    connect(searching_btn,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToSearching);
    bar->addSeparator();

    // library
    QPushButton* library = new QPushButton(bar);
    bar->addWidget(library);
    library->setToolTip("书库");
    library->setIcon(QIcon(":/toolbar_icon/icons/booklib.ico"));
    connect(library,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToLibrary);
    bar->addSeparator();

    // OCR
    QPushButton* OCR = new QPushButton(bar);
    bar->addWidget(OCR);
    OCR->setToolTip("打开OCR");
    OCR->setIcon(QIcon(":/toolbar_icon/icons/OCR_current.png"));
    connect(OCR,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToOCR);
    bar->addSeparator();

    // page index lineEdit
    QLineEdit* pageIndexEdit = new QLineEdit(bar);
    pageIndexEdit->setMaximumWidth(100);
    bar->addWidget(pageIndexEdit);
    pageIndexEdit->setValidator(new QIntValidator(pageIndexEdit));
    connect(pageIndexEdit, &QLineEdit::textChanged, this->window, qOverload<const QString&>(&CCPDFView_MainWindow::pageNavigate));

    QPushButton* to_prev_tn = new QPushButton(bar);
    bar->addWidget(to_prev_tn);
    to_prev_tn->setToolTip("前一页");
    to_prev_tn->setIcon(QIcon(":/toolbar_icon/icons/toPrev.png"));
    connect(to_prev_tn, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageBackward);

    QPushButton* to_next_tn = new QPushButton(bar);
    bar->addWidget(to_next_tn);
    to_next_tn->setToolTip("后一页");
    to_next_tn->setIcon(QIcon(":/toolbar_icon/icons/toNext.png"));
    connect(to_next_tn, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageForward);
    bar->addSeparator();

    QPushButton* to_first = new QPushButton(bar);
    bar->addWidget(to_first);
    to_first->setToolTip("第一页");
    to_first->setIcon(QIcon(":/toolbar_icon/icons/firstPage.png"));
    connect(to_first, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageBegin);

    QPushButton* to_final = new QPushButton(bar);
    bar->addWidget(to_final);
    to_final->setToolTip("最后一页");
    to_final->setIcon(QIcon(":/toolbar_icon/icons/lastPage.png"));
    connect(to_final, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageEnd);
    bar->addSeparator();

    QPushButton* for_hyper = new QPushButton(bar);
    bar->addWidget(for_hyper);
    for_hyper->setToolTip("更多...");
    for_hyper->setIcon(QIcon(":/toolbar_icon/icons/forMore.png"));
    connect(for_hyper, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::opposeHyperWidgetVisible);
    bar->addSeparator();

    // zooming
    QPushButton* btn_zoomIn = new QPushButton(bar);
    bar->addWidget(btn_zoomIn);
    btn_zoomIn->setToolTip("放大");
    btn_zoomIn->setIcon(QIcon(":/toolbar_icon/icons/zoomIn.png"));
    connect(btn_zoomIn, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::zoomIn);

    QPushButton* btn_zoomOut = new QPushButton(bar);
    bar->addWidget(btn_zoomOut);
    btn_zoomOut->setToolTip("缩小");
    btn_zoomOut->setIcon(QIcon(":/toolbar_icon/icons/zoomOut.png"));
    connect(btn_zoomOut, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::zoomOut);
    bar->addSeparator();

    // zooming
    QPushButton* btn_SinglePage = new QPushButton(bar);
    bar->addWidget(btn_SinglePage);
    btn_SinglePage->setToolTip("单页模式");
    btn_SinglePage->setIcon(QIcon(":/toolbar_icon/icons/singlePage.png"));
    connect(btn_SinglePage, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageSingle);

    QPushButton* btn_MultiPage = new QPushButton(bar);
    bar->addWidget(btn_MultiPage);
    btn_MultiPage->setToolTip("缩小");
    btn_MultiPage->setIcon(QIcon(":/toolbar_icon/icons/multiPage.png"));
    connect(btn_MultiPage, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageMulti);
    bar->addSeparator();

//    // page mode view
//    QPushButton* btn_changePageMode = new QPushButton(bar);
//    bar->addWidget(btn_changePageMode);
//    btn_changePageMode->setToolTip("改变页模式");
//    btn_changePageMode->setIcon(QIcon(":/Ui/icons/pageMode.png"));
//    connect(btn_changePageMode, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::changePageMode);
//    bar->addSeparator();
//    // edit
//    QPushButton* btn_editPDF = new QPushButton(bar);
//    bar->addWidget(btn_editPDF);
//    btn_editPDF->setToolTip("编辑当前页");
//    btn_editPDF->setIcon(QIcon(":/Ui/icons/editPDF.png"));
//    connect(btn_editPDF, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::openEditWindow);

//    QPushButton* btn_resumeCurPage = new QPushButton(bar);
//    bar->addWidget(btn_resumeCurPage);
//    btn_resumeCurPage->setToolTip("恢复当前页");
//    btn_resumeCurPage->setIcon(QIcon(":/Ui/icons/ResumeCurPage.png"));
//    connect(btn_resumeCurPage, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::backToBeforeEditedCurPage);

//    bar->addSeparator();

//    // noteBook
//    QPushButton* btn_addOrOpenNote = new QPushButton(bar);
//    bar->addWidget(btn_addOrOpenNote);
//    btn_addOrOpenNote->setToolTip("打开或者创建笔记");
//    btn_addOrOpenNote->setIcon(QIcon(":/Ui/icons/notebookOpenAdd.png"));
//    connect(btn_addOrOpenNote, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::openAddNoteBook);

//    QPushButton* btn_releaseNote = new QPushButton(bar);
//    bar->addWidget(btn_releaseNote);
//    btn_releaseNote->setToolTip("解绑笔记");
//    btn_releaseNote->setIcon(QIcon(":/Ui/icons/notebookRelease.png"));
//    connect(btn_releaseNote, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::removeNoteBook);

//    QPushButton* btnSwitch = new QPushButton(bar);
//    bar->addWidget(btnSwitch);
//    btnSwitch->setToolTip("更换绑定笔记");
//    btnSwitch->setIcon(QIcon(":/Ui/icons/switchNoteBook.png"));
//    connect(btnSwitch, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::switchNoteBook);
//    bar->addSeparator();

//    // notebookTarget
//    QPushButton* btn_addTarget = new QPushButton(bar);
//    bar->addWidget(btn_addTarget);
//    btn_addTarget->setToolTip("增加笔记工具");
//    btn_addTarget->setIcon(QIcon(":/Ui/icons/editTargetHandleAdd.png"));
//    connect(btn_addTarget, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::addHandle);

//    QPushButton* btn_removeTarget = new QPushButton(bar);
//    bar->addWidget(btn_removeTarget);
//    btn_removeTarget->setToolTip("去除笔记工具");
//    btn_removeTarget->setIcon(QIcon(":/Ui/icons/editTargetHandleShowRemove.png"));
//    connect(btn_removeTarget, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::removeHandle);

//    QPushButton* btn_showTarget = new QPushButton(bar);
//    bar->addWidget(btn_showTarget);
//    btn_showTarget->setToolTip("查看当前的笔记工具");
//    btn_showTarget->setIcon(QIcon(":/Ui/icons/editTargetHandleShow.png"));
//    connect(btn_showTarget, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::showhandles);
//    bar->addSeparator();

//    // style
//    QPushButton* btn_styleshift = new QPushButton(bar);
//    bar->addWidget(btn_styleshift);
//    btn_styleshift->setToolTip("切换主题");
//    btn_styleshift->setIcon(QIcon(":/Ui/icons/styleSwitch.png"));
//    connect(btn_styleshift, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::changeStyleDirect);
//    bar->addSeparator();

//    // about
//    QPushButton* btn_about = new QPushButton(bar);
//    bar->addWidget(btn_about);
//    btn_about->setToolTip("关于这个软件...");
//    btn_about->setIcon(QIcon(":/Ui/icons/btn_about.png"));
//    connect(btn_about, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::viewAbout);
//    bar->addSeparator();

//    // help
//    QPushButton* btn_help = new QPushButton(bar);
//    bar->addWidget(btn_help);
//    btn_help->setToolTip("关于这个软件...");
//    btn_help->setIcon(QIcon(":/Ui/icons/help.png"));
//    connect(btn_help, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::viewHelp);
//    bar->addSeparator();
}
