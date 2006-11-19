#include "hsBitVector.h"
#include <string.h>

hsBitVector::hsBitVector() : bLen(0) {
    bits = new int[0];
}

hsBitVector::~hsBitVector() {
    delete bits;
}

bool hsBitVector::get(int idx) {
    if ((idx >> 5) < bLen)
        return (bits[idx >> 5] & (1 << (idx & BVMASK)));
    else return false;
}

void hsBitVector::set(int idx, bool b) {
    if ((idx >> 5) < bLen) {
        bLen = (idx >> 5) + 1;
        int* newBits = new int[bLen];
        memcpy(newBits, bits, sizeof(int)*bLen);
        delete bits;
        bits = newBits;
    }
    if (b) bits[idx >> 5] |=  (1 << (idx & BVMASK));
    else   bits[idx >> 5] &= ~(1 << (idx & BVMASK));
}

bool hsBitVector::isEmpty() {
    return (bLen == 0);
}

void hsBitVector::clear() {
    delete bits;
    bits = new int[0];
}

void hsBitVector::deleteBit(int idx) {
    int b = idx >> 5;
    idx &= BVMASK;
    int mask = (1 << idx) - 1;
    bits[b] = (bits[b] & mask) | ((bits[b] & ~mask) >> 1);
    for (int i = b+1; i<bLen; i++) {
        bits[i-1] |= bits[i] << BVMASK;
        bits[i] >>= 1;
    }
}

void hsBitVector::read(hsStream *S) {
    bLen = S->readInt();
    delete bits;
    bits = new int[bLen];
    for (int i=0; i<bLen; i++)
        bits[i] = S->readInt();
}

void hsBitVector::write(hsStream *S) {
    S->writeInt(bLen);
    for (int i=0; i<bLen; i++)
        S->writeInt(bits[i]);
}

