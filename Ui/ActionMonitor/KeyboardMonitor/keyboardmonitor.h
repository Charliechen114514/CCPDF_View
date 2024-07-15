#ifndef KEYBOARDMONITOR_H
#define KEYBOARDMONITOR_H
#include "CCPDF_Global.h"
#include <QMap>
struct KeyBoardFunctor;

class WindowKeyboardMonitor
{
public:
    DISABLE_COPY(WindowKeyboardMonitor);
    WindowKeyboardMonitor() = default;
    ~WindowKeyboardMonitor() = default;
    struct MonitoringError{
        enum class Error{
            NO_ERROR,
            RE_REGISTER
        } e{Error::NO_ERROR};
        QString errorString()
        {
            switch (e) {
            case Error::RE_REGISTER:
                return "重复注册";
                break;
            case Error::NO_ERROR:
                return "";
                break;
            }
            return "Unknown Error";
        }
    };

    bool registerEventHandle(int key, KeyBoardFunctor* functor);
    void doProcess(int catchingkey);
    void removeEventHandler(int key){keyHandler.remove(key);}
    void setCurrentModifiers(int modi){modifiers = modi;}
    void clearModifiers(){modifiers = CLEAR_KEY;}
    MonitoringError                 e;
private:
    using Key = int;
    const Key   CLEAR_KEY           = 0;
    Key                             modifiers {CLEAR_KEY};
    QMap<Key,
    __MEMEROY_HOLD_BY_SMT_PTR
    std::shared_ptr<KeyBoardFunctor>>     keyHandler;
};

#endif // KEYBOARDMONITOR_H
