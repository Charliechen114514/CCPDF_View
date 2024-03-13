#include <QMenu>
#include "pdf_specialaction.h"


PDF_SpecialAction::PDF_SpecialAction(QString pdfPath, QObject *parent)
    : QAction{parent}, pdfPath(pdfPath)
{
    connect(this, &QAction::triggered, this, &PDF_SpecialAction::detailedTriggler);
}

void PDF_SpecialActionManager::addToMenu(PDF_SpecialAction* action, bool allowed_duplicate)
{
    if(!action)
        return;
    if(!allowed_duplicate)
        for(auto& it : actions)
            if(it->getPath() == action->getPath())
                actions.removeOne(it);
    this->actions.push_front(action);
    refreshMenu();
}

void PDF_SpecialActionManager::removeAction(QString path)
{
    for(auto& it : actions)
    {
        if(it->matchByPath(path))
        {
            actions.removeOne(it);
        }
    }
}

void PDF_SpecialActionManager::moveLastToFirst()
{
    auto it = actions.last();
    actions.removeLast();
    actions.push_front(it);
}


void PDF_SpecialActionManager::refreshMenu()
{
    this->binder.clear();
    for(auto& it : actions)
        binder.addAction(it);
}

PDF_SpecialActionManager::~PDF_SpecialActionManager()
{
    for(auto& it : actions)
    {
        if(it)
        {
            delete it;
            it = nullptr;
        }
    }
    actions.clear();
}








