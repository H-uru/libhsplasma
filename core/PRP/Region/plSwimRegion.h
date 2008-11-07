#ifndef _PLSWIMREGION_H
#define _PLSWIMREGION_H

#include "PRP/Object/plObjInterface.h"

DllClass plSwimRegionInterface : public plObjInterface {
protected:
    float fDownBuoyancy, fUpBuoyancy, fMaxUpwardVel;

public:
    plSwimRegionInterface();

    DECLARE_CREATABLE(plSwimRegionInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSwimCircularCurrentRegion : public plSwimRegionInterface {
protected:
    float fRotation;
    float fPullNearDistSq, fPullFarDistSq;
    float fPullNearVel, fPullFarVel;
    plKey fCurrentObj;

public:
    plSwimCircularCurrentRegion();

    DECLARE_CREATABLE(plSwimCircularCurrentRegion)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSwimStraightCurrentRegion : public plSwimRegionInterface {
protected:
    float fNearDist, fFarDist;
    float fNearVel, fFarVel;
    plKey fCurrentObj;

public:
    plSwimStraightCurrentRegion();

    DECLARE_CREATABLE(plSwimStraightCurrentRegion)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
