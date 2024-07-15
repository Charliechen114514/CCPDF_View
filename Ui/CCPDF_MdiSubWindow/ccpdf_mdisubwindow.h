#ifndef CCPDF_MDISUBWINDOW_H
#define CCPDF_MDISUBWINDOW_H
#include "CCPDF_Global.h"
#include <QKeyEvent>
#include <QMdiSubWindow>

class CCPDF_SinglePDF_Widget;

class CCPDF_MdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    CCPDF_MdiSubWindow(QWidget* parent);
    ~CCPDF_MdiSubWindow() = default;
    virtual void setWidget(QWidget* w);
    virtual void keyPressEvent(QKeyEvent* env){
        env->ignore();
    }
    virtual void closeEvent(QCloseEvent* env);

private:
    __MEMEROY_HOLD_BY_OBJ_TREE  CCPDF_SinglePDF_Widget* w;
signals:
    void self_close(QString path);
};

#endif // CCPDF_MDISUBWINDOW_H
