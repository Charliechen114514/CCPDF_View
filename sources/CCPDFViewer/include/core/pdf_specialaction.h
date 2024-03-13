#ifndef PDF_SPECIALACTION_H
#define PDF_SPECIALACTION_H

#include <QAction>
class QMenu;
class PDF_SpecialAction : public QAction
{
    Q_OBJECT
public:
    explicit PDF_SpecialAction(QString pdfPath, QObject *parent = nullptr);
    ~PDF_SpecialAction() override = default ;
    bool matchByPath(QString path){return path == pdfPath;}
    QString getPath(){return pdfPath;}
signals:
    void passName(QString path);
public slots:
    void detailedTriggler(){
        emit this->passName(pdfPath);
    }

private:
    QString pdfPath;
};

class PDF_SpecialActionManager
{
public:
    const int default_max_show = 7;
    PDF_SpecialActionManager() = delete;
    PDF_SpecialActionManager(const PDF_SpecialActionManager&) = delete;
    const PDF_SpecialActionManager& operator=(const PDF_SpecialActionManager&) = delete;
    ~PDF_SpecialActionManager();
    PDF_SpecialActionManager(QMenu& binder):binder(binder), maxAllowed(default_max_show){}
    void addToMenu(PDF_SpecialAction* action, bool allowed_duplicate = false);
    void removeAction(QString path);
    void moveLastToFirst();
    void setMaxShow(int max){maxAllowed = max;}
    void refreshMenu();
private:
    QMenu&                      binder;
    int                         maxAllowed;
    QList<PDF_SpecialAction*>   actions;
};



#endif // PDF_SPECIALACTION_H
