#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

hsKeyedObject::hsKeyedObject() : koFlags(0) { }
hsKeyedObject::~hsKeyedObject() { }

IMPLEMENT_CREATABLE(hsKeyedObject, kKeyedObject, plReceiver)

void hsKeyedObject::read(hsStream* S) {
    myKey = plResManager::inst->readUoidKey(S);
    myKey->setObj(this);
}

void hsKeyedObject::write(hsStream* S) {
    plResManager::inst->writeUoidKey(S, myKey);
}

void hsKeyedObject::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);
    myKey->prcWrite(prc);
}

const plKey& hsKeyedObject::getKey() const {
    return myKey;
}
