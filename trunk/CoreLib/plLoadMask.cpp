#include "plLoadMask.h"

plLoadMask::plLoadMask() : mask(0xFFFF) { }
plLoadMask::~plLoadMask() { }

void plLoadMask::read(hsStream* S) {
    unsigned char m = S->readByte();
    quality[0] = (m >> 4) | 0xF0;
    quality[1] = m | 0xF0;
}

void plLoadMask::write(hsStream* S) {
    unsigned char m = (quality[1] & 0x0F) | (quality[0] << 4);
    S->writeByte(m);
}

void plLoadMask::prcWrite(pfPrcHelper* prc) {
    prc->writeParamHex("LoadMask", mask);
}

void plLoadMask::prcParse(const pfPrcTag* tag) {
    mask = tag->getParam("LoadMask", "0xFFFF").toUint();
}

bool plLoadMask::isUsed() {
    return (mask != 0xFFFF);
}

plLoadMask& plLoadMask::setMask(unsigned char m1, unsigned char m2) {
    quality[0] = m1;
    quality[1] = m2;
    return *this;
}

plLoadMask& plLoadMask::setAlways() {
    mask = 0xFFFF;
    return *this;
}
