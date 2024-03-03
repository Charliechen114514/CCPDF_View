#ifndef CLASSRELATIONSHIPGRAPHICVIEW_H
#define CLASSRELATIONSHIPGRAPHICVIEW_H

#include <QGraphicsView>
class QGraphicsScene;
class DrawingRect;
class PDF_EditHistoricalRecorder;
class MarkerPropertySetter;
class TextItemPropertySetter;
class EditPDF_MainWindow;
class PDF_EditGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    enum class FlagState{
        CREATING_MARKER,
        CREATING_TEXT,
        DEFAULT_MOVING
    };

    const short DEFAULT_MARKER_LENGTH   = 10;
    const short DEFAULT_MARKER_WIDTH    = 20;
    const short DEFAULT_TEXT_LENGTH     = 100;
    const short DEFAULT_TEXT_HEIGHT     = 50;
    PDF_EditGraphicView(QWidget* parent = nullptr);
    ~PDF_EditGraphicView();
    void                                initBasic();
    void                                bindBackGroundImage(QImage i);
    QGraphicsScene*                     sceneInterFace(){return this->scene;}
    void                                clearItemsAndRedraw(QList<QGraphicsItem*> it);
    void                                setViewState(FlagState f){currentViewState = f;}
    MarkerPropertySetter*               interfaceOfMarkerManager(){return markerPropertyManager;}
    TextItemPropertySetter*             interfaceOfTextManager(){return this->textPropertyManager;}
    PDF_EditHistoricalRecorder*         interfaceOfHistoryManager(){return historyRecorder;}
    void                                clearSelectedItems();
    void                                resumeLastState();
    void                                resumeLastResume();
    void                                clearAllItems();


signals:
    void                                EmitTheFinishCreation();

public slots:
    void                                mousePressEvent(QMouseEvent*);
    void                                mouseMoveEvent(QMouseEvent*);
    void                                mouseReleaseEvent(QMouseEvent*);

private:
    FlagState                           currentViewState = FlagState::DEFAULT_MOVING;
    QGraphicsScene*                     scene = nullptr;
    QPixmap                             backgroundImage;
    PDF_EditHistoricalRecorder*         historyRecorder = nullptr;
    MarkerPropertySetter*               markerPropertyManager;
    TextItemPropertySetter*             textPropertyManager;
    void                                bindScene(QGraphicsScene* scene = nullptr);
    void                                createDrawingRect(QPoint where);
    void                                createDrawingText(QPoint where);
};

#endif // CLASSRELATIONSHIPGRAPHICVIEW_H
