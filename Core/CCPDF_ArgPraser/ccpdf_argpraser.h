#ifndef CCPDF_ARGPRASER_H
#define CCPDF_ARGPRASER_H
#include <QCommandLineParser>
#include "CCPDF_Global.h"
class CCPDFView_MainWindow;
using CCPDF_Positional_Arguments_Installee = QPair<const char*, const char*>;

struct CCPDF_Arguments_Installee {
    const char* const short_op;
    const char* const long_op;
    const char* const discriptions;
};

class CCPDF_ArgPraser {
public:
    CCPDF_ArgPraser() = delete;
    CCPDF_ArgPraser(CCPDFView_MainWindow* window);
    DISABLE_COPY(CCPDF_ArgPraser);
    void makeProcess();

private:
    void                  initializeAppInfo();
    void                  loadArguments();
    void                  loadRequiredPdfs();
    QCommandLineParser    parser;
    CCPDFView_MainWindow* window;
};

#endif  // CCPDF_ARGPRASER_H
