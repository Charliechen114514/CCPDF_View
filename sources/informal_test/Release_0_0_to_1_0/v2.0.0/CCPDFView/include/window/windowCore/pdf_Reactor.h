#ifndef PDF_REACTOR_H
#define PDF_REACTOR_H
#include "eventhandler.h"

class Page_Reactor : public MyFunctor
{
public:
    Page_Reactor() = default;
    Page_Reactor(const Page_Reactor&) = delete;
    const Page_Reactor& operator=(const Page_Reactor& )=delete;
    virtual ~Page_Reactor(){}


    Page_Reactor* setPageReactor(std::function<void(void)> f){
        pageReactor = f;
        return this;
    }

    void operator()()override{
        pageReactor();
    }

    bool need_modifiers() override{
        return false;
    }

    virtual Page_Reactor* setRequired_modifiers(int modifiers) override{
        this->modifiers = modifiers;
        return this;
    }

    virtual int getModifiiers() override{return modifiers;}

private:
    std::function<void(void)> pageReactor;
};

class Zoom_Reactor : public MyFunctor
{
public:
    Zoom_Reactor() = default;
    Zoom_Reactor(const Zoom_Reactor&) = delete;
    const Zoom_Reactor& operator=(const Zoom_Reactor&) = delete;
    virtual ~Zoom_Reactor(){}

    Zoom_Reactor* setZoomReactor(std::function<void(void)> f){
        zoomReactor = f;
        return this;
    }

    void operator()()override{
        zoomReactor();
    }

    bool need_modifiers() override{
        return true;
    }

    virtual Zoom_Reactor* setRequired_modifiers(int modifiers) override{
        this->modifiers = modifiers;
        return this;
    }

    virtual int getModifiiers() override{return modifiers;}

private:
    std::function<void(void)> zoomReactor;
};

class ViewWidget_Reactor : public MyFunctor
{
public:
    ViewWidget_Reactor() = default;
    ViewWidget_Reactor(const ViewWidget_Reactor&) = delete;
    const ViewWidget_Reactor& operator=(const ViewWidget_Reactor&) = delete;
    virtual ~ViewWidget_Reactor(){};

    ViewWidget_Reactor* setViewFunctor(std::function<bool(void)> f){
        this->functor = f;
        return this;
    }

    void operator()()override{
        functor();
    }

    bool need_modifiers() override{
        return true;
    }

    virtual ViewWidget_Reactor* setRequired_modifiers(int modifiers) override{
        this->modifiers = modifiers;
        return this;
    }

    virtual int getModifiiers() override{return modifiers;}

private:
    std::function<bool(void)> functor;
};


// EditWindow one
// historical operations for Crtl + Z and Ctrl + Y
class HistoricalOperation_Reactor : public MyFunctor
{
public:
    HistoricalOperation_Reactor() = default;
    HistoricalOperation_Reactor(const HistoricalOperation_Reactor&) = delete;
    const HistoricalOperation_Reactor& operator=(const HistoricalOperation_Reactor&) = delete;
    virtual ~HistoricalOperation_Reactor(){}

    HistoricalOperation_Reactor* setFunctor(std::function<void(void)> functor){
        this->functor = functor;
        return this;
    }

    void operator()()override{
        functor();
    }

    bool need_modifiers() override{
        return true;
    }

    virtual HistoricalOperation_Reactor* setRequired_modifiers(int modifiers) override{
        this->modifiers = modifiers;
        return this;
    }

    virtual int getModifiiers() override{return modifiers;}

private:
    std::function<void(void)> functor;
};

class SaveReactor : public MyFunctor
{
public:
    SaveReactor() = default;
    SaveReactor(const SaveReactor&) = delete;
    const SaveReactor& operator=(const SaveReactor&) = delete;
    virtual ~SaveReactor(){}

    SaveReactor* setFunctor(std::function<void(void)> functor){
        this->functor = functor;
        return this;
    }

    void operator()()override{
        functor();
    }

    bool need_modifiers() override{
        return true;
    }

    virtual SaveReactor* setRequired_modifiers(int modifiers) override{
        this->modifiers = modifiers;
        return this;
    }

    virtual int getModifiiers() override{return modifiers;}

private:
    std::function<void(void)> functor;
};

class EditReactor : public MyFunctor
{
public:
    EditReactor() = default;
    EditReactor(const EditReactor&) = delete;
    const EditReactor& operator=(const EditReactor&) = delete;
    virtual ~EditReactor(){}

    EditReactor* setFunctor(std::function<void(void)> functor){
        this->functor = functor;
        return this;
    }

    void operator()()override{
        functor();
    }

    bool need_modifiers() override{
        return true;
    }

    virtual EditReactor* setRequired_modifiers(int modifiers) override{
        this->modifiers = modifiers;
        return this;
    }

    virtual int getModifiiers() override{return modifiers;}

private:
    std::function<void(void)> functor;
};



#endif // PDF_REACTOR_H
