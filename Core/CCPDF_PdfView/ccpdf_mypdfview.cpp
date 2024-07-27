#include "CCPDF_PdfView/ccpdf_mypdfview.h"
#include <QScrollBar>
#include <QScrollArea>
#include <QPdfPageNavigator>
#include <QPdfDocument>
CCPDF_MyPDFView::CCPDF_MyPDFView(QWidget* parent):QPdfView(parent)
{}


void CCPDF_MyPDFView::startRecordingDragging(QMouseEvent* e)
{
    QPoint begin_pos = e->pos();
    grab_recorder.setStart(begin_pos);
    grab_recorder.setIsGragging(true);
    fromBeginScrollBarValue.first = horizontalScrollBar()->value();
    fromBeginScrollBarValue.second = verticalScrollBar()->value();
}

void CCPDF_MyPDFView::doMakeGragging(QMouseEvent* e)
{
    grab_recorder.setEnd(e->pos());
    auto res = grab_recorder.caculateTheOffSet();
    qDebug() << res.first << ", " << res.second;
    horizontalScrollBar()->setValue(
        fromBeginScrollBarValue.first - res.first
        );
    verticalScrollBar()->setValue(
        fromBeginScrollBarValue.second - res.second
        );
}


void CCPDF_MyPDFView::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::RightButton)
    {
        startRecordingDragging(e);
    }
    e->ignore();
}

void CCPDF_MyPDFView::mouseMoveEvent(QMouseEvent* e)
{
    if(grab_recorder.isGragging())
    {
        doMakeGragging(e);
    }
    e->ignore();
}

void CCPDF_MyPDFView::mouseReleaseEvent(QMouseEvent* e)
{
    if(grab_recorder.isGragging())
    {
        grab_recorder.setIsGragging(false);
    }
    e->ignore();
}
