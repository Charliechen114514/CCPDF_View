#ifndef PDF_EDITHISTORICALRECORDER_H
#define PDF_EDITHISTORICALRECORDER_H
#include <QGraphicsItem>
#include <QGraphicsScene>

class PDF_EditHistoricalRecorder
{
public:
    enum class OperateType
    {
        PUSH_A_NEW,
        DELETE_A_OLD,
    };

    PDF_EditHistoricalRecorder() = default;
    PDF_EditHistoricalRecorder(const PDF_EditHistoricalRecorder&) = delete;
    const PDF_EditHistoricalRecorder&   operator=(const PDF_EditHistoricalRecorder&) = delete;
    ~PDF_EditHistoricalRecorder();
    void                                setScene(QGraphicsScene* s){configScene = s;};
    void                                enRecord(QGraphicsItem* items);
    void                                deRecord(QGraphicsItem* items);
    void                                clearGarbage(){garbageBin.clear();}
    void                                clearRecorder(){recorders.clear();}
    void                                moveRecordersToGarbage();
    void                                clearToBegin(){clearGarbage();clearRecorder();}
    void                                resumeToLast();
    void                                backToResumeOpNext();
    void                                resumeAllThrow();
    QList<QGraphicsItem*>&              getTheRecorders(){return recorders;};
private:
    using Record = QPair<QGraphicsItem*, OperateType>;
    QList<Record>                       mapRecording;
    QList<Record>                       mapGarbage;
    void                                transForResumeLast();
    void                                transForMoveForward();
    QList<QGraphicsItem*>               recorders;
    QList<QGraphicsItem*>               garbageBin;
    QGraphicsScene*                     configScene = nullptr;
    void                                cancelDeRecord();
    void                                cancelEnRecord();
    void                                enMapRecord(QGraphicsItem* who, OperateType what);
    void                                deMapRecord();
};

#endif // PDF_EDITHISTORICALRECORDER_H
