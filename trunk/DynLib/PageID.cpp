#include "PageID.h"
#include "../CoreLib/hsStream.h"

PageID::PageID(PlasmaVer pv) : seqPrefix(-1), pageID(-1), ver(pv) { }
PageID::~PageID() { }

PlasmaVer PageID::getVer() const {
    return ver;
}

void PageID::setVer(PlasmaVer pv, bool mutate) {
    ver = pv;
}

bool PageID::operator==(PageID& other) const {
    return (getPageNum() == other.getPageNum() &&
            getSeqPrefix() == other.getSeqPrefix());
}

PageID& PageID::operator=(const PageID& other) {
    pageID = other.pageID;
    seqPrefix = other.seqPrefix;
    ver = other.ver;
    return *this;
}

char* PageID::toString() const {
    char* str = new char[16];
    sprintf(str, "<%d|%d>", seqPrefix, pageID);
    return str;
}

void PageID::parse(unsigned int id) {
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

unsigned int PageID::unparse() const {
    int sp = seqPrefix;
    if (sp < 0) 
        sp = (sp & 0xFFFFFF00) | (0x100 - sp);
    if (pageID < 0)
        sp++;
    unsigned int id = sp << (ver == pvLive ? 16 : 8);
    id += pageID + (seqPrefix < 0 ? 1 : 0x21);
    
    return id;
}

void PageID::read(hsStream* S) {
    int id = S->readInt();
    setVer(S->getVer());
    parse(id);
}

void PageID::write(hsStream* S) {
    if (S->getVer() != pvUnknown)
        setVer(S->getVer(), true);
    S->writeInt(unparse());
}

bool PageID::isGlobal() const { return (seqPrefix < 0); }
int PageID::getPageNum() const { return pageID; }
int PageID::getSeqPrefix() const { return seqPrefix; }
void PageID::setPageNum(int pn) { pageID = pn; }
void PageID::setSeqPrefix(int sp) { seqPrefix = sp; }

void PageID::invalidate() { parse(0xFFFFFFFF); }
bool PageID::isValid() const { return (unparse() != 0xFFFFFFFF); }

/* PageComparator */

bool PageComparator::operator()(PageID pid1, PageID pid2) const {
    if (pid1.getSeqPrefix() == pid2.getSeqPrefix())
        return (pid1.getPageNum() < pid2.getPageNum());
    return (pid1.getSeqPrefix() < pid2.getSeqPrefix());
}

