#include <QTabWidget>
#include <QTextBrowser>
#include "ccpdf_helpingbuildhelper.h"
#include "CCPDF_Utils/ccpdf_fileutils.h"


void CCPDF_HelpingBuildHelper::addTabTo(QTabWidget* w, const QString& tabName, const QString& helpFile)
{
    if(!w)
        return;
    QTextBrowser* browser = new QTextBrowser(w);
    QFont f;
    f.setPointSize(20);
    browser->setFont(f);
    browser->setOpenExternalLinks(true);
    browser->setReadOnly(true);
    w->addTab(browser, tabName);
    if(CCPDF_FileUtils::FileUtils::isFileExsits(helpFile)){
        browser->setMarkdown(
            CCPDF_FileUtils::File_ReadWrite::readFile(helpFile)
        );
    }
}
