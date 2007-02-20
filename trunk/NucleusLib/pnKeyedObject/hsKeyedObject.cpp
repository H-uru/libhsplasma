#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

hsKeyedObject::hsKeyedObject(PlasmaVer pv) : myKey(NULL), koFlags(0) { }

hsKeyedObject::~hsKeyedObject() {
    if (myKey != NULL)
        myKey->UnRef();
}

short hsKeyedObject::ClassIndex() { return 0x0002; }

void hsKeyedObject::read(hsStream * S) {
    if (myKey != NULL)
        myKey->UnRef();
    myKey = plResManager::inst->readRealKey(S);
    myKey->Ref();
    myKey->objPtr = this;
}

void hsKeyedObject::write(hsStream * S) {
    plResManager::inst->writeRealKey(S, myKey);
}

plKey* hsKeyedObject::getKey() {
    return myKey;
}