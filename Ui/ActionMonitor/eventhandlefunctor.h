#ifndef EVENTHANDLEFUNCTOR_H
#define EVENTHANDLEFUNCTOR_H
#include <functional>

struct EventHandleFunctor
{
    using ModifiersType = int;
    EventHandleFunctor() = default;
    virtual ~EventHandleFunctor() = default;
    virtual EventHandleFunctor*    setCallBack(std::function<void(void)> f){callBack = f;return this;}
    virtual void    doCallBack(){callBack();}
    virtual void    operator()(){doCallBack();}
    bool            req_modifiers() const {return req_modifier;}
    void            set_if_req_modifiers(bool req){req_modifier = req;}
    virtual EventHandleFunctor*    set_modifiers(ModifiersType modifiers){
        if(req_modifiers())
            this->modifiers = modifiers;
        return this;
    }
    ModifiersType   get_modifiers(){return modifiers;}
private:
    bool            req_modifier { false };
    std::function<void(void)>       callBack;
    ModifiersType   modifiers;
};

struct KeyBoardFunctor : EventHandleFunctor
{};

struct MouseFunctor : EventHandleFunctor
{};



#endif // EVENTHANDLEFUNCTOR_H
