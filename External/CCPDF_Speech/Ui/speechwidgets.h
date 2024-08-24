#ifndef SPEECHWIDGETS_H
#define SPEECHWIDGETS_H

#include <QWidget>
#include "Core/ccspeech_core.h"
#include "Ui/ccspeech_uisettings.h"
class QTextBrowser;
QT_BEGIN_NAMESPACE
namespace Ui {
class SpeechWidgets;
}
QT_END_NAMESPACE

class SpeechWidgets : public QWidget {
    Q_OBJECT

public:
    SpeechWidgets(QWidget *parent = nullptr);
    void bindSources(QTextBrowser *b) {
        this->b = b;
    }
    void doSaying();
    void doStop();
    void doResume();
    void doPause();
    ~SpeechWidgets();
signals:
    void tellFinishSaying();

private:
    Ui::SpeechWidgets                   *ui;
    std::unique_ptr<CCSpeech_Core>       core;
    std::unique_ptr<CCSpeech_UiSettings> uiSettings;
    QTextBrowser                        *b;
    bool                                 isNatureEnd{false};
    void                                 initConnections();
    void                                 handleSpeechReady();
    void                                 handleStateChange();
};
#endif  // SPEECHWIDGETS_H
