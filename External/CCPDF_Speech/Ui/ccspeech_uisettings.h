#ifndef CCSPEECH_UISETTINGS_H
#define CCSPEECH_UISETTINGS_H
#include <QWidget>
#include "Core/ccspeech_core.h"

namespace Ui {
class CCSpeech_UiSettings;
}

class CCSpeech_UiSettings : public QWidget {
    Q_OBJECT

public:
    struct DEFAULT_SpeechConfig {
        static constexpr const char *DEFAULT      = "默认";
        static constexpr const char *WINDOW_TITLE = "语音设置";
    };

    explicit CCSpeech_UiSettings(QWidget *parent = nullptr);
    inline void setHandle(CCSpeech_Core *handle) {
        this->handle = handle;
    }
    void scan_available_engine();
    void setRate(int val);
    void setVolume(int val);
    void setPitch(int val);
    void setAsDefault();
    ~CCSpeech_UiSettings();
    enum class Error { NO_ERROR, NO_OP_HANDLE };
    Error error() {
        return e;
    }

signals:
    void speechEngineReady();

private:
    Ui::CCSpeech_UiSettings *ui;
    Error                    e{Error::NO_ERROR};
    void                     engineSelected(int index);
    void                     localeChanged(const QLocale &locale);
    void                     voiceSelected(int index);
    void                     languageSelected(int language);
    void                     submitSpeechReady();
    inline void              setError(Error e) {
        this->e = e;
    }
    inline void clearError() {
        e = Error::NO_ERROR;
    }
    CCSpeech_Core *handle;
    bool           check_handle() {
        return handle;
    }
    void init_connections();
};

#endif  // CCSPEECH_UISETTINGS_H
