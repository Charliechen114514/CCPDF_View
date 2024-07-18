#include "ccpdf_gragpointrecorder.h"

QPair<int, int> CCPDF_GragPointRecorder::caculateTheOffSet()
{
    QPoint Offset = m_end_record - m_start_record;
    return {Offset.x(), Offset.y()};
}
