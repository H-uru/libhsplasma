#include "plLocation.h"

plLocation::plLocation(PlasmaVer pv)
          : fSeqPrefix(-1), fPageNum(-1), fVer(pv), fFlags(0) { }

plLocation::plLocation(const plLocation& init)
          : fSeqPrefix(init.fSeqPrefix), fPageNum(init.fPageNum),
            fVer(init.fVer), fFlags(init.fFlags) { }

plLocation::~plLocation() { }

PlasmaVer plLocation::getVer() const { return fVer; }
void plLocation::setVer(PlasmaVer pv) { fVer = pv; }

plLocation& plLocation::operator=(const plLocation& other) {
    fPageNum = other.fPageNum;
    fSeqPrefix = other.fSeqPrefix;
    fVer = other.fVer;
    fFlags = other.fFlags;
    return *this;
}

bool plLocation::operator==(const plLocation& other) const {
    return (fPageNum == other.fPageNum && fSeqPrefix == other.fSeqPrefix);
}

bool plLocation::operator<(const plLocation& other) const {
    if (fSeqPrefix == other.fSeqPrefix)
        return fPageNum < other.fPageNum;
    return fSeqPrefix < other.fSeqPrefix;
}

void plLocation::parse(unsigned int id) {
    if (id == 0xFFFFFFFF) {
        fPageNum = -1;
        fSeqPrefix = -1;
    } else {
        fPageNum = id & (fVer == pvLive ? 0x0000FFFF : 0x000000FF);
        if (id & 0x80000000) {
            id -= 1;
            fPageNum -= 1;
        } else {
            id -= 0x21;
            fPageNum -= 0x21;
        }
        fSeqPrefix = (signed int)id >> (fVer == pvLive ? 16 : 8);
        if (id & 0x80000000)
            fSeqPrefix = (fSeqPrefix & 0xFFFFFF00) | (0x100 - fSeqPrefix);
    }
}

unsigned int plLocation::unparse() const {
    if (fPageNum == -1 && fSeqPrefix == -1) {
        return 0xFFFFFFFF;
    } else {
        int sp = fSeqPrefix;
        if (sp < 0)
            sp = (sp & 0xFFFFFF00) | (0x100 - sp);
        if (fPageNum < 0)
            sp++;
        unsigned int id = sp << (fVer == pvLive ? 16 : 8);
        id += fPageNum + (fSeqPrefix < 0 ? 1 : 0x21);
        return id;
    }
}

void plLocation::read(hsStream* S) {
    setVer(S->getVer());
    parse(S->readInt());
    if (S->getVer() >= pvEoa)
        fFlags = S->readByte();
    else
        fFlags = S->readShort();
}

void plLocation::write(hsStream* S) {
    if (S->getVer() != pvUnknown)
        setVer(S->getVer());
    S->writeInt(unparse());
    if (S->getVer() >= pvEoa)
        S->writeByte(fFlags);
    else
        S->writeShort(fFlags);
}

void plLocation::prcWrite(pfPrcHelper* prc) {
    plString buf = plString::Format("%d;%d", fSeqPrefix, fPageNum);
    prc->writeParam("Location", buf);
    prc->writeParamHex("LocFlag", fFlags);
}

void plLocation::prcParse(const pfPrcTag* tag) {
    plString buf = tag->getParam("Location", "-1;-1");
    fSeqPrefix = buf.beforeFirst(';').toInt();
    fPageNum = buf.afterFirst(';').toInt();
    fFlags = tag->getParam("LocFlag", "0").toUint();
}

void plLocation::invalidate() {
    parse(0xFFFFFFFF);
    fFlags = 0;
}

bool plLocation::isValid() const { return (unparse() != 0xFFFFFFFF); }
bool plLocation::isReserved() const { return (fFlags & kReserved) != 0; }
bool plLocation::isItinerant() const { return (fFlags & kItinerant) != 0; }
bool plLocation::isVirtual() const { return unparse() == 0; }
bool plLocation::isGlobal() const { return (fSeqPrefix < 0); }

int plLocation::getPageNum() const { return fPageNum; }
int plLocation::getSeqPrefix() const { return fSeqPrefix; }
unsigned short plLocation::getFlags() const { return fFlags; }

void plLocation::setPageNum(int pn) { fPageNum = pn; }
void plLocation::setSeqPrefix(int sp) { fSeqPrefix = sp; }
void plLocation::setFlags(unsigned short flags) { fFlags = flags; }

void plLocation::set(int pid, unsigned short flags, PlasmaVer pv) {
    setVer(pv);
    parse(pid);
    fFlags = flags;
}

plString plLocation::toString() const {
    return plString::Format("<%d|%d>", fSeqPrefix, fPageNum);
}
