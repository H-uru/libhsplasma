#ifndef _PLSIMPLEREGIONSENSOR_H
#define _PLSIMPLEREGIONSENSOR_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plMessage.h"

DllClass plSimpleRegionSensor : public plSingleModifier {
    CREATABLE(plSimpleRegionSensor, kSimpleRegionSensor, plSingleModifier)

protected:
    plMessage* fEnterMsg;
    plMessage* fExitMsg;

public:
    plSimpleRegionSensor();
    virtual ~plSimpleRegionSensor();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setEnterMsg(plMessage* msg);
    void setExitMsg(plMessage* msg);
};


DllClass plSwimDetector : public plSimpleRegionSensor {
    CREATABLE(plSwimDetector, kSwimDetector, plSimpleRegionSensor)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};


DllClass plAutoWalkRegion : public plSimpleRegionSensor {
    CREATABLE(plAutoWalkRegion, kAutoWalkRegion, plSimpleRegionSensor)

protected:
    unsigned int fUnknown;

public:
    plAutoWalkRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plRidingAnimatedPhysicalDetector : public plSimpleRegionSensor {
    CREATABLE(plRidingAnimatedPhysicalDetector,
              kRidingAnimatedPhysicalDetector,
              plSimpleRegionSensor)
};

#endif
