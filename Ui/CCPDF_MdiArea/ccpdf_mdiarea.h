#ifndef CCPDF_MDIAREA_H
#define CCPDF_MDIAREA_H

#include <QMdiArea>
#include <QKeyEvent>
class CCPDF_MdiArea : public QMdiArea
{
    Q_OBJECT
public:
    CCPDF_MdiArea(QWidget* w);
    virtual void keyPressEvent(QKeyEvent* e){
        QMdiArea::keyPressEvent(e);
        e->ignore();
    }
};

#endif // CCPDF_MDIAREA_H
