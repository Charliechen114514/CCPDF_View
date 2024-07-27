#include <QPropertyAnimation>
#include "ccpdf_animanations.h"

void CCPDF_Animanations::animationInit()
{
    animationCore = std::make_unique<QPropertyAnimation>();
    animationCore->setEasingCurve(QEasingCurve::OutBounce);
}

void CCPDF_Animanations::bindObjectAndProperty(QObject *target, const char* property)
{
    if(!animationCore)
        animationInit();
    animationCore->setPropertyName(property);
    animationCore->setTargetObject(target);
}

QObject* CCPDF_Animanations::object()
{
    return animationCore ? animationCore->targetObject() : nullptr;
}

void CCPDF_Animanations::setDuration(const int msec){
    if(!animationCore)
        animationInit();
    animationCore->setDuration(msec);
}

void CCPDF_BinaryStateAnimations::setBeginState(const QVariant& beginState)
{
    if(!animationCore)
        return;
    beginVariant = beginState;
}

void CCPDF_BinaryStateAnimations::setEndState(const QVariant& endState)
{
    if(!animationCore)
        return;
    endVariant = endState;
}

void CCPDF_BinaryStateAnimations::setPositive()
{
    animationCore->setStartValue(beginVariant);
    animationCore->setEndValue(endVariant);
}
void CCPDF_BinaryStateAnimations::setReversive()
{
    animationCore->setEndValue(beginVariant);
    animationCore->setStartValue(endVariant);
}

void CCPDF_BinaryStateAnimations::startPositiveAnimation()
{
    if(!animationCore)
        return;
    setPositive();

    animationCore->start();
}


void CCPDF_BinaryStateAnimations::startReversiveAnimation()
{
    if(!animationCore)
        return;
    setReversive();
    animationCore->start();
}

void CCPDF_BinaryStateAnimations::startAnimation(bool doPositive)
{
    if(doPositive)  startPositiveAnimation();
    else            startReversiveAnimation();
}

void CCPDF_BinaryStateParalAnimation::doParalAnimation(bool st)
{
    if(!core_group)
    {
        core_group = std::make_unique<QParallelAnimationGroup>();
        for(auto& each : lists)
        {
            core_group->addAnimation(each->getAnimation());
        }
    }

    if(st){
        for(auto& each : lists) each->setPositive();
    }else{
        for(auto& each : lists) each->setReversive();
    }
    core_group->start();
}







