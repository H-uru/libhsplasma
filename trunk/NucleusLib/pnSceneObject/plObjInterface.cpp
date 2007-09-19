#include "plObjInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plObjInterface::plObjInterface() { }
plObjInterface::~plObjInterface() { }

IMPLEMENT_CREATABLE(plObjInterface, kObjInterface, plSynchedObject)

void plObjInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    Owner = mgr->readKey(S);
    Props.read(S);
}

void plObjInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, Owner);
    Props.write(S);
}

void plObjInterface::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->writeSimpleTag("Owner");
    Owner->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Props");
    Props.prcWrite(prc);
    prc->closeTag();
}
