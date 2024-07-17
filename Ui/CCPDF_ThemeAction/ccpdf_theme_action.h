#ifndef CCPDF_THEME_ACTION_H
#define CCPDF_THEME_ACTION_H
#include <QAction>
#include <QMenu>

class CCPDF_Theme_Action : public QAction
{
    Q_OBJECT
public:
    explicit    CCPDF_Theme_Action(QObject *parent = nullptr);
    virtual     ~CCPDF_Theme_Action(){qDebug() << " Eraseing the CCPDF_Theme Actions";}
signals:
    void        tellSelfName(const QString filePath);
    void        tellRemoveThis(const QString filePath);
private:
    void        _pvtDoEmitSelfSig(){emit tellSelfName(this->text());}
    void        _pvtTellRemoveThis(){emit tellRemoveThis(this->text());}
    std::unique_ptr<QMenu>  selfDelMenu;
};

#endif // CCPDF_THEME_ACTION_H
