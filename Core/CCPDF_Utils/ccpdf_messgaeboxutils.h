#ifndef CCPDF_MESSGAEBOXUTILS_H
#define CCPDF_MESSGAEBOXUTILS_H
#include <QStringList>
class QWidget;

struct CCPDF_MessgaeBoxUtils
{
    struct ErrorInform
    {
        static void tellError(QString title, QString captions, QWidget* parent);
    };

    struct InfoInform
    {
        static bool inform(QString title, QString captions, QWidget* parent);
    };

    struct AskForQuery
    {
        static bool query(QString title, QString captions, QWidget* parent);
    };

    struct AboutCCPDFView
    {
        static void showAbout(QWidget* parent);
    };
};


#endif // CCPDF_MESSGAEBOXUTILS_H
