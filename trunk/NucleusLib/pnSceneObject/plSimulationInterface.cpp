#include "plSimulationInterface.h"

plSimulationInterface::plSimulationInterface() {
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kWeightless_DEAD, "kWeightless");
    fProps.setName(kPinned, "kPinned");
    fProps.setName(kWarp_DEAD, "kWarp");
    fProps.setName(kUpright_DEAD, "kUpright");
    fProps.setName(kPassive, "kPassive");
    fProps.setName(kRotationForces_DEAD, "kRotationForces");
    fProps.setName(kCameraAvoidObject_DEAD, "kCameraAvoidObject");
    fProps.setName(kPhysAnim, "kPhysAnim");
    fProps.setName(kStartInactive, "kStartInactive");
    fProps.setName(kNoSynchronize, "kNoSynchronize");
    fProps.setName(kSuppressed_DEAD, "kSuppressed");
    fProps.setName(kNoOwnershipChange, "kNoOwnershipChange");
    fProps.setName(kAvAnimPushable, "kAvAnimPushable");
}

plSimulationInterface::~plSimulationInterface() { }

IMPLEMENT_CREATABLE(plSimulationInterface, kSimulationInterface, plObjInterface)

void plSimulationInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    if (S->getVer() < pvEoa) {
        fProps.read(S);
        S->readInt();
    }
    fPhysical = mgr->readKey(S);
}

void plSimulationInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    if (S->getVer() < pvEoa) {
        fProps.write(S);
        S->writeInt(0);
    }
    mgr->writeKey(S, fPhysical);
}

void plSimulationInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Properties");
    fProps.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Physical");
    fPhysical->prcWrite(prc);
    prc->closeTag();
}
