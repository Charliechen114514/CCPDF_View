#include "windoweventhelper.h"
#include "ActionMonitor/KeyboardMonitor/keyboardmonitor.h"
#include "ActionMonitor/MouseMonitor/mousemonitor.h"
#include "ActionMonitor/eventhandlefunctor.h"

WindowEventHelper::WindowEventHelper():
    keyboardMonitor(new WindowKeyboardMonitor),
    mouseMonitor(new WindowMouseMonitor)
{}

void WindowEventHelper::registerKeyEvents(Key key, std::function<void (void)> f,  Modifiers m)
{
    auto functor = new KeyBoardFunctor;
    functor->setCallBack(f);
    if(m)
    {
        functor->set_if_req_modifiers(true);
        functor->set_modifiers(m);
    }
    keyboardMonitor->registerEventHandle(key, functor);
}

void WindowEventHelper::registerMouseEvents(MouseProcess p, std::function<void(void)> f, Modifiers m)
{
    auto functor = new MouseFunctor;
    functor->setCallBack(f);
    if(m)
    {
        functor->set_if_req_modifiers(true);
        functor->set_modifiers(m);
    }
    switch(p)
    {
    case MouseProcess::WHEEL_UP:
        mouseMonitor->registerEventsHandle(
            WindowMouseMonitor::MouseWheelOperator::WHEEL_UP, functor);
        break;
    case MouseProcess::WHEEL_DOWN:
        mouseMonitor->registerEventsHandle(
            WindowMouseMonitor::MouseWheelOperator::WHEEL_DOWN, functor);
        break;
    }

}


void WindowEventHelper::setModifiers(Modifiers m, Monitor type)
{
    switch(type)
    {
    case Monitor::KeyMonitor:
        keyboardMonitor->setCurrentModifiers(m);
        break;
    case Monitor::MouseMonitor:
        mouseMonitor->setModifiers(m);
        break;
    case Monitor::Global:
        keyboardMonitor->setCurrentModifiers(m);
        mouseMonitor->setModifiers(m);
        break;
    }
}

void WindowEventHelper::clearModifiers(Monitor type)
{
    switch(type)
    {
    case Monitor::KeyMonitor:
        keyboardMonitor->clearModifiers();break;
    case Monitor::MouseMonitor:
        mouseMonitor->clearModifiers();break;
    case Monitor::Global:
        keyboardMonitor->clearModifiers();
        mouseMonitor->clearModifiers();
        break;
    }
}

void WindowEventHelper::doKeyProcess(Key key)
{
    keyboardMonitor->doProcess(key);
}

void WindowEventHelper::doMouseProcess(MouseProcess P)
{
    switch(P)
    {
    case MouseProcess::WHEEL_UP:
        mouseMonitor->doProcess(WindowMouseMonitor::MouseWheelOperator::WHEEL_UP);break;
    case MouseProcess::WHEEL_DOWN:
        mouseMonitor->doProcess(WindowMouseMonitor::MouseWheelOperator::WHEEL_DOWN);
        break;
    }
}
