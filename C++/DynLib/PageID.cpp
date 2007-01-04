#include "PageID.h"
#include "../CoreLib/hsStream.h"

PageID::PageID() : id(-1), ver(pvUnknown) { }
PageID::PageID(int pid, PlasmaVer pv) : id(pid), ver(pv) { }
PageID::~PageID() { }

int PageID::getID()         { return id; }
void PageID::setID(int pid) { id = pid;  }

PlasmaVer PageID::getVer() {
    return ver;
}

void PageID::setVer(PlasmaVer pv, bool mutate) {
    register int sp = getSeqPrefix();
    register int pn = getPageNum();
    ver = pv;
    if (mutate) {
        setPageNum(pn);
        setSeqPrefix(sp);
    }
}

bool PageID::operator==(PageID &other) {
    return (getPageNum() == other.getPageNum() &&
            getSeqPrefix() == other.getSeqPrefix());
}

void PageID::read(hsStream *S) {
    id = S->readInt();
    ver = S->getVer();
}

void PageID::write(hsStream *S) {
    if (S->getVer() != pvUnknown)
        this->setVer(S->getVer(), true);
    S->writeInt(id);
}

bool PageID::isGlobal() {
    return (id & 0x80000000);
}

int PageID::getPageNum() {
    if (isGlobal())
        return (ver == pvLive) ? (id & 0xFFFF) - 1 : (id & 0xFF) - 1;
    else
        return (ver == pvLive) ? (id & 0xFFFF) - 0x31 : (id & 0xFF) - 0x21;
}

int PageID::getSeqPrefix() {
    int sp = (ver == pvLive) ? (id >> 16) : (id >> 8);
    if (isGlobal())
        sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF)) + 1;
    if (getPageNum() < 0) sp--;
    return sp;
}

void PageID::setPageNum(int pn) {
    if (ver == pvLive)
        id = (id & 0xFFFF0000) | ((pn & 0xFFFF) + (isGlobal() ? 1 : 0x31));
    else
        id = (id & 0xFFFFFF00) | ((pn & 0xFF) + (isGlobal() ? 1 : 0x21));
}

void PageID::setSeqPrefix(int sp) {
    if (sp < 0)
        sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF)) + 1;
    if (getPageNum() < 0) sp++;
    sp <<= (ver == pvLive) ? 16 : 8;
    id &= (ver == pvLive) ? 0xFFFF : 0xFF;
    id |= sp;
}

