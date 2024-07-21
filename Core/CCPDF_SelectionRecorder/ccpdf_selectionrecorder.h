#ifndef CCPDF_SELECTIONRECORDER_H
#define CCPDF_SELECTIONRECORDER_H
#include <QPoint>
#include "CCPDF_Global.h"

class CCPDF_SelectionRecorder
{
public:
    CCPDF_SelectionRecorder() = default;
    DISABLE_COPY(CCPDF_SelectionRecorder);
    void            setStartPoint(const QPoint& s){startSelectPoint = s;}
    void            setEndPoint(const QPoint& s){endSelectPoint = s;}
    QPair<QPoint,
          QPoint>   getResultRecording(){return {startSelectPoint, endSelectPoint};}
    void            setIsRecording(bool st){isRecording = st;}
    bool            getIsRecording() const {return isRecording;}
private:
    QPoint          startSelectPoint;
    QPoint          endSelectPoint;
    bool            isRecording{false};
};

#endif // CCPDF_SELECTIONRECORDER_H
