#include "hsBitVector.h"
#include <string.h>

hsBitVector::hsBitVector() : nVectors(0) {
    bits = new int[0];
}

hsBitVector::~hsBitVector() {
    delete bits;
}

bool hsBitVector::get(int idx) {
    if ((idx / 32) >= nVectors) return false;
    return (bits[idx / 32] & (1 << (idx & BVMASK))) != 0;
}

void hsBitVector::set(int idx, bool b) {
    if ((idx / 32) < nVectors) {
        nVectors = (idx / 32) + 1;
        int* newBits = new int[nVectors];
        memcpy(newBits, bits, sizeof(int)*nVectors);
        delete bits;
        bits = newBits;
    }
    if (b) bits[idx / 32] |=  (1 << (idx & BVMASK));
    else   bits[idx / 32] &= ~(1 << (idx & BVMASK));
}

bool hsBitVector::operator[](int idx) {
    return get(idx);
}

bool hsBitVector::isEmpty() {
    return (nVectors == 0);
}

void hsBitVector::clear() {
    delete bits;
    bits = new int[0];
    nVectors = 0;
}

void hsBitVector::deleteBit(int idx) {
    int b = idx >> 5;
    idx &= BVMASK;
    int mask = (1 << idx) - 1;
    bits[b] = (bits[b] & mask) | ((bits[b] & ~mask) >> 1);
    for (int i = b+1; i<nVectors; i++) {
        bits[i-1] |= bits[i] << BVMASK;
        bits[i] >>= 1;
    }
}

void hsBitVector::read(hsStream *S) {
    nVectors = S->readInt();
    delete bits;
    bits = new int[nVectors];
    for (int i=0; i<nVectors; i++)
        bits[i] = S->readInt();
}

void hsBitVector::write(hsStream *S) {
    S->writeInt(nVectors);
    for (int i=0; i<nVectors; i++)
        S->writeInt(bits[i]);
}

