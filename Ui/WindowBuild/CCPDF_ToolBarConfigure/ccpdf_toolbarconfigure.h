#ifndef CCPDF_TOOLBARCONFIGURE_H
#define CCPDF_TOOLBARCONFIGURE_H
#include "CCPDF_Global.h"
#include <QObject>
class QToolBar;
class CCPDFView_MainWindow;


class CCPDF_ToolBarConfigure : public QObject
{
    Q_OBJECT
public:
    CCPDF_ToolBarConfigure(QObject* parent = nullptr):QObject(parent){}
    virtual ~CCPDF_ToolBarConfigure() = default;
    DISABLE_COPY(CCPDF_ToolBarConfigure);
    virtual void doConfig(QToolBar* bar) = 0;
};

class CCPDF_MainWindowToolBarConfigure : public CCPDF_ToolBarConfigure
{
    Q_OBJECT
public:
    CCPDF_MainWindowToolBarConfigure() = delete;
    DISABLE_COPY(CCPDF_MainWindowToolBarConfigure);
    CCPDF_MainWindowToolBarConfigure(CCPDFView_MainWindow* w,
                                     QObject* parent = nullptr):
        CCPDF_ToolBarConfigure(parent),
        window(w){}
    void doConfig(QToolBar* bar) override;
private:
    CCPDFView_MainWindow*           window;
};

#endif // CCPDF_TOOLBARCONFIGURE_H
