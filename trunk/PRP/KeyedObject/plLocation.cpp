#include "plLocation.h"

/* PageID */
PageID::PageID(PlasmaVer pv) : seqPrefix(-1), pageID(-1), ver(pv) { }
PageID::~PageID() { }

PlasmaVer PageID::getVer() const { return ver; }
void PageID::setVer(PlasmaVer pv) { ver = pv; }

PageID& PageID::operator=(const PageID& other) {
    pageID = other.pageID;
    seqPrefix = other.seqPrefix;
    ver = other.ver;
    return *this;
}

bool PageID::operator==(const PageID& other) const {
    return (getPageNum() == other.getPageNum() &&
            getSeqPrefix() == other.getSeqPrefix());
}

bool PageID::operator<(const PageID& other) const {
    if (getSeqPrefix() == other.getSeqPrefix())
        return getPageNum() < other.getPageNum();
    return getSeqPrefix() < other.getSeqPrefix();
}

plString PageID::toString() const {
    return plString::Format("<%d|%d>", seqPrefix, pageID);
}

void PageID::parse(unsigned int id) {
    if (id == 0xFFFFFFFF) {
        pageID = -1;
        seqPrefix = -1;
    } else {
        pageID = id & (ver == pvLive ? 0x0000FFFF : 0x000000FF);
        if (id & 0x80000000) {
            id -= 1;
            pageID -= 1;
        } else {
            id -= 0x21;
            pageID -= 0x21;
        }
        seqPrefix = (signed int)id >> (ver == pvLive ? 16 : 8);
        if (id & 0x80000000)
            seqPrefix = (seqPrefix & 0xFFFFFF00) | (0x100 - seqPrefix);
    }
}

unsigned int PageID::unparse() const {
    if (pageID == -1 && seqPrefix == -1) {
        return 0xFFFFFFFF;
    } else {
        int sp = seqPrefix;
        if (sp < 0) 
            sp = (sp & 0xFFFFFF00) | (0x100 - sp);
        if (pageID < 0)
            sp++;
        unsigned int id = sp << (ver == pvLive ? 16 : 8);
        id += pageID + (seqPrefix < 0 ? 1 : 0x21);
        return id;
    }
}

void PageID::read(hsStream* S) {
    int id = S->readInt();
    setVer(S->getVer());
    parse(id);
}

void PageID::write(hsStream* S) {
    if (S->getVer() != pvUnknown)
        setVer(S->getVer());
    S->writeInt(unparse());
}

bool PageID::isGlobal() const { return (seqPrefix < 0); }
int PageID::getPageNum() const { return pageID; }
int PageID::getSeqPrefix() const { return seqPrefix; }
void PageID::setPageNum(int pn) { pageID = pn; }
void PageID::setSeqPrefix(int sp) { seqPrefix = sp; }

void PageID::invalidate() { parse(0xFFFFFFFF); }
bool PageID::isValid() const { return (unparse() != 0xFFFFFFFF); }


/* plLocation */
plLocation::plLocation() : pageID(), flags(0) { }
plLocation::~plLocation() { }

plLocation& plLocation::operator=(const plLocation& other) {
    pageID = other.pageID;
    flags = other.flags;
    return *this;
}

bool plLocation::operator==(const plLocation& other) const {
    return pageID == other.pageID;
}

bool plLocation::operator<(const plLocation& other) const {
    return pageID < other.pageID;
}

int plLocation::getPageNum() const { return pageID.getPageNum(); }
int plLocation::getSeqPrefix() const { return pageID.getSeqPrefix(); }

void plLocation::set(int pid, int lflags, PlasmaVer pv) {
    pageID.setVer(pv);
    pageID.parse(pid);
    flags = lflags;
}

void plLocation::read(hsStream* S) {
    pageID.read(S);
    if (S->getVer() >= pvEoa)
        flags = S->readByte();
    else
        flags = S->readShort();
}

void plLocation::write(hsStream* S) {
    pageID.write(S);
    if (S->getVer() >= pvEoa)
        S->writeByte(flags);
    else
        S->writeShort(flags);
}

void plLocation::prcWrite(pfPrcHelper* prc) {
    plString buf = plString::Format("%d;%d", pageID.getSeqPrefix(), pageID.getPageNum());
    prc->writeParam("Location", buf);
    prc->writeParamHex("LocFlag", flags);
}

void plLocation::prcParse(const pfPrcTag* tag) {
    plString buf = tag->getParam("Location", "-1;-1");
    pageID.setSeqPrefix(buf.beforeFirst(';').toInt());
    pageID.setPageNum(buf.afterFirst(';').toInt());
    flags = tag->getParam("LocFlags", "0").toUint();
}

void plLocation::invalidate() {
    pageID.invalidate();
    flags = 0;
}

bool plLocation::isValid() const { return pageID.isValid(); }
bool plLocation::isReserved() const { return (flags & kReserved) != 0; }
bool plLocation::isItinerant() const { return (flags & kItinerant) != 0; }
bool plLocation::isVirtual() const { return pageID.unparse() == 0; }
const PageID& plLocation::getPageID() const { return pageID; }
unsigned short plLocation::getFlags() const { return flags; }
plString plLocation::toString() const { return pageID.toString(); }
