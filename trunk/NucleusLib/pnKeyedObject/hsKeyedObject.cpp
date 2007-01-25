#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

unsigned short hsKeyedObject::hsKeyedObjectClassIndex;
hsKeyedObject::hsKeyedObject(PlasmaVer pv) : myKey(NULL), koFlags(0) { }

hsKeyedObject::~hsKeyedObject() {
    if (myKey != NULL)
        myKey->UnRef();
}

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
