#include "keyboardmonitor.h"
#include "Ui/ActionMonitor/eventhandlefunctor.h"
#include "Debugging/Logger/ccpdf_logger.h"

void WindowKeyboardMonitor::doProcess(int catchingkey)
{
    auto callBack = keyHandler.value(catchingkey, nullptr);
    if(!callBack) return;
    if(!callBack->req_modifiers() ||
        ( callBack->req_modifiers() && modifiers == callBack->get_modifiers()))
    {
        (*callBack)();
    }
}

bool WindowKeyboardMonitor::registerEventHandle(int key, KeyBoardFunctor* functor)
{
    if(keyHandler.value(key, nullptr))
    {
        e.e = MonitoringError::Error::RE_REGISTER;
        return false;
    }
    keyHandler.insert(key, std::shared_ptr<KeyBoardFunctor>(functor));
    return true;
}
