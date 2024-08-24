#include "speechwidgets.h"
#include <QTextBrowser>
#include <QtTextToSpeech>
#include "ui_speechwidgets.h"
SpeechWidgets::SpeechWidgets(QWidget *parent)
    : QWidget(parent), ui(new Ui::SpeechWidgets) {
    ui->setupUi(this);
    core       = std::make_unique<CCSpeech_Core>();
    uiSettings = std::make_unique<CCSpeech_UiSettings>();
    uiSettings->setHandle(core.get());
    uiSettings->scan_available_engine();
    initConnections();
    uiSettings->setAsDefault();
}

void SpeechWidgets::initConnections() {
    connect(uiSettings.get(), &CCSpeech_UiSettings::speechEngineReady, this,
            &SpeechWidgets::handleSpeechReady);
    connect(ui->btn_settings, &QPushButton::clicked, this,
            [this]() { uiSettings->show(); });
}

void SpeechWidgets::doSaying() {
    if (!b) return;
    core->speech()->say(b->toPlainText().simplified());
}

void SpeechWidgets::doStop() {
    isNatureEnd = false;
    core->speech()->stop();
}
void SpeechWidgets::doResume() {
    core->speech()->resume();
}
void SpeechWidgets::doPause() {
    core->speech()->pause();
}

void SpeechWidgets::handleSpeechReady() {
    const bool hasPauseResume = core->speech()->engineCapabilities() &
                                QTextToSpeech::Capability::PauseResume;
    ui->btn_pause->setVisible(hasPauseResume);
    ui->btn_resume->setVisible(hasPauseResume);
    connect(ui->btn_play, &QPushButton::clicked, this,
            &SpeechWidgets::doSaying);

    connect(ui->btn_stop, &QPushButton::clicked, this, &SpeechWidgets::doStop);

    connect(ui->btn_pause, &QPushButton::clicked, this,
            &SpeechWidgets::doPause);

    connect(ui->btn_resume, &QPushButton::clicked, this,
            &SpeechWidgets::doResume);

    connect(core->speech(), &QTextToSpeech::stateChanged, this,
            &SpeechWidgets::handleStateChange);
}

void SpeechWidgets::handleStateChange() {
    QTextToSpeech::State state = core->speech()->state();
    if (state == QTextToSpeech::Ready) {
        if (isNatureEnd) {
            emit tellFinishSaying();
        } else {
            isNatureEnd = true;
        }
    }
    ui->btn_pause->setEnabled(state == QTextToSpeech::Speaking);
    ui->btn_resume->setEnabled(state == QTextToSpeech::Paused);
    ui->btn_stop->setEnabled(state == QTextToSpeech::Speaking ||
                             state == QTextToSpeech::Paused);
}

SpeechWidgets::~SpeechWidgets() {
    // Prevent Core Releases Signal ReTriggures
    disconnect(core->speech(), &QTextToSpeech::stateChanged, this,
               &SpeechWidgets::handleStateChange);
    delete ui;
}
