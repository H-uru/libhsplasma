#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "hsStream.h"

#define BVMASK  0x1F

class hsBitVector {
private:
    int* bits;
    int bLen;

public:
    hsBitVector();
    ~hsBitVector();

    bool get(int idx);
    void set(int idx, bool b);

    bool isEmpty();
    void clear();
    void deleteBit(int idx);

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

