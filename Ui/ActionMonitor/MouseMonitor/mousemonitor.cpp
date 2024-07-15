#include "mousemonitor.h"

bool WindowMouseMonitor::registerEventsHandle(MouseWheelOperator op, MouseFunctor* f)
{
    if(mouseHandler.value(op, nullptr)){
        e.e = MonitoringError::Error::RE_REGISTER;
        return false;
    }

    mouseHandler.insert(op, std::shared_ptr<MouseFunctor>(f));
    return true;
}


bool WindowMouseMonitor::doProcess(MouseWheelOperator op)
{
    auto callBack = mouseHandler.value(op, nullptr);
    if(!callBack) return false;

    if(!callBack->req_modifiers())
    {
        (*callBack)();
        return true;
    }

    if(( callBack->req_modifiers() && modifiers == callBack->get_modifiers()))
    {
        (*callBack)();
    }
    return true;
}
