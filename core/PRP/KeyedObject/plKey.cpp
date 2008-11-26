#include <stdlib.h>
#include <string.h>
#include "plKey.h"
#include "hsKeyedObject.h"
#include "Debug/plDebug.h"

/* plKeyData */
plKeyData::plKeyData() : fUoid(), fObjPtr(NULL), fFileOff(0), fObjSize(0),
                         fRefCnt(0) { }

plKeyData::~plKeyData() {
    if (fObjPtr != NULL) {
        Ref();
        delete fObjPtr;
       --fRefCnt;  // Under absolutely NO circumstance replace this with UnRef()
    }
}

bool plKeyData::operator==(plKeyData& other) const {
    return (fUoid == other.fUoid);
}

plString plKeyData::toString() const {
    if (this == NULL)
        return "NULL";
    return fUoid.toString();
}

void plKeyData::read(hsStream* S) {
    fUoid.read(S);
    fFileOff = S->readInt();
    fObjSize = S->readInt();
}

void plKeyData::write(hsStream* S) {
    fUoid.write(S);
    S->writeInt(fFileOff);
    S->writeInt(fObjSize);
}

void plKeyData::readUoid(hsStream* S) {
    fUoid.read(S);
}

void plKeyData::writeUoid(hsStream* S) {
    fUoid.write(S);
}

void plKeyData::prcWrite(pfPrcHelper* prc) {
    if (this == NULL || !getLocation().isValid()) {
        prc->startTag("plKey");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    } else {
        fUoid.prcWrite(prc);
    }
}

plKeyData* plKeyData::PrcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    if (!tag->getParam("NULL", "false").toBool()) {
        plKeyData* key = new plKeyData();
        key->fUoid.prcParse(tag);
        return key;
    } else {
        return NULL;
    }
}

plUoid& plKeyData::getUoid() { return fUoid; }
class hsKeyedObject* plKeyData::getObj() { return fObjPtr; }
void plKeyData::setObj(class hsKeyedObject* obj) { fObjPtr = obj; }

short plKeyData::getType() const { return fUoid.getType(); }
const plString& plKeyData::getName() const { return fUoid.getName(); }
const plLocation& plKeyData::getLocation() const { return fUoid.getLocation(); }
const plLoadMask& plKeyData::getLoadMask() const { return fUoid.getLoadMask(); }
hsUint32 plKeyData::getID() const { return fUoid.getID(); }
hsUint32 plKeyData::getFileOff() const { return fFileOff; }
hsUint32 plKeyData::getObjSize() const { return fObjSize; }

void plKeyData::setType(short type) { fUoid.setType(type); }
void plKeyData::setName(const plString& name) { fUoid.setName(name); }
void plKeyData::setLocation(const plLocation& loc) { fUoid.setLocation(loc); }
void plKeyData::setLoadMask(const plLoadMask& mask) { fUoid.setLoadMask(mask); }
void plKeyData::setID(hsUint32 id) { fUoid.setID(id); }
void plKeyData::setFileOff(hsUint32 off) { fFileOff = off; }
void plKeyData::setObjSize(hsUint32 size) { fObjSize = size; }

hsUint32 plKeyData::RefCnt() const { return fRefCnt; }
hsUint32 plKeyData::Ref() { return ++fRefCnt; }

void plKeyData::UnRef() {
    if (--fRefCnt == 0) {
        //plDebug::Debug("Key %s no longer in use, deleting...", toString().cstr());
        delete this;
    }
}


/* plWeakKey */
plWeakKey::plWeakKey() : fKeyData(NULL) { }
plWeakKey::plWeakKey(const plWeakKey& init) : fKeyData(init) { }
plWeakKey::plWeakKey(plKeyData* init) : fKeyData(init) { }
plWeakKey::~plWeakKey() { }

plWeakKey::operator plKeyData*() const { return fKeyData; }
plKeyData& plWeakKey::operator*() const { return *fKeyData; }
plKeyData* plWeakKey::operator->() const { return fKeyData; }

plWeakKey& plWeakKey::operator=(const plWeakKey& other) {
    fKeyData = other;
    return *this;
}

plWeakKey& plWeakKey::operator=(plKeyData* other) {
    fKeyData = other;
    return *this;
}

bool plWeakKey::operator==(const plWeakKey& other) const {
    return fKeyData == other.fKeyData;
}

bool plWeakKey::operator==(const plKeyData* other) const {
    return fKeyData == other;
}

bool plWeakKey::operator!=(const plWeakKey& other) const {
    return fKeyData != other.fKeyData;
}

bool plWeakKey::operator!=(const plKeyData* other) const {
    return fKeyData != other;
}

bool plWeakKey::operator<(const plWeakKey& other) const {
    return fKeyData->getUoid() < other->getUoid();
}

bool plWeakKey::Exists() const {
    return (fKeyData != NULL);
}

bool plWeakKey::isLoaded() const {
    if (!Exists())
        return true;
    return fKeyData->getObj() != NULL;
}


/* plKey */
plKey::plKey() { }

plKey::plKey(const plWeakKey& init) : plWeakKey(init) {
    if (fKeyData) fKeyData->Ref();
}

plKey::plKey(const plKey& init) : plWeakKey(init) {
    if (fKeyData) fKeyData->Ref();
}

plKey::plKey(plKeyData* init) : plWeakKey(init) {
    if (fKeyData) fKeyData->Ref();
}

plKey::~plKey() {
    if (fKeyData) fKeyData->UnRef();
}

plKey& plKey::operator=(const plWeakKey& other) {
    if (*this != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        *this = other;
    }
    return *this;
}

plKey& plKey::operator=(const plKey& other) {
    if (*this != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        fKeyData = other;
    }
    return *this;
}

plKey& plKey::operator=(plKeyData* other) {
    if (fKeyData != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        fKeyData = other;
    }
    return *this;
}
