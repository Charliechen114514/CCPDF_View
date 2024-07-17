#include "ccpdf_theme_action.h"


CCPDF_Theme_Action::CCPDF_Theme_Action(QObject *parent)
    : QAction{parent}
{
    selfDelMenu = std::make_unique<QMenu>();
    QAction* remove_act = new QAction("删除这一主题", selfDelMenu.get());
    QAction* use_this = new QAction("应用这个主题", selfDelMenu.get());
    selfDelMenu->addAction(use_this);
    selfDelMenu->addAction(remove_act);
    setMenu(selfDelMenu.get());
    connect(use_this, &QAction::triggered, this, &CCPDF_Theme_Action::_pvtDoEmitSelfSig);
    connect(remove_act, &QAction::triggered, this, &CCPDF_Theme_Action::_pvtTellRemoveThis);
}
