#include <QApplication>
#include "CCPDF_ArgPraser/ccpdf_argpraser.h"
#include "MainWindow/ccpdfview_mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication         a(argc, argv);
    CCPDFView_MainWindow w;
    CCPDF_ArgPraser      parser(&w);
    parser.makeProcess();
    w.show();
    return a.exec();
}
