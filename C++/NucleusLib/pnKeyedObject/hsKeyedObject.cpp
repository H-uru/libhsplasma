#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

hsKeyedObject::hsKeyedObject(PlasmaVer pv) : koFlags(0) {
    myKey = new plKey();
}

hsKeyedObject::~hsKeyedObject() {
    myKey->UnRef();
}

void hsKeyedObject::read(hsStream * S) {
    myKey = plResManager::inst->readKey(S);
    myKey->Ref();
    myKey->objPtr = this;
}

void hsKeyedObject::write(hsStream * S) {
    plResManager::inst->writeKey(S, myKey);
}

