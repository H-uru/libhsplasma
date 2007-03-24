#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "hsStream.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

#define BVMASK 0x1F
#define BVSHIFT 5

class hsBitVector {
private:
    int* bits;
    int nVectors;

public:
    hsBitVector();
    ~hsBitVector();

    bool get(int idx);
    void set(int idx, bool b);
    bool operator[](int idx);

    bool isEmpty();
    void clear();
    void deleteBit(int idx);

    void read(hsStream *S);
    void write(hsStream *S);
    void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

