#include "plLoadMask.h"

plLoadMask::plLoadMask() : fMask(0xFFFF) { }
plLoadMask::~plLoadMask() { }

void plLoadMask::read(hsStream* S) {
    unsigned char m = S->readByte();
    fQuality[0] = (m >> 4) | 0xF0;
    fQuality[1] = m | 0xF0;
}

void plLoadMask::write(hsStream* S) {
    unsigned char m = (fQuality[1] & 0x0F) | (fQuality[0] << 4);
    S->writeByte(m);
}

void plLoadMask::prcWrite(pfPrcHelper* prc) {
    prc->writeParamHex("LoadMask", fMask);
}

void plLoadMask::prcParse(const pfPrcTag* tag) {
    fMask = tag->getParam("LoadMask", "0xFFFF").toUint();
}

bool plLoadMask::isUsed() {
    return (fMask != 0xFFFF);
}

void plLoadMask::setQuality(unsigned char low, unsigned char high) {
    fQuality[0] = low;
    fQuality[1] = high;
}

void plLoadMask::setMask(unsigned short mask) {
    fMask = mask;
}

void plLoadMask::setAlways() {
    fMask = 0xFFFF;
}

unsigned short plLoadMask::getMask() const {
    return fMask;
}
