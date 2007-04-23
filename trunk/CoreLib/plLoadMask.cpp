#include "plLoadMask.h"

plLoadMask::plLoadMask() : mask(0xFFFF) { }
plLoadMask::~plLoadMask() { }

void plLoadMask::read(hsStream* S) {
    mask = S->readByte();
    quality[0] = (mask >> 4) | 0xF0;
    quality[1] = mask | 0xF0;
}

void plLoadMask::write(hsStream* S) {
    mask = (quality[1] & 0x0F) | (quality[0] << 4);
    S->writeByte(mask);
}

void plLoadMask::prcWrite(hsStream* S, pfPrcHelper* prc) {
    prc->writeParam("LoadMask", mask);
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
