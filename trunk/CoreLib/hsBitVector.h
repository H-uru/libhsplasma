#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "hsStream.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

#define BVMASK 0x1F
#define BVSHIFT 5

DllClass hsBitVector {
private:
    uint* fBits;
    size_t fNumVectors;

public:
    hsBitVector();
    ~hsBitVector();

    bool get(size_t idx) const;
    void set(size_t idx, bool b);
    bool operator[](size_t idx) const;

    bool isEmpty() const;
    void clear();
    void deleteBit(size_t idx);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
