#include "qevent.h"
#include <QGraphicsScene>

#include "PDF_EditGraphicView.h"
#include "markerpropertysetter.h"
#include "pdf_edithistoricalrecorder.h"
#include "paintingpackage.h"
PDF_EditGraphicView::PDF_EditGraphicView(QWidget* parent): QGraphicsView(parent)
{
    initBasic();
}

void PDF_EditGraphicView::bindScene(QGraphicsScene* scene)
{
    if(scene != nullptr)
    {
        if(this->scene != nullptr)
            delete this->scene;
        this->scene = scene;
    }
    else
    {
        if(this->scene == nullptr)
            this->scene = new QGraphicsScene(this);
    }
    this->setScene(this->scene);
}

void PDF_EditGraphicView::initBasic()
{
    bindScene();
    historyRecorder = new PDF_EditHistoricalRecorder;
    historyRecorder->setScene(scene);
    markerPropertyManager = new MarkerPropertySetter;
    textPropertyManager = new TextItemPropertySetter;
}

void PDF_EditGraphicView::clearSelectedItems()
{
    if(!historyRecorder)
        return;
    for(auto each : scene->selectedItems())
    {
        historyRecorder->deRecord(each);
    }
}

void PDF_EditGraphicView::resumeLastState()
{
    if(!historyRecorder)
        return;
    historyRecorder->resumeToLast();
}

void PDF_EditGraphicView::resumeLastResume()
{
    if(!historyRecorder)
        return;
    historyRecorder->backToResumeOpNext();
}

void PDF_EditGraphicView::clearAllItems()
{
    if(!historyRecorder)
        return;
    for(auto items : scene->items())
        scene->removeItem(items);
    historyRecorder->clearToBegin();
}

void PDF_EditGraphicView::bindBackGroundImage(QImage i)
{
    if(!i.isNull())
    {
        backgroundImage = QPixmap::fromImage(i);
        scene->addPixmap(backgroundImage);
    }
}

void PDF_EditGraphicView::createDrawingRect(QPoint where)
{
    QPointF real = mapToScene(where);
    DrawingRect* d = new DrawingRect(QRect(real.x(), real.y(), DEFAULT_MARKER_LENGTH, DEFAULT_MARKER_WIDTH));
    markerPropertyManager->setProperty(d);
    historyRecorder->enRecord(d);
}

void PDF_EditGraphicView::createDrawingText(QPoint where)
{
    QPointF real = mapToScene(where);
    DrawingText* t = new DrawingText(QRect(real.x(), real.y(), textPropertyManager->getTextLength(),
                                           textPropertyManager->getTextHeight()));
    textPropertyManager->setProperty(t);
    historyRecorder->enRecord(t);
}


void PDF_EditGraphicView::mousePressEvent(QMouseEvent* e)
{
    if(currentViewState == FlagState::CREATING_MARKER)
    {
        createDrawingRect(e->pos());
    }
    if(currentViewState == FlagState::CREATING_TEXT)
    {
        createDrawingText(e->pos());
    }
    return QGraphicsView::mousePressEvent(e);
}

void PDF_EditGraphicView::mouseMoveEvent(QMouseEvent* e)
{
    return QGraphicsView::mouseMoveEvent(e);
}


void PDF_EditGraphicView::mouseReleaseEvent(QMouseEvent* e[[maybe_unused]])
{
    currentViewState = FlagState::DEFAULT_MOVING;
    emit EmitTheFinishCreation();
    return QGraphicsView::mouseReleaseEvent(e);
}


void PDF_EditGraphicView::clearItemsAndRedraw(QList<QGraphicsItem*> it)
{
    scene->clear();
    scene->addPixmap(backgroundImage);
    for(auto each : it){
        scene->addItem(each);
    }
}

PDF_EditGraphicView::~PDF_EditGraphicView()
{
    delete markerPropertyManager;
    delete historyRecorder;
}



