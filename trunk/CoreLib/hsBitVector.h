#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "hsStream.h"
#include "hsTArray.hpp"
#include "FeatureLib/pfPRC/pfPrcHelper.h"
#include <map>

#define BVMASK 0x1F
#define BVMULT 0x20

DllClass hsBitVector {
public:
    DllClass Bit {
    protected:
        hsBitVector* fVector;
        size_t fOffset;

    public:
        Bit(hsBitVector* vec, size_t off);
        operator bool() const;
        bool operator!() const;
        bool operator==(bool value) const;
        Bit& operator=(bool value);
    };

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
    Bit operator[](size_t idx);

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
