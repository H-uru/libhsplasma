#include "hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

hsKeyedObject::hsKeyedObject() : myKey(NULL), koFlags(0) { }

hsKeyedObject::~hsKeyedObject() {
    if (myKey != NULL)
        myKey->UnRef();
}

short hsKeyedObject::ClassIndex() { return kKeyedObject; }
short hsKeyedObject::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kKeyedObject, ver);
}

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
    prc->writeSimpleTag(ClassName());
    prc->writeSimpleTag("MyKey");
    myKey->prcWrite(S, prc);
    prc->closeTag();
}
