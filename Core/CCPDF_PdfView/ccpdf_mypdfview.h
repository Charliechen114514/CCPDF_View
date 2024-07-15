#ifndef CCPDF_MYPDFVIEW_H
#define CCPDF_MYPDFVIEW_H

#include <QPdfView>
#include <QKeyEvent>
class CCPDF_MyPDFView : public QPdfView
{
    Q_OBJECT
public:
    CCPDF_MyPDFView(QWidget* parent);
    virtual void keyPressEvent(QKeyEvent* e){
        e->ignore();
    }
};

#endif // CCPDF_MYPDFVIEW_H
