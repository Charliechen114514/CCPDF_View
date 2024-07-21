#ifndef CCPDF_MYPDFVIEW_H
#define CCPDF_MYPDFVIEW_H
#include "CCPDF_GragRecorder/ccpdf_gragpointrecorder.h"
#include "CCPDF_SelectionRecorder/ccpdf_selectionrecorder.h"
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
    // Grags handle
    void    startRecordingDragging(QMouseEvent *e);
    void    doMakeGragging(QMouseEvent *e);
    void    startRecordingSelection(QMouseEvent *e);
    void    doMakeSelection(QMouseEvent *e);

    bool    editMode{true};

    // For the Right Button Click
    CCPDF_GragPointRecorder     grab_recorder;
    QPair<int, int>             fromBeginScrollBarValue{0, 0};

    CCPDF_SelectionRecorder     selection_recorder;
    // for selections

};

#endif // CCPDF_MYPDFVIEW_H
