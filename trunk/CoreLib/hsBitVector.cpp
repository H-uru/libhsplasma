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
        if (fBits != NULL) {
            memcpy(newBits, fBits, sizeof(hsUint32)*fNumVectors);
            delete[] fBits;
        } else {
            memset(newBits, 0, sizeof(hsUint32)*fNumVectors);
        }
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

void hsBitVector::setBit(size_t idx) {
    set(idx, true);
}

void hsBitVector::clearBit(size_t idx) {
    set(idx, false);
}

void hsBitVector::compact() {
    size_t newNumVectors = fNumVectors;
    while (newNumVectors > 0 && fBits[newNumVectors-1] == 0)
        newNumVectors--;
    if (newNumVectors < fNumVectors) {
        if (newNumVectors == 0) {
            clear();
        } else {
            hsUint32* newBits = new hsUint32[newNumVectors];
            memcpy(newBits, fBits, sizeof(hsUint32)*newNumVectors);
            if (fBits) delete[] fBits;
            fBits = newBits;
            fNumVectors = newNumVectors;
        }
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
    compact();
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
