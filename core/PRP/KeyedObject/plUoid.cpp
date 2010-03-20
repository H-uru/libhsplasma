#include "plUoid.h"
#include "ResManager/plFactory.h"
#include "ResManager/pdUnifiedTypeMap.h"
#include <string.h>
#include <stdlib.h>

plUoid::plUoid()
      : classType((short)0x8000), objID(0), clonePlayerID(0), cloneID(0),
        eoaExtra(0) { }

plUoid::plUoid(const plUoid& other)
      : location(other.location), loadMask(other.loadMask),
        classType(other.classType), objName(other.objName), objID(other.objID),
        clonePlayerID(other.clonePlayerID), cloneID(other.cloneID),
        eoaExtra(0) { }

plUoid::~plUoid() { }

plUoid& plUoid::operator=(const plUoid& other) {
    location = other.location;
    loadMask = other.loadMask;
    classType = other.classType;
    objName = other.objName;
    objID = other.objID;
    clonePlayerID = other.clonePlayerID;
    cloneID = other.cloneID;
    return *this;
}

bool plUoid::operator==(const plUoid& other) const {
    return (location == other.location) && (classType == other.classType) &&
           (objName == other.objName);
}

bool plUoid::operator<(const plUoid& other) const {
    if (location == other.location) {
        if (classType == other.classType)
            return objName < other.objName;
        return classType < other.classType;
    }
    return location < other.location;
}

void plUoid::read(hsStream* S) {
    unsigned char contents = S->readByte();
    location.read(S);
    if ((contents & kHasLoadMask) && (S->getVer() < pvEoa || S->getVer() == pvUniversal))
        loadMask.read(S);
    else
        loadMask.setAlways();
    classType = pdUnifiedTypeMap::PlasmaToMapped(S->readShort(), S->getVer());
    if (S->getVer() >= pvLive && S->getVer() != pvUniversal)
        objID = S->readInt();
    objName = S->readSafeStr();
    if ((contents & kHasCloneIDs) && (S->getVer() < pvEoa || S->getVer() == pvUniversal)) {
        cloneID = S->readInt();
        clonePlayerID = S->readInt();
    } else {
        cloneID = clonePlayerID = 0;
    }
    if ((contents & 0x06) && S->getVer() >= pvEoa)
        eoaExtra = S->readByte();
    else eoaExtra = 0;
}

void plUoid::write(hsStream* S) {
    unsigned char contents = 0;
    if (cloneID != 0)
        contents |= kHasCloneIDs;
    if (loadMask.isUsed())
        contents |= kHasLoadMask;
    if (eoaExtra != 0 && S->getVer() >= pvEoa)
        contents |= 0x4;
    S->writeByte(contents);

    location.write(S);
    if ((contents & kHasLoadMask) && (S->getVer() < pvEoa || S->getVer() == pvUniversal))
        loadMask.write(S);
    S->writeShort(pdUnifiedTypeMap::MappedToPlasma(classType, S->getVer()));
    if (S->getVer() >= pvLive && S->getVer() != pvUniversal)
        S->writeInt(objID);
    S->writeSafeStr(objName);
    if ((contents & kHasCloneIDs) && (S->getVer() < pvEoa || S->getVer() == pvUniversal)) {
        S->writeInt(cloneID);
        S->writeInt(clonePlayerID);
    }
    if ((contents & 0x06) && S->getVer() >= pvEoa)
        S->writeByte(eoaExtra);
}

void plUoid::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plKey");
    prc->writeParam("Name", objName);
    prc->writeParam("Type", plFactory::ClassName(classType));
    location.prcWrite(prc);
    if (loadMask.isUsed())
        loadMask.prcWrite(prc);
    if (cloneID != 0) {
        prc->writeParam("CloneID", cloneID);
        prc->writeParam("ClonePlayerID", clonePlayerID);
    }
    if (eoaExtra != 0)
        prc->writeParam("EoaExtra", eoaExtra);
    if (objID != 0)
        prc->writeParam("ObjID", objID);
    prc->endTag(true);
}

void plUoid::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plKey")
        throw hsBadParamException(__FILE__, __LINE__, "Tag name mismatch");

    objName = tag->getParam("Name", "");
    classType = plFactory::ClassIndex(tag->getParam("Type", ""));
    location.prcParse(tag);
    loadMask.prcParse(tag);
    cloneID = tag->getParam("CloneID", "0").toUint();
    clonePlayerID = tag->getParam("ClonePlayerID", "0").toUint();
    eoaExtra = tag->getParam("EoaExtra", "0").toUint();
}

plString plUoid::toString() const {
    return plString::Format("%s[%04hX]%s", location.toString().cstr(),
                            classType, objName.cstr());
}

short plUoid::getType() const { return classType; }
const plString& plUoid::getName() const { return objName; }
const plLocation& plUoid::getLocation() const { return location; }
const plLoadMask& plUoid::getLoadMask() const { return loadMask; }
unsigned int plUoid::getID() const { return objID; }
unsigned int plUoid::getCloneID() const { return cloneID; }
unsigned int plUoid::getClonePlayerID() const { return clonePlayerID; }

void plUoid::setType(short type) { classType = type; }
void plUoid::setName(const plString& name) { objName = name; }
void plUoid::setLocation(const plLocation& loc) { location = loc; }
void plUoid::setLoadMask(const plLoadMask& mask) { loadMask = mask; }
void plUoid::setID(unsigned int id) { objID = id; }

void plUoid::setCloneIDs(unsigned int clone, unsigned int clonePlayer) {
    cloneID = clone;
    clonePlayerID = clonePlayer;
}
