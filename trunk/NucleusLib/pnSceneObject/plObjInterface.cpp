#include "plObjInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plObjInterface::plObjInterface() : Props() {
    Owner = new plKey();
}

plObjInterface::~plObjInterface() {
    Owner->UnRef();
}

IMPLEMENT_CREATABLE(plObjInterface, kObjInterface, plSynchedObject)

void plObjInterface::read(hsStream* S) {
    plSynchedObject::read(S);
    Owner = plResManager::inst->readKey(S);
    Owner->Ref();
    Props.read(S);
}

void plObjInterface::write(hsStream* S) {
    plSynchedObject::write(S);
    plResManager::inst->writeKey(S, Owner);
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
