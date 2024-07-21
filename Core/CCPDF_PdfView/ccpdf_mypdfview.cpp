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


static void __calculate_abs_point(QPoint& f, int horizV, int verV, int zoomFactor)
{
    f.setX((f.x() + horizV + 85)/zoomFactor);
    f.setY((f.y() + verV + 50)/zoomFactor);
}


void    CCPDF_MyPDFView::startRecordingSelection(QMouseEvent *e)
{
    QPoint get =  e->position().toPoint();
    __calculate_abs_point(get, horizontalScrollBar()->value(), verticalScrollBar()->value(), zoomFactor());
    selection_recorder.setIsRecording(true);
    selection_recorder.setStartPoint(
        get
    );
    auto doc = document();
    auto nav = pageNavigator();
    auto margin = documentMargins().left();
    qDebug() << margin;
    qDebug() << get;
    qDebug() << doc->getAllText(nav->currentPage()).boundingRectangle();
}

void    CCPDF_MyPDFView::doMakeSelection(QMouseEvent *e)
{
    QPoint get =  e->position().toPoint();
    __calculate_abs_point(get, horizontalScrollBar()->value(), verticalScrollBar()->value(), zoomFactor());
    selection_recorder.setEndPoint(
        get
    );
    auto doc = document();
    auto nav = pageNavigator();
    const auto res = selection_recorder.getResultRecording();
    if(!doc || !nav)return;
    qDebug() << res;
    auto selection = doc->getSelection(nav->currentPage(), res.first, res.second);
    if(!selection.text().isEmpty()){
        qDebug() << "Fetch";
        qDebug() << selection.boundingRectangle().toRect();
        qDebug() << selection.text();
    }
}


void CCPDF_MyPDFView::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::RightButton)
    {
        startRecordingDragging(e);
    }
    if(e->button() == Qt::LeftButton)
    {
        startRecordingSelection(e);
    }
    e->ignore();
}

void CCPDF_MyPDFView::mouseMoveEvent(QMouseEvent* e)
{
    if(grab_recorder.isGragging())
    {
        doMakeGragging(e);
    }
    if(selection_recorder.getIsRecording())
    {
        doMakeSelection(e);
    }
    e->ignore();
}

void CCPDF_MyPDFView::mouseReleaseEvent(QMouseEvent* e)
{
    if(grab_recorder.isGragging())
    {
        grab_recorder.setIsGragging(false);
    }
    if(selection_recorder.getIsRecording()){
        selection_recorder.setIsRecording(false);
    }
    e->ignore();
}
