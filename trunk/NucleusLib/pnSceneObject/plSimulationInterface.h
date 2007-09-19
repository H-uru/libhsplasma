#ifndef _PLSIMULATIONINTERFACE_H
#define _PLSIMULATIONINTERFACE_H

#include "plObjInterface.h"

class plSimulationInterface : public plObjInterface {
public:
    enum plSimulationProperties {
        kDisable, kWeightless_DEAD, kPinned, kWarp_DEAD, kUpright_DEAD,
        kPassive, kRotationForces_DEAD, kCameraAvoidObject_DEAD, kPhysAnim,
        kStartInactive, kNoSynchronize, kSuppressed_DEAD, kNoOwnershipChange,
        kAvAnimPushable, kNumProps
    };

protected:
    hsBitVector Props;
    plKey Physical;

public:
    plSimulationInterface();
    virtual ~plSimulationInterface();

    DECLARE_CREATABLE(plSimulationInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

