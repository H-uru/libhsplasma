#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

hsKeyedObject::hsKeyedObject() : myKey(NULL), koFlags(0) { }

hsKeyedObject::~hsKeyedObject() {
    if (myKey != NULL)
        myKey->UnRef();
}

IMPLEMENT_CREATABLE(hsKeyedObject, kKeyedObject, plReceiver)

void hsKeyedObject::read(hsStream* S) {
    if (myKey != NULL)
        myKey->UnRef();
    myKey = plResManager::inst->readUoidKey(S);
    myKey->Ref();
    myKey->objPtr = this;
}

void hsKeyedObject::write(hsStream* S) {
    plResManager::inst->writeUoidKey(S, myKey);
}

void hsKeyedObject::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);
    myKey->prcWrite(prc);
}

plKey* hsKeyedObject::getKey() {
    return myKey;
}
