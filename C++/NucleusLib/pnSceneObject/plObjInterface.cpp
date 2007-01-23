#include "plObjInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plObjInterface::plObjInterface(PlasmaVer pv) {
    Owner = new plKey();
}

plObjInterface::~plObjInterface() {
    Owner->UnRef();
}

bool plObjInterface::msgReceive(plMessage * msg) {
    // Later
    return false;
}

void plObjInterface::read(hsStream *S) {
    plSynchedObject::read(S);
    Owner = plResManager::inst->readKey(S);
    Owner->Ref();
    Properties.read(S);
}

void plObjInterface::write(hsStream *S) {
    plSynchedObject::write(S);
    plResManager::inst->writeKey(S, Owner);
    Properties.write(S);
}

