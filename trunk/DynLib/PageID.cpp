#include "PageID.h"
#include "../CoreLib/hsStream.h"

PageID::PageID(PlasmaVer pv) : seqPrefix(-1), pageID(-1), ver(pv) { }
PageID::~PageID() { }

PlasmaVer PageID::getVer() {
    return ver;
}

void PageID::setVer(PlasmaVer pv, bool mutate) {
    ver = pv;
}

bool PageID::operator==(PageID& other) {
    return (getPageNum() == other.getPageNum() &&
            getSeqPrefix() == other.getSeqPrefix());
}

PageID& PageID::operator=(const PageID& other) {
    pageID = other.pageID;
    seqPrefix = other.seqPrefix;
    ver = other.ver;
    return *this;
}

const char* PageID::toString() {
    char* str = new char[16];
    sprintf(str, "<%d|%d>", seqPrefix, pageID);
    return str;
}

void PageID::parse(unsigned int id) {
    seqPrefix = id >> (ver == pvLive ? 16 :  8);
    if (id & 0x80000000)
        seqPrefix = (seqPrefix & 0xFFFFFF00) | (~(seqPrefix & 0xFF) + 1);

    if (id & 0x80000000)
        pageID = (ver == pvLive) ? (id & 0xFFFF) - 1 : (id & 0xFF) - 1;
    else
        pageID = (ver == pvLive) ? (id & 0xFFFF) - 0x21 : (id & 0xFF) - 0x21;

    if (pageID < 0) seqPrefix--;
}

unsigned int PageID::unparse() {
    unsigned int id = pageID;
    if (ver == pvLive)
        id = (pageID + (seqPrefix < 0 ? 1 : 0x21)) & 0xFFFF;
    else
        id = (pageID + (seqPrefix < 0 ? 1 : 0x21)) & 0xFF;

    int sp = seqPrefix;
    if (sp < 0)
        sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF) + 1);
    sp &= (ver == pvLive) ? 0xFFFF : 0xFF;
    if (pageID < 0) sp++;
    sp <<= (ver == pvLive) ? 16 : 8;
    id |= sp;
    return id;
}

void PageID::read(hsStream *S) {
    int id = S->readInt();
    setVer(S->getVer());
    parse(id);
}

void PageID::write(hsStream *S) {
    if (S->getVer() != pvUnknown)
        setVer(S->getVer(), true);
    S->writeInt(unparse());
}

bool PageID::isGlobal() { return (seqPrefix < 0); }
int PageID::getPageNum() { return pageID; }
int PageID::getSeqPrefix() { return seqPrefix; }
void PageID::setPageNum(int pn) { pageID = pn; }
void PageID::setSeqPrefix(int sp) { seqPrefix = sp; }

void PageID::invalidate() { parse(0xFFFFFFFF); }
bool PageID::isValid() { return (unparse() != 0xFFFFFFFF); }

/* PageComparator */

bool PageComparator::operator()(PageID pid1, PageID pid2) const {
    if (pid1.getSeqPrefix() == pid2.getSeqPrefix())
        return (pid1.getPageNum() < pid2.getPageNum());
    return (pid1.getSeqPrefix() < pid2.getSeqPrefix());
}

