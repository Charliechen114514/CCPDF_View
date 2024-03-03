#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <QMap>
#include <QObject>
#include <QAction>

// self defined MyFunctor
class MyFunctor
{
public:
    // must have to process the operator()
    virtual void operator()() = 0;
    virtual bool            need_modifiers() = 0;
    virtual MyFunctor*      setRequired_modifiers(int modifiers) = 0;
    virtual int             getModifiiers(){return modifiers;}
protected:
    int             modifiers = 0;
};


class KeyBoardEventHandler
{
public:
    KeyBoardEventHandler() = default;

    KeyBoardEventHandler(const KeyBoardEventHandler&) = delete;

    const KeyBoardEventHandler& operator=(const KeyBoardEventHandler&) = delete;

    void registerEventHandle(int key, MyFunctor* functor);

    void doProcess(int catchingkey);

    void removeEventHandler(int key){
        keyHandler.remove(key);
    }

    void setCurrentModifiers(int modi){modifiers = modi;}

    void clearModifiers(){modifiers = 0;}

private:

    QMap<int, MyFunctor*>           keyHandler;
    int modifiers                   = 0;
};

class MouseWheelEventHandle
{
public:
    MouseWheelEventHandle() = default;
    const MouseWheelEventHandle& operator=(const MouseWheelEventHandle&) = delete;
    MouseWheelEventHandle(const MouseWheelEventHandle&) = delete;

    enum MouseWheelType{
        UP      = 1,
        DOWN    = 2
    };

    void registerEventHandle(int wheelEventCode, MyFunctor* func);

    void doProcess(int wheelEventCode);

    void removeEventHandler(int key){
        wheelHandler.remove(key);
    }

    void    setCheckModifiers(int modifiers){this->modifiers = modifiers;}
    void    clearModifiers(){modifiers = 0;}
    int     getCheckedModifiers(){return this->modifiers;}

private:
    QMap<int, MyFunctor*>           wheelHandler;
    int modifiers                   = 0;
};

    template<class WindowType>
struct ActionHandler
{
    using SigSlotPair = QPair<QAction* , bool(WindowType::*)()>;
    ActionHandler() = default;
    ActionHandler(const ActionHandler&) = delete;
    const ActionHandler& operator=(const ActionHandler&) = delete;
    ActionHandler* insertConnections(QAction*& sigAct, bool(WindowType::*slot)()){
        pairs.push_back(SigSlotPair(sigAct, slot));
        return this;
    }

    void connectAll(WindowType* w){
        for(auto& each : pairs)
        {
            QObject::connect(each.first, &QAction::triggered, w, each.second);
        }
    }

private:
    QList<SigSlotPair> pairs;
};

#endif // EVENTHANDLER_H
