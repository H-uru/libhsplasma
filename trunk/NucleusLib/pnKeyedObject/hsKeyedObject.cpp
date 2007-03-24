#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

hsKeyedObject::hsKeyedObject(PlasmaVer pv) : myKey(NULL), koFlags(0) { }

hsKeyedObject::~hsKeyedObject() {
    if (myKey != NULL)
        myKey->UnRef();
}

short hsKeyedObject::ClassIndex() { return 0x0002; }
const char* hsKeyedObject::ClassName() { return "hsKeyedObject"; }

void hsKeyedObject::read(hsStream * S) {
    if (myKey != NULL)
        myKey->UnRef();
    myKey = plResManager::inst->readUoidKey(S);
    myKey->Ref();
    myKey->objPtr = this;
}

void hsKeyedObject::write(hsStream * S) {
    plResManager::inst->writeUoidKey(S, myKey);
}

plKey* hsKeyedObject::getKey() {
    return myKey;
}

void hsKeyedObject::prcWrite(hsStream* S, pfPrcHelper* prc) {
    prc->writeSimpleTag(S, ClassName());
    prc->writeSimpleTag(S, "MyKey");
      myKey->prcWrite(S, prc); // Short tag
    prc->endTag(S);
}
