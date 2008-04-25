#include "hsKeyedObject.h"

hsKeyedObject::hsKeyedObject() : koFlags(0) { }

hsKeyedObject::~hsKeyedObject() {
    myKey.DeleteWeakRef();
}

IMPLEMENT_CREATABLE(hsKeyedObject, kKeyedObject, plReceiver)

void hsKeyedObject::read(hsStream* S, plResManager* mgr) {
    myKey.DeleteWeakRef();
    if (S->getVer() == pvLive)
        myKey = mgr->readKey(S);
    else
        myKey = mgr->readUoid(S);
    myKey->setObj(this);
    myKey.CreateWeakRef();
}

void hsKeyedObject::write(hsStream* S, plResManager* mgr) {
    if (S->getVer() == pvLive)
        mgr->writeKey(S, myKey);
    else
        mgr->writeUoid(S, myKey);
}

void hsKeyedObject::IPrcWrite(pfPrcHelper* prc) {
    myKey->prcWrite(prc);
}

const plKey& hsKeyedObject::getKey() const {
    return myKey;
}
