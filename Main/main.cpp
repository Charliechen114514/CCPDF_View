#include "MainWindow/ccpdfview_mainwindow.h"
/// #include "tests/testcases.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CCPDFView_MainWindow w;
    w.show();
    return a.exec();
}
