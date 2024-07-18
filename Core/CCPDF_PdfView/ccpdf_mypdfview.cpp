#include "CCPDF_PdfView/ccpdf_mypdfview.h"
#include <QScrollBar>
CCPDF_MyPDFView::CCPDF_MyPDFView(QWidget* parent):QPdfView(parent)
{}


void CCPDF_MyPDFView::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::RightButton)
    {
        qDebug() << "Get Mouse button";
        QPoint begin_pos = e->pos();
        recorder.setStart(begin_pos);
        recorder.setIsGragging(true);
        fromBeginScrollBarValue.first = horizontalScrollBar()->value();
        fromBeginScrollBarValue.second = verticalScrollBar()->value();
    }
    e->ignore();
}

void CCPDF_MyPDFView::mouseMoveEvent(QMouseEvent* e)
{
    if(recorder.isGragging())
    {
        qDebug() << "Now it is dragging mode";
        recorder.setEnd(e->pos());
        auto res = recorder.caculateTheOffSet();
        qDebug() << res.first << ", " << res.second;
        horizontalScrollBar()->setValue(
            fromBeginScrollBarValue.first - res.first
        );
        verticalScrollBar()->setValue(
            fromBeginScrollBarValue.second - res.second
        );
    }
    e->ignore();
}

void CCPDF_MyPDFView::mouseReleaseEvent(QMouseEvent* e)
{
    recorder.setIsGragging(false);
    qDebug() << "Right Mouse Button release! do stop dragging!";
    e->ignore();
}
