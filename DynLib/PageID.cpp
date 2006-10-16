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
    if (mutate) {
        // Mutate the stored ID to match pv
        // Or it would if I decide to add this version mutating stuff ;)
    }
    ver = pv;
}

void PageID::read(hsStream *S) {
    id = S->readLong();
    ver = S->getVer();
}

void PageID::write(hsStream *S) {
    S->writeLong(id);
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
