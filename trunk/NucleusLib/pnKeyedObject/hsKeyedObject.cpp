#include "hsKeyedObject.h"

hsKeyedObject::hsKeyedObject() : koFlags(0) { }

hsKeyedObject::~hsKeyedObject() { }

IMPLEMENT_CREATABLE(hsKeyedObject, kKeyedObject, plReceiver)

void hsKeyedObject::read(hsStream* S, plResManager* mgr) {
    if (S->getVer() == pvLive)
        myKey = mgr->readKey(S);
    else
        myKey = mgr->readUoid(S);
    myKey->setObj(this);
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

void hsKeyedObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plKey")
        myKey = mgr->prcParseKey(tag);
    else
        plCreatable::IPrcParse(tag, mgr);
}

const plWeakKey& hsKeyedObject::getKey() const {
    return myKey;
}
