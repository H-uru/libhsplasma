#include "hsKeyedObject.h"
#include "Stream/hsRAMStream.h"

/* hsKeyedObject */
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


/* hsKeyedObjectStub */
hsKeyedObjectStub::hsKeyedObjectStub() : fStub(NULL) { }

hsKeyedObjectStub::~hsKeyedObjectStub() {
    if (fStub != NULL)
        delete fStub;
}

short hsKeyedObjectStub::ClassIndex() const {
    return fStub->getClassIdx();
}

const char* hsKeyedObjectStub::ClassName() const {
    return "hsKeyedObjectStub";
}

void hsKeyedObjectStub::write(hsStream* S, plResManager* mgr) {
    fStub->write(S, mgr);
}

void hsKeyedObjectStub::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    fStub->prcWrite(prc);
}

void hsKeyedObjectStub::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plCreatableStub")
        fStub->prcParse(tag, mgr);
    else
        hsKeyedObject::IPrcParse(tag, mgr);
}

const plCreatableStub* hsKeyedObjectStub::getStub() const {
    return fStub;
}

void hsKeyedObjectStub::setStub(plCreatableStub* stub) {
    fStub = stub;
}
