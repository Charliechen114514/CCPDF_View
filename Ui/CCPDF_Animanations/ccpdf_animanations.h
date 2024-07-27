#ifndef CCPDF_ANIMANATIONS_H
#define CCPDF_ANIMANATIONS_H
#include "CCPDF_Global.h"
#include <QVariant>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class CCPDF_Animanations
{
public:
    CCPDF_Animanations() = default;
    DISABLE_COPY(CCPDF_Animanations);
    void    bindObjectAndProperty(QObject *target, const char* property);
    QObject*object();
    void    setDuration(const int msec);
    QPropertyAnimation*         getAnimation(){return animationCore.get();}
    virtual ~CCPDF_Animanations() = default;

protected:
    std::unique_ptr<QPropertyAnimation> animationCore;

private:
    void    animationInit();
};


class CCPDF_BinaryStateAnimations : public CCPDF_Animanations
{
public:
    CCPDF_BinaryStateAnimations() = default;
    DISABLE_COPY(CCPDF_BinaryStateAnimations);
    void                            setBeginState(const QVariant& beginState);
    void                            setEndState(const QVariant& endState);
    void                            setPositive();
    void                            setReversive();
    void                            startPositiveAnimation();
    void                            startReversiveAnimation();
    void                            startAnimation(bool doPositive = true);
protected:
    QVariant                        beginVariant;
    QVariant                        endVariant;
};

class CCPDF_BinaryStateParalAnimation
{
public:
    CCPDF_BinaryStateParalAnimation() = default;
    DISABLE_COPY(CCPDF_BinaryStateParalAnimation);
    void                    addCCPDF_BinaryStateAnimations(CCPDF_BinaryStateAnimations* animation){lists.push_back(animation);}
    void                    doParalAnimation(bool shouldPositive = true);
private:
    QList<CCPDF_BinaryStateAnimations*>         lists;
    std::unique_ptr<QParallelAnimationGroup>    core_group;
};



#endif // CCPDF_ANIMANATIONS_H
