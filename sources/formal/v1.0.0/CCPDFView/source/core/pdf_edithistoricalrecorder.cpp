#include "pdf_edithistoricalrecorder.h"

void PDF_EditHistoricalRecorder::enMapRecord(QGraphicsItem* who, OperateType what)
{
    mapRecording.push_back(Record(who, what));
}

void PDF_EditHistoricalRecorder::deMapRecord()
{
    mapRecording.pop_back();
}

void  PDF_EditHistoricalRecorder::transForResumeLast()
{
    if(mapRecording.isEmpty())
        return;
    Record& last = mapRecording.last();
    mapRecording.removeLast();
    mapGarbage.push_back(last);
}

void  PDF_EditHistoricalRecorder::transForMoveForward()
{
    if(mapGarbage.isEmpty())
        return;
    Record& last = mapGarbage.last();
    mapGarbage.removeLast();
    mapRecording.push_back(last);
}

void PDF_EditHistoricalRecorder::cancelDeRecord()
{
    if(garbageBin.empty()){
        return;
    }
    auto items = garbageBin.last();
    garbageBin.removeOne(items);
    recorders.push_back(items);
    configScene->addItem(items);
}

void PDF_EditHistoricalRecorder::cancelEnRecord()
{
    if(recorders.empty()){
        return;
    }
    auto items = recorders.last();
    recorders.removeOne(items);
    garbageBin.push_back(items);
    configScene->removeItem(items);
}

void PDF_EditHistoricalRecorder::enRecord(QGraphicsItem* items)
{
    if(configScene->items().contains(items)){
        return;
    }
    enMapRecord(items, OperateType::PUSH_A_NEW);
    recorders.push_back(items);
    configScene->addItem(items);

}

void PDF_EditHistoricalRecorder::deRecord(QGraphicsItem* items)
{
    if(!recorders.contains(items)){
        return;
    }
    enMapRecord(items, OperateType::DELETE_A_OLD);
    recorders.removeOne(items);
    garbageBin.push_back(items);
    configScene->removeItem(items);
}

void PDF_EditHistoricalRecorder::resumeAllThrow()
{
    recorders.clear();
    for(auto items : recorders)
    {
        garbageBin.removeOne(items);
        recorders.push_back(items);
        configScene->addItem(items);
    }
}

void PDF_EditHistoricalRecorder::resumeToLast()
{
    if(mapRecording.size() == 0){
        return; // avoid operate empty
    }
    Record& last = mapRecording.last();
    switch (last.second) {
    case OperateType::PUSH_A_NEW:
        cancelEnRecord();
        break;
    case OperateType::DELETE_A_OLD:
        cancelDeRecord();
        break;
    default:
        break;
    }
    transForResumeLast();
}

void PDF_EditHistoricalRecorder::backToResumeOpNext()
{
    if(mapGarbage.size() == 0){
        return; // avoid operate empty
    }
    Record& last = mapGarbage.last();
    switch (last.second) {
    case OperateType::PUSH_A_NEW:
        cancelDeRecord();
        break;
    case OperateType::DELETE_A_OLD:
        cancelEnRecord();
        break;
    default:
        break;
    }
    transForMoveForward();
}


void PDF_EditHistoricalRecorder::moveRecordersToGarbage()
{
    for(auto i : recorders)
    {
        deRecord(i);
    }
}

PDF_EditHistoricalRecorder::~PDF_EditHistoricalRecorder()
{
    for(auto i : mapRecording)
    {
        if(i.first)
            delete i.first;
        i.first = nullptr;
    }
    for(auto i : mapGarbage)
    {
        if(i.first)
            delete i.first;
        i.first = nullptr;
    }
    recorders.clear();
    garbageBin.clear();
}
