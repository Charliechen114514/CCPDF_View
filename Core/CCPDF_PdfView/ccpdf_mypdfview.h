#ifndef CCPDF_MYPDFVIEW_H
#define CCPDF_MYPDFVIEW_H
#include "CCPDF_GragRecorder/ccpdf_gragpointrecorder.h"
#include <QPdfView>
#include <QKeyEvent>
class CCPDF_MyPDFView : public QPdfView
{
    Q_OBJECT
public:
    CCPDF_MyPDFView(QWidget* parent);
    virtual ~CCPDF_MyPDFView() = default;
    virtual void keyPressEvent(QKeyEvent* e)override{
        e->ignore();
    }

    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent* e)override;
private:
    CCPDF_GragPointRecorder     recorder;
    QPair<int, int>             fromBeginScrollBarValue{0, 0};
};

#endif // CCPDF_MYPDFVIEW_H
