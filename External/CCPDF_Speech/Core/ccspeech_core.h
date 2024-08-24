#ifndef CCSPEECH_CORE_H
#define CCSPEECH_CORE_H
#include <QString>
#include <memory>
class QTextToSpeech;

class CCSpeech_Core {
public:
    struct Configure {
        static constexpr const char* DEFAULT_ST = "";
    };

    CCSpeech_Core();
    CCSpeech_Core(const CCSpeech_Core&)                   = delete;
    const CCSpeech_Core&  operator=(const CCSpeech_Core&) = delete;
    inline QTextToSpeech* speech() {
        return speechCore.get();
    };

private:
    friend class CCSpeech_UiSettings;
    void        switch_engine(const QString& str);
    void        _init();
    inline bool checkVadility() {
        return speechCore.get();
    }
    std::shared_ptr<QTextToSpeech> speechCore{};
};

#endif  // CCSPEECH_CORE_H
