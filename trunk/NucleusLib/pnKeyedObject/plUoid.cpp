#include "plUoid.h"
#include "../pnFactory/plFactory.h"
#include "../../DynLib/pdUnifiedTypeMap.h"
#include <string.h>
#include <malloc.h>

/* plLocation */
plLocation::plLocation() : pageID(), flags(0) { }
plLocation::~plLocation() { }

bool plLocation::operator==(plLocation& other) {
    return pageID == other.pageID;
}

plLocation& plLocation::operator=(plLocation& other) {
    pageID = other.pageID;
    flags = other.flags;
    return *this;
}

int plLocation::getPageNum() { return pageID.getPageNum(); }
int plLocation::getSeqPrefix() { return pageID.getSeqPrefix(); }

void plLocation::set(int pid, int lflags, PlasmaVer pv) {
    pageID.setVer(pv);
    pageID.parse(pid);
    flags = lflags;
}

void plLocation::read(hsStream* S) {
    pageID.read(S);
    if (S->getVer() == pvEoa)
        flags = S->readByte();
    else
        flags = S->readShort();
}

void plLocation::write(hsStream* S) {
    pageID.write(S);
    if (S->getVer() == pvEoa)
        S->writeByte(flags);
    else
        S->writeShort(flags);
}

void plLocation::prcWrite(pfPrcHelper* prc) {
    char buf[32];
    sprintf(buf, "%d;%d", pageID.getSeqPrefix(), pageID.getPageNum());
    prc->writeParam("Location", buf);
    prc->writeParam("LocFlag", flags);
}

void plLocation::invalidate() {
    pageID.invalidate();
    flags = 0;
}

bool plLocation::isValid() { return pageID.isValid(); }
bool plLocation::isReserved() { return (flags & kReserved); }
bool plLocation::isItinerant() { return (flags & kItinerant); }
bool plLocation::isVirtual() { return pageID.unparse() == 0; }
const char* plLocation::toString() { return pageID.toString(); }


/* plUoid */
plUoid::plUoid() : location(), loadMask(), objName(NULL) { }
plUoid::~plUoid() {
    if (objName) free(objName);
}

bool plUoid::operator==(plUoid& other) {
    return (location == other.location) && (classType == other.classType) &&
           (strcmp(objName, other.objName) == 0);
}

plUoid& plUoid::operator=(plUoid& other) {
    location = other.location;
    loadMask = other.loadMask;
    classType = other.classType;
    objName = strdup(other.objName);
    objID = other.objID;
    clonePlayerID = other.clonePlayerID;
    cloneID = other.cloneID;
    return *this;
}

void plUoid::read(hsStream* S) {
    unsigned char contents = S->readByte();
    location.read(S);
    if ((contents & kHasLoadMask) && S->getVer() != pvEoa)
        loadMask.read(S);
    else
        loadMask.setAlways();
    classType = pdUnifiedTypeMap::PlasmaToMapped(S->readShort(), S->getVer());
    if (S->getVer() == pvEoa || S->getVer() == pvLive)
        objID = S->readInt();
    if (objName) free(objName);
    objName = S->readSafeStr();
    if ((contents & kHasCloneIDs) && S->getVer() != pvEoa) {
        cloneID = S->readInt();
        clonePlayerID = S->readInt();
    } else {
        cloneID = clonePlayerID = 0;
    }
    if ((contents & 0x06) && S->getVer() == pvEoa)
        eoaExtra = S->readByte();
    else eoaExtra = 0;
}

void plUoid::write(hsStream* S) {
    unsigned char contents = 0;
    if (cloneID != 0) contents |= kHasCloneIDs;
    if (loadMask.isUsed()) contents |= kHasLoadMask;
    if (eoaExtra != 0) contents |= 0x4;
    S->writeByte(contents);
    location.write(S);
    if ((contents & kHasLoadMask) && S->getVer() != pvEoa)
        loadMask.write(S);
    S->writeShort(pdUnifiedTypeMap::MappedToPlasma(classType, S->getVer()));
    if (S->getVer() == pvEoa || S->getVer() == pvLive)
        S->writeInt(objID);
    S->writeSafeStr(objName);
    if ((contents & kHasCloneIDs) && S->getVer() != pvEoa) {
        S->writeInt(cloneID);
        S->writeInt(clonePlayerID);
    }
    if ((contents & 0x06) && S->getVer() == pvEoa)
        S->writeByte(eoaExtra);
}

void plUoid::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plKey");
    prc->writeParam("Name", objName);
    prc->writeParam("Type", plFactory::ClassName(classType, prc->getStream()->getVer()));
    location.prcWrite(prc);
    if (loadMask.isUsed())
        loadMask.prcWrite(prc);
    if (cloneID != 0) {
        prc->writeParam("CloneID", cloneID);
        prc->writeParam("ClonePlayerID", clonePlayerID);
    }
    prc->endTag(true);
}

const char* plUoid::toString() {
    char* buf = (char*)malloc(256);
    sprintf(buf, "%s[%04X]%s", location.toString(), classType, objName);
    return buf;
}

short plUoid::getType() { return (short)classType; }
PageID& plUoid::getPageID() { return location.pageID; }
const char* plUoid::getName() { return objName; }
void plUoid::setID(unsigned int id) { objID = id; }
