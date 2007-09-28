#include "hsBitVector.h"
#include <string.h>

hsBitVector::hsBitVector() : fBits(NULL), fNumVectors(0) { }
hsBitVector::~hsBitVector() {
    if (fBits) delete[] fBits;
}

bool hsBitVector::get(size_t idx) const {
    if ((idx >> BVSHIFT) >= fNumVectors) return false;
    return (fBits[idx >> BVSHIFT] & (1 << (idx & BVMASK))) != 0;
}

void hsBitVector::set(size_t idx, bool b) {
    if ((idx >> BVSHIFT) < fNumVectors) {
        fNumVectors = (idx >> BVSHIFT) + 1;
        hsUint32* newBits = new hsUint32[fNumVectors];
        memcpy(newBits, fBits, sizeof(hsUint32)*fNumVectors);
        if (fBits) delete[] fBits;
        fBits = newBits;
    }
    if (b) fBits[idx >> BVSHIFT] |=  (1 << (idx & BVMASK));
    else   fBits[idx >> BVSHIFT] &= ~(1 << (idx & BVMASK));
}

bool hsBitVector::operator[](size_t idx) const {
    return get(idx);
}

bool hsBitVector::isEmpty() const {
    return (fNumVectors == 0);
}

void hsBitVector::clear() {
    if (fBits) delete[] fBits;
    fBits = NULL;
    fNumVectors = 0;
}

void hsBitVector::deleteBit(size_t idx) {
    size_t b = idx >> BVSHIFT;
    idx &= BVMASK;
    size_t mask = (1 << idx) - 1;
    fBits[b] = (fBits[b] & mask) | ((fBits[b] & ~mask) >> 1);
    for (size_t i = b+1; i<fNumVectors; i++) {
        fBits[i-1] |= fBits[i] << BVMASK;
        fBits[i] >>= 1;
    }
}

void hsBitVector::read(hsStream* S) {
    fNumVectors = S->readInt();
    if (fBits) delete[] fBits;
    if (fNumVectors > 0)
        fBits = new hsUint32[fNumVectors];
    for (size_t i=0; i<fNumVectors; i++)
        fBits[i] = S->readInt();
}

void hsBitVector::write(hsStream* S) {
    S->writeInt(fNumVectors);
    for (size_t i=0; i<fNumVectors; i++)
        S->writeInt(fBits[i]);
}

void hsBitVector::prcWrite(pfPrcHelper* prc) {
    prc->writeTagNoBreak("hsBitVector");
    for (size_t i=1; i<=fNumVectors; i++) {
        char buf[9];
        sprintf(buf, "%08lX", fBits[fNumVectors - i]);
        prc->getStream()->writeStr(buf);
    }
    prc->closeTagNoBreak();
}
