#include "eventhandler.h"

void KeyBoardEventHandler::registerEventHandle(int key, MyFunctor* functor)
{
    if(!functor)
        return;

    this->keyHandler.insert(key, functor);
}


void KeyBoardEventHandler::doProcess(int catchingkey)
{
    MyFunctor* functor = this->keyHandler.value(catchingkey, nullptr);    
    if(!functor) //check if it is a valid function ptr
        return;
    if(functor->need_modifiers()){
        if(functor->getModifiiers() != modifiers)
            return;
    }

    (*functor)();
}


void MouseWheelEventHandle::registerEventHandle(int wheelEventCode, MyFunctor* func)
{
    if(!func)
        return;

    this->wheelHandler.insert(wheelEventCode, func);
}

void MouseWheelEventHandle::doProcess(int wheelEventCode)
{
    MyFunctor* functor = this->wheelHandler.value(wheelEventCode, nullptr);
    if(!functor)
        return;
    if(functor->need_modifiers()){
        if(functor->getModifiiers() != modifiers)
            return;
    }

    (*functor)();
}

