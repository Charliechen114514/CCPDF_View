#ifndef CCPDF_HISTORYACTION_H
#define CCPDF_HISTORYACTION_H

#include <QAction>

class CCPDF_HistoryAction : public QAction
{
    Q_OBJECT
public:
    explicit    CCPDF_HistoryAction(QString restored_path, QString text, QObject *parent = nullptr);
    QString     holding_path(){return restored_path;}
private:
    QString     restored_path;
    void        _doEmitPvtSignal(){emit tellSelfPdfPath(restored_path);}
signals:
    void        tellSelfPdfPath(QString self_file_path);
};

#endif // CCPDF_HISTORYACTION_H

