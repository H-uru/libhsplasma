#include "plObjInterface.h"

plObjInterface::plObjInterface() {
    fProps.setName(kDisable, "kDisable");
}

plObjInterface::~plObjInterface() { }

IMPLEMENT_CREATABLE(plObjInterface, kObjInterface, plSynchedObject)

void plObjInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fOwner = mgr->readKey(S);
    fProps.read(S);
}

void plObjInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, fOwner);
    fProps.write(S);
}

void plObjInterface::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Owner");
    fOwner->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Props");
    fProps.prcWrite(prc);
    prc->closeTag();
}
