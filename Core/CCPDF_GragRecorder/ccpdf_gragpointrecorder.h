#ifndef CCPDF_GRAGPOINTRECORDER_H
#define CCPDF_GRAGPOINTRECORDER_H
#include <QPoint>
#include "CCPDF_Global.h"

struct CCPDF_GragPointRecorder
{
public:
    CCPDF_GragPointRecorder() = default;
    DISABLE_COPY(CCPDF_GragPointRecorder);
    bool                isGragging()const{return is_current_dragging;}
    void                setStart(const QPoint& start){m_start_record = start;};
    void                setIsGragging(bool st){is_current_dragging = st;}
    void                setEnd(const QPoint& end){m_end_record = end;}
    QPair<int, int>     caculateTheOffSet();
private:
    bool                is_current_dragging{false};
    QPoint              m_start_record;
    QPoint              m_end_record;
};

#endif // CCPDF_GRAGPOINTRECORDER_H
