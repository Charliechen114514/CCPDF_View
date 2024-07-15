#ifndef CCPDF_THEME_ACTION_H
#define CCPDF_THEME_ACTION_H

#include <QAction>

class CCPDF_Theme_Action : public QAction
{
    Q_OBJECT
public:
    explicit    CCPDF_Theme_Action(QObject *parent = nullptr);
signals:
    void        tellSelfName(const QString filePath);
    void        tellRemoveThis(const QString filePath);
private:
    void        _pvtDoEmitSelfSig(){emit tellSelfName(this->text());}
    void        _pvtTellRemoveThis(){emit tellRemoveThis(this->text());}
};

#endif // CCPDF_THEME_ACTION_H
