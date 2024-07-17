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

    // for more
    QPushButton* for_hyper = new QPushButton(bar);
    bar->addWidget(for_hyper);
    for_hyper->setToolTip("更多...");
    for_hyper->setIcon(QIcon(":/toolbar_icon/icons/forMore.png"));
    connect(for_hyper, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::opposeHyperWidgetVisible);
    bar->addSeparator();

    // history
    QPushButton* history = new QPushButton(bar);
    bar->addWidget(history);
    history->setToolTip("历史记录");
    history->setIcon(QIcon(":/toolbar_icon/icons/history.ico"));
    connect(history,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToHistory);
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

    // Translate
    QPushButton* translate = new QPushButton(bar);
    bar->addWidget(translate);
    translate->setToolTip("翻译");
    translate->setIcon(QIcon(":/toolbar_icon/icons/translate.png"));
    connect(translate,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToTranslate);
    bar->addSeparator();

    // Link
    QPushButton* link = new QPushButton(bar);
    bar->addWidget(link);
    link->setToolTip("翻译");
    link->setIcon(QIcon(":/toolbar_icon/icons/link.png"));
    connect(link,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToLink);
    bar->addSeparator();

    // searching model
    QPushButton* searching_btn = new QPushButton(bar);
    bar->addWidget(searching_btn);
    searching_btn->setToolTip("检索");
    searching_btn->setIcon(QIcon(":/toolbar_icon/icons/searching.png"));
    connect(searching_btn,  &QPushButton::clicked, this->window, &CCPDFView_MainWindow::routeToSearching);
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

    // page mode
    QPushButton* btn_SinglePage = new QPushButton(bar);
    bar->addWidget(btn_SinglePage);
    btn_SinglePage->setToolTip("单页模式");
    btn_SinglePage->setIcon(QIcon(":/toolbar_icon/icons/singlePage.png"));
    connect(btn_SinglePage, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageSingle);

    QPushButton* btn_MultiPage = new QPushButton(bar);
    bar->addWidget(btn_MultiPage);
    btn_MultiPage->setToolTip("多页模式");
    btn_MultiPage->setIcon(QIcon(":/toolbar_icon/icons/multiPage.png"));
    connect(btn_MultiPage, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::pageMulti);
    bar->addSeparator();

    // about
    QPushButton* btn_about = new QPushButton(bar);
    bar->addWidget(btn_about);
    btn_about->setToolTip("关于这个软件...");
    btn_about->setIcon(QIcon(":/toolbar_icon/icons/btn_about.png"));
    connect(btn_about, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::showAbout);
    bar->addSeparator();

//    // help
//    QPushButton* btn_help = new QPushButton(bar);
//    bar->addWidget(btn_help);
//    btn_help->setToolTip("帮助...");
//    btn_help->setIcon(QIcon(":/Ui/icons/help.png"));
//    connect(btn_help, &QPushButton::clicked, this->window, &CCPDFView_MainWindow::viewHelp);
//    bar->addSeparator();
}
