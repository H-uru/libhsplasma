#ifndef _PLSIMPLEREGIONSENSOR_H
#define _PLSIMPLEREGIONSENSOR_H

#include "PRP/Modifier/plModifier.h"

DllClass plSimpleRegionSensor : public plSingleModifier {
protected:
    plMessage* fEnterMsg;
    plMessage* fExitMsg;

public:
    plSimpleRegionSensor();
    virtual ~plSimpleRegionSensor();

    DECLARE_CREATABLE(plSimpleRegionSensor)

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
public:
    plSwimDetector();

    DECLARE_CREATABLE(plSwimDetector)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};

DllClass plAutoWalkRegion : public plSimpleRegionSensor {
protected:
    unsigned int fUnknown;

public:
    plAutoWalkRegion();

    DECLARE_CREATABLE(plAutoWalkRegion)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plRidingAnimatedPhysicalDetector : public plSimpleRegionSensor {
public:
    plRidingAnimatedPhysicalDetector();

    DECLARE_CREATABLE(plRidingAnimatedPhysicalDetector)
};

#endif
