#include "plObjInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plObjInterface::plObjInterface() : Props() {
    Owner = new plKey();
}

plObjInterface::~plObjInterface() {
    Owner->UnRef();
}

short plObjInterface::ClassIndex() { return kObjInterface; }
short plObjInterface::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kObjInterface, ver);
}


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

void plObjInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);

    prc->writeSimpleTag("Owner");
    Owner->prcWrite(S, prc);
    prc->closeTag();

    prc->writeSimpleTag("Props");
    Props.prcWrite(S, prc);
    prc->closeTag();
}
