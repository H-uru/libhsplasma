#ifndef _PFOBJECTFLOCKER_H
#define _PFOBJECTFLOCKER_H

#include "PRP/Modifier/plModifier.h"

DllStruct pfFlock {
    float fGoalWeight, fRandomWeight;
    float fSeparationWeight, fSeparationRadius;
    float fCohesionWeight, fCohesionRadius;
    float fMaxForce, fMaxSpeed, fMinSpeed;

    pfFlock();
};

DllClass pfObjectFlocker : public plSingleModifier {
protected:
    unsigned char fNumBoids;
    bool fUseTargetRotation, fRandomizeAnimationStart;
    plKey fBoidKey;
    pfFlock fFlock;

public:
    pfObjectFlocker();

    DECLARE_CREATABLE(pfObjectFlocker)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
