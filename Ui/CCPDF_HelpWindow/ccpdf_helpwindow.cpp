#include "ccpdf_helpwindow.h"
#include "ui_ccpdf_helpwindow.h"
#include "WindowBuild/CCPDF_HelpingBuild/ccpdf_helpingbuildhelper.h"
#include "CCPDF_Global.h"

static constexpr const char* TABS[]{
    "加载PDF",    // 1
    "历史记录",
    "PDF浏览时",
    "更换自己的主题",
    "文本提取",     // 5
    "插件: OCR",
    "插件: 翻译",
    "书库",
    "检索",
    "PDF链接",    // 10
    "关于",
    "帮助:但是是自身"
};

static constexpr const char* TAB_FILE[]{
    __DocDir"LoadPDF.md",       // 1
    __DocDir"Historical.md",
    __DocDir"Browse_PDF.md",
    __DocDir"SwitchThemes.md",
    __DocDir"TextGrabber.md",    // 5
    __DocDir"Plugin_OCR.md",
    __DocDir"Plugin_Translations.md",
    __DocDir"Library.md",
    __DocDir"Searching.md",
    __DocDir"PDF_Link.md",      // 10
    __DocDir"About.md",
    __DocDir"Help.md"          // 12
};

static constexpr short TAB_N = sizeof(TAB_FILE) / sizeof(const char*);


CCPDF_HelpWindow::CCPDF_HelpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CCPDF_HelpWindow)
{
    ui->setupUi(this);
    configMap();
    registerTabs();
}

void CCPDF_HelpWindow::configMap()
{
    for(int i = 0; i < TAB_N; i++)
        mappings.insert(TABS[i], TAB_FILE[i]);
}

void CCPDF_HelpWindow::registerTabs()
{
    CCPDF_HelpingBuildHelper helper;
    auto it = mappings.begin();
    while(it!=mappings.end())
    {
        helper.addTabTo(ui->helpingTab, it.key(), it.value());
        ++it;
    }
}

CCPDF_HelpWindow::~CCPDF_HelpWindow()
{
    delete ui;
}
