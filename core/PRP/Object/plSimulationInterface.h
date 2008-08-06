#ifndef _PLSIMULATIONINTERFACE_H
#define _PLSIMULATIONINTERFACE_H

#include "plObjInterface.h"

DllClass plSimulationInterface : public plObjInterface {
public:
    enum plSimulationProperties {
        kDisable, kWeightless, kPinned, kWarp, kUpright, kPassive,
        kRotationForces, kCameraAvoidObject, kPhysAnim, kStartInactive,
        kNoSynchronize, kSuppressed, kNoOwnershipChange, kAvAnimPushable,
        kNumProps
    };

protected:
    plKey fPhysical;

public:
    plSimulationInterface();
    virtual ~plSimulationInterface();

    DECLARE_CREATABLE(plSimulationInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    plKey getPhysical() const;
    void setPhysical(plKey phys);
};

#endif
