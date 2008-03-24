#include "hsBitVector.h"
#include <cstring>

/* hsBitVector::Bit */
hsBitVector::Bit::Bit(hsBitVector* vec, size_t off)
           : fVector(vec), fOffset(off) { }

hsBitVector::Bit::operator bool() const { return fVector->get(fOffset); }
bool hsBitVector::Bit::operator!() const { return !fVector->get(fOffset); }

bool hsBitVector::Bit::operator==(bool value) const {
    return fVector->get(fOffset) == value;
}

hsBitVector::Bit& hsBitVector::Bit::operator=(bool value) {
    fVector->set(fOffset, value);
    return *this;
}


/* hsBiVector */
hsBitVector::hsBitVector() : fBits(NULL), fNumVectors(0) { }
hsBitVector::~hsBitVector() {
    if (fBits) delete[] fBits;
}

bool hsBitVector::get(size_t idx) const {
    if ((idx / BVMULT) >= fNumVectors) return false;
    return (fBits[idx / BVMULT] & (1 << (idx & BVMASK))) != 0;
}

void hsBitVector::set(size_t idx, bool b) {
    if ((idx / BVMULT) < fNumVectors + 1) {
        size_t oldNumVectors = fNumVectors;
        fNumVectors = (idx / BVMULT) + 1;
        hsUint32* newBits = new hsUint32[fNumVectors];
        if (fBits != NULL) {
            for (size_t i=0; i<oldNumVectors; i++)
                newBits[i] = fBits[i];
            delete[] fBits;
        } else {
            memset(newBits, 0, sizeof(hsUint32)*fNumVectors);
        }
        fBits = newBits;
    }
    if (b) fBits[idx / BVMULT] |=  (1 << (idx & BVMASK));
    else   fBits[idx / BVMULT] &= ~(1 << (idx & BVMASK));
}

bool hsBitVector::operator[](size_t idx) const {
    return get(idx);
}

hsBitVector::Bit hsBitVector::operator[](size_t idx) {
    return hsBitVector::Bit(this, idx);
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

const char* hsBitVector::getName(size_t idx) {
    static char tempName[11];
    if (fBitNames.count(idx) > 0) {
        return fBitNames[idx];
    } else {
        snprintf(tempName, 11, "%u", idx);
        return tempName;
    }
}

void hsBitVector::setName(size_t idx, const char* name) {
    fBitNames[idx] = name;
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
    for (size_t i=0; i<fNumVectors; i++) {
        for (size_t j=0; j<BVMULT; j++) {
            if (get((i*BVMULT) + j)) {
                prc->getStream()->writeStr(getName((i*BVMULT) + j));
                prc->getStream()->writeStr(" ");
            }
        }
    }
    prc->closeTagNoBreak();
}
