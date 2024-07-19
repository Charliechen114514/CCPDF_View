#include "MainWindow/ccpdfview_mainwindow.h"
/// #include "tests/testcases.h"
#ifdef CHECK_MEMORY
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <vld.h>
#endif
#endif
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CCPDFView_MainWindow w;
    w.show();
    return a.exec();
}
