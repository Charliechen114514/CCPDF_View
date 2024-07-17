#include <QMessageBox>
#include "ccpdf_messgaeboxutils.h"
#include "CCPDF_About/CCPDF_About.h"

void CCPDF_MessgaeBoxUtils::ErrorInform::tellError(
    QString title, QString captions, QWidget* parent)
{
    QMessageBox::critical(parent, title, captions);
}

bool CCPDF_MessgaeBoxUtils::InfoInform::
inform(QString title, QString captions, QWidget* parent)
{
    return QMessageBox::StandardButton::Ok == QMessageBox::information(
        parent,
        title,
        captions
    );
}

bool CCPDF_MessgaeBoxUtils::AskForQuery::
query(QString title, QString captions, QWidget* parent)
{
    return QMessageBox::StandardButton::Yes ==
           QMessageBox::question(parent, title, captions);
}

void CCPDF_MessgaeBoxUtils::AboutCCPDFView::
showAbout(QWidget* parent)
{
    return QMessageBox::about(parent, CCPDF_ABOUT::aboutTitle, CCPDF_ABOUT::aboutMain());
}


