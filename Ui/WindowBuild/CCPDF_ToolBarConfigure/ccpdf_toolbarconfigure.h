#ifndef CCPDF_TOOLBARCONFIGURE_H
#define CCPDF_TOOLBARCONFIGURE_H
#include <QObject>
#include "CCPDF_Global.h"
class QToolBar;
class CCPDFView_MainWindow;
class SpeechWidgets;
class CCPDF_ToolBarConfigure : public QObject {
    Q_OBJECT
public:
    CCPDF_ToolBarConfigure(QObject* parent = nullptr) : QObject(parent) {
    }
    virtual ~CCPDF_ToolBarConfigure() = default;
    DISABLE_COPY(CCPDF_ToolBarConfigure);
    virtual void doConfig(QToolBar* bar) = 0;
};

class CCPDF_MainWindowToolBarConfigure : public CCPDF_ToolBarConfigure {
    Q_OBJECT
public:
    CCPDF_MainWindowToolBarConfigure() = delete;
    DISABLE_COPY(CCPDF_MainWindowToolBarConfigure);
    CCPDF_MainWindowToolBarConfigure(CCPDFView_MainWindow* w,
                                     QObject*              parent = nullptr)
        : CCPDF_ToolBarConfigure(parent), window(w) {
    }
    SpeechWidgets* speechWidgets() {
#ifdef SUPPORT_SPEECHING
        return _recordings;
#endif
        return nullptr;
    }
    void doConfig(QToolBar* bar) override;

private:
    friend class CCPDFView_MainWindow;
    void configBonus(QToolBar* bar);

    CCPDFView_MainWindow* window;
#ifdef SUPPORT_SPEECHING
    SpeechWidgets* _recordings{};
#endif
};

#endif  // CCPDF_TOOLBARCONFIGURE_H
