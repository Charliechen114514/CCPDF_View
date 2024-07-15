#include "ccpdf_historyaction.h"

CCPDF_HistoryAction::CCPDF_HistoryAction(QString restored_path, QString text, QObject *parent)
    : QAction{text, parent}
{
    this->restored_path = restored_path;
    connect(this, &QAction::triggered, this, &CCPDF_HistoryAction::_doEmitPvtSignal);
}
