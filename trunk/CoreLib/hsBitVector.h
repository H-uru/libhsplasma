#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "hsStream.h"
#include "hsTArray.hpp"
#include "FeatureLib/pfPRC/pfPrcHelper.h"
#include <map>

#define BVMASK 0x1F
#define BVMULT 0x20

DllClass hsBitVector {
private:
    hsUint32* fBits;
    size_t fNumVectors;
    std::map<size_t, const char*> fBitNames;

public:
    hsBitVector();
    ~hsBitVector();

    bool get(size_t idx) const;
    void set(size_t idx, bool b);
    bool operator[](size_t idx) const;

    bool isEmpty() const;
    void clear();
    void setBit(size_t idx);
    void clearBit(size_t idx);
    void compact();

    const char* getName(size_t idx);
    void setName(size_t idx, const char* name);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
