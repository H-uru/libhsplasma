#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "hsStream.h"
#include "hsTArray.hpp"
#include "FeatureLib/pfPRC/pfPrcHelper.h"
#include <map>

#define BVBTYPE hsUint32
#define BVMASK ((sizeof(BVBTYPE)<<3)-1)
#define BVMULT (sizeof(BVBTYPE)<<3)

DllClass hsBitVector {
public:
    DllClass Bit {
    protected:
        hsBitVector* fVector;
        BVBTYPE fOffset;

    public:
        Bit(hsBitVector* vec, BVBTYPE off);
        operator bool() const;
        bool operator!() const;
        bool operator==(bool value) const;
        Bit& operator=(bool value);
    };

private:
    hsUint32* fBits;
    hsUint32 fNumVectors;
    std::map<BVBTYPE, const char*> fBitNames;

public:
    hsBitVector();
    ~hsBitVector();

    bool get(BVBTYPE idx) const;
    void set(BVBTYPE idx, bool b);
    bool operator[](BVBTYPE idx) const;
    Bit operator[](BVBTYPE idx);

    bool isEmpty() const;
    void clear();
    void setBit(BVBTYPE idx);
    void clearBit(BVBTYPE idx);
    void compact();

    const char* getName(BVBTYPE idx);
    void setName(BVBTYPE idx, const char* name);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
