#include "hsKeyedObject.h"
#include "Stream/hsRAMStream.h"

/* hsKeyedObject */
hsKeyedObject::hsKeyedObject() { }
hsKeyedObject::~hsKeyedObject() { }

IMPLEMENT_CREATABLE(hsKeyedObject, kKeyedObject, plReceiver)

void hsKeyedObject::init(const plString& name) {
    myKey = new plKeyData();
    myKey->setType(ClassIndex());
    myKey->setName(name);
    myKey->setObj(this);
}

void hsKeyedObject::read(hsStream* S, plResManager* mgr) {
    if (S->getVer() == pvLive)
        myKey = mgr->readKey(S);
    else
        myKey = mgr->readUoid(S);
    if (myKey != NULL) {
        // In case we're replacing a key
        if (myKey->getObj() != NULL)
            delete myKey->getObj();
        myKey->setObj(this);
    }
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
    if (tag->getName() == "plKey") {
        myKey = mgr->prcParseKey(tag);
        if (myKey != NULL)
            myKey->setObj(this);
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plKey hsKeyedObject::getKey() const { return myKey; }

void hsKeyedObject::setKey(plKey key) {
    myKey = key;
    if (myKey != NULL)
        myKey->setObj(this);
}


/* hsKeyedObjectStub */
hsKeyedObjectStub::hsKeyedObjectStub() : fStub(NULL) { }

hsKeyedObjectStub::~hsKeyedObjectStub() {
    if (fStub != NULL)
        delete fStub;
}

short hsKeyedObjectStub::ClassIndex() const {
    return fStub->ClassIndex();
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
