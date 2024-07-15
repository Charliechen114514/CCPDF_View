#ifndef WINDOWEVENTHELPER_H
#define WINDOWEVENTHELPER_H
#include <memory>
#include <CCPDF_Global.h>
#include "ActionMonitor/KeyboardMonitor/keyboardmonitor.h"
#include "ActionMonitor/MouseMonitor/mousemonitor.h"

class WindowEventHelper
{
public:
    using Key = int;
    using Modifiers = int;
    enum class Monitor{
        KeyMonitor,
        MouseMonitor,
        Global
    };

    enum class MouseProcess
    {
        WHEEL_UP,
        WHEEL_DOWN
    };

    WindowEventHelper();
    DISABLE_COPY(WindowEventHelper);
    void            registerKeyEvents(Key key, std::function<void(void)>, Modifiers m = 0);
    void            registerMouseEvents(MouseProcess p, std::function<void(void)>, Modifiers m = 0);
    void            clearModifiers(Monitor type);
    void            setModifiers(Modifiers m, Monitor type);
    void            doKeyProcess(Key key);
    void            doMouseProcess(MouseProcess P);
private:
    std::unique_ptr<WindowKeyboardMonitor>  keyboardMonitor;
    std::unique_ptr<WindowMouseMonitor>     mouseMonitor;
};

#endif // WINDOWEVENTHELPER_H
