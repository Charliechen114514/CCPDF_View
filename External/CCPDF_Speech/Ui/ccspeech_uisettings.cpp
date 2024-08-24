#include "ccspeech_uisettings.h"
#include <QTextToSpeech>
#include "ui_ccspeech_uisettings.h"
static int PITCH_MAX;
static int VOLUME_MAX;
static int RATE_MAX;

CCSpeech_UiSettings::CCSpeech_UiSettings(QWidget* parent)
    : QWidget(parent), ui(new Ui::CCSpeech_UiSettings) {
    ui->setupUi(this);
    setWindowTitle(DEFAULT_SpeechConfig::WINDOW_TITLE);
    PITCH_MAX  = ui->pitch->maximum() == 0 ? 10 : ui->pitch->maximum();
    RATE_MAX   = ui->rate->maximum() == 0 ? 10 : ui->rate->maximum();
    VOLUME_MAX = ui->volume->maximum() == 0 ? 100 : ui->volume->maximum();
    init_connections();
}

void CCSpeech_UiSettings::scan_available_engine() {
    if (!check_handle()) return;
    ui->engine->addItem(DEFAULT_SpeechConfig::DEFAULT);
    const auto engines = handle->speech()->availableEngines();
    for (const auto& engine : engines) ui->engine->addItem(engine);
}

void CCSpeech_UiSettings::init_connections() {
    connect(ui->pitch, &QSlider::valueChanged, this,
            &CCSpeech_UiSettings::setPitch);
    connect(ui->rate, &QSlider::valueChanged, this,
            &CCSpeech_UiSettings::setRate);
    connect(ui->volume, &QSlider::valueChanged, this,
            &CCSpeech_UiSettings::setVolume);
    connect(ui->engine, &QComboBox::currentIndexChanged, this,
            &CCSpeech_UiSettings::engineSelected);
    connect(ui->language, &QComboBox::currentIndexChanged, this,
            &CCSpeech_UiSettings::languageSelected);
    connect(ui->voice, &QComboBox::currentIndexChanged, this,
            &CCSpeech_UiSettings::voiceSelected);
}

void CCSpeech_UiSettings::languageSelected(int language) {
    if (!check_handle()) return;
    QLocale locale = ui->language->itemData(language).toLocale();
    handle->speech()->setLocale(locale);
}

void CCSpeech_UiSettings::setPitch(int val) {
    if (!check_handle()) return;
    handle->speech()->setPitch(val / (double)PITCH_MAX);
}

void CCSpeech_UiSettings::setAsDefault() {
    ui->engine->setCurrentIndex(0);
    engineSelected(0);
}

void CCSpeech_UiSettings::setRate(int val) {
    if (!check_handle()) return;
    handle->speech()->setRate(val / (double)RATE_MAX);
}
void CCSpeech_UiSettings::setVolume(int val) {
    if (!check_handle()) return;
    handle->speech()->setVolume(val / (double)VOLUME_MAX);
}

void CCSpeech_UiSettings::submitSpeechReady() {
    if (!check_handle()) return;
    ui->engine->setEnabled(true);
    // Block signals of the languages combobox while populating
    QSignalBlocker blocker(ui->language);
    auto           speechCoreHandle = handle->speech();
    ui->language->clear();
    const QList<QLocale> locales = speechCoreHandle->availableLocales();
    QLocale              current = speechCoreHandle->locale();
    for (const QLocale& locale : locales) {
        QString  name(QString("%1 (%2)").arg(
            QLocale::languageToString(locale.language()),
            QLocale::territoryToString(locale.territory())));
        QVariant localeVariant(locale);
        ui->language->addItem(name, localeVariant);
        if (locale.name() == current.name()) current = locale;
    }

    setRate(ui->rate->value());
    setPitch(ui->pitch->value());
    setVolume(ui->volume->value());

    connect(speechCoreHandle, &QTextToSpeech::localeChanged, this,
            &CCSpeech_UiSettings::localeChanged);

    blocker.unblock();

    localeChanged(current);

    emit speechEngineReady();
}

void CCSpeech_UiSettings::engineSelected(int index) {
    if (!check_handle()) return;
    ui->engine->setEnabled(false);

    const QString items = ui->engine->itemText(index);
    if (items == DEFAULT_SpeechConfig::DEFAULT) {
        handle->switch_engine(CCSpeech_Core::Configure::DEFAULT_ST);
    } else {
        handle->switch_engine(items);
    }
    auto speechCoreHandle = handle->speech();

    if (speechCoreHandle->state() == QTextToSpeech::Ready) {
        submitSpeechReady();
    } else {
        connect(speechCoreHandle, &QTextToSpeech::stateChanged, this,
                &CCSpeech_UiSettings::submitSpeechReady,
                Qt::SingleShotConnection);
    }
}

void CCSpeech_UiSettings::voiceSelected(int index) {
    if (!check_handle()) return;
    const auto voices = handle->speech()->availableVoices();
    handle->speech()->setVoice(voices.at(index));
}

void CCSpeech_UiSettings::localeChanged(const QLocale& locale) {
    if (!check_handle()) return;
    QVariant localeVariant(locale);
    ui->language->setCurrentIndex(ui->language->findData(localeVariant));

    QSignalBlocker blocker(ui->voice);

    ui->voice->clear();
    auto   speechCoreHandle = handle->speech();
    auto   voices           = speechCoreHandle->availableVoices();
    QVoice currentVoice     = speechCoreHandle->voice();
    for (const QVoice& voice : std::as_const(voices)) {
        ui->voice->addItem(QString("%1 - %2 - %3")
                               .arg(voice.name(),
                                    QVoice::genderName(voice.gender()),
                                    QVoice::ageName(voice.age())));
        if (voice.name() == currentVoice.name())
            ui->voice->setCurrentIndex(ui->voice->count() - 1);
    }
}

CCSpeech_UiSettings::~CCSpeech_UiSettings() {
    delete ui;
}
