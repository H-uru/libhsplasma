#include "plObjInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plObjInterface::plObjInterface(PlasmaVer pv) : Props() {
    Owner = new plKey();
}

plObjInterface::~plObjInterface() {
    Owner->UnRef();
}

short plObjInterface::ClassIndex() { return 0x0010; }
const char* plObjInterface::ClassName() { return "plObjInterface"; }

void plObjInterface::read(hsStream *S) {
    plSynchedObject::read(S);
    Owner = plResManager::inst->readKey(S);
    Owner->Ref();
    Props.read(S);
}

void plObjInterface::write(hsStream *S) {
    plSynchedObject::write(S);
    plResManager::inst->writeKey(S, Owner);
    Props.write(S);
}

void plObjInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);

    prc->writeSimpleTag("Owner");
    Owner->prcWrite(S, prc);
    prc->closeTag();

    prc->writeSimpleTag("Props");
    Props.prcWrite(S, prc);
    prc->closeTag();
}
