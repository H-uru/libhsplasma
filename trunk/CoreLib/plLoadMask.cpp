#include "plLoadMask.h"

plLoadMask::plLoadMask() : mask(0xFFFF) { }
plLoadMask::~plLoadMask() { }

void plLoadMask::read(hsStream* S) {
    quality[0] = S->readByte();
    quality[1] = S->readByte();
}

void plLoadMask::write(hsStream* S) {
    S->writeByte(quality[0]);
    S->writeByte(quality[1]);
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

