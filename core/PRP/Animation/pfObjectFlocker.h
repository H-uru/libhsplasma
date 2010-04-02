#ifndef _PFOBJECTFLOCKER_H
#define _PFOBJECTFLOCKER_H

#include "PRP/Modifier/plModifier.h"

DllClass pfObjectFlocker : public plSingleModifier {
    CREATABLE(pfObjectFlocker, kObjectFlocker, plSingleModifier)

public:
    DllStruct pfFlock {
        float fGoalWeight, fRandomWeight;
        float fSeparationWeight, fSeparationRadius;
        float fCohesionWeight, fCohesionRadius;
        float fMaxForce, fMaxSpeed, fMinSpeed;

        pfFlock();
    };

protected:
    unsigned char fNumBoids;
    bool fUseTargetRotation, fRandomizeAnimationStart;
    plKey fBoidKey;
    pfFlock fFlock;

public:
    pfObjectFlocker();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getNumBoids() const { return fNumBoids; }
    bool getUseTargetRotation() const { return fUseTargetRotation; }
    bool getRandomizeAnimationStart() const { return fRandomizeAnimationStart; }
    plKey getBoidKey() const { return fBoidKey; }

    void setNumBoids(unsigned char boids) { fNumBoids = boids; }
    void setUseTargetRotation(bool use) { fUseTargetRotation = use; }
    void setRandomizeAnimationStart(bool randomize) { fRandomizeAnimationStart = randomize; }
    void setBoidKey(plKey boidKey) { fBoidKey = boidKey; }

    pfFlock& getFlock() { return fFlock; }
};

#endif
