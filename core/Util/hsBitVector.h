#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "Util/hsTArray.hpp"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include <map>

#define BVMASK 0x1F
#define BVMULT 0x20

DllClass hsBitVector {
public:
    DllClass Bit {
    protected:
        hsBitVector* fVector;
        unsigned int fOffset;

    public:
        Bit(hsBitVector* vec, unsigned int off);
        operator bool() const;
        bool operator!() const;
        bool operator==(bool value) const;
        Bit& operator=(bool value);
    };

private:
    hsUint32* fBits;
    size_t fNumVectors;
    std::map<unsigned int, char*> fBitNames;

public:
    hsBitVector();
    hsBitVector(const hsBitVector& init);
    ~hsBitVector();

    bool get(unsigned int idx) const;
    void set(unsigned int idx, bool b);
    bool operator[](unsigned int idx) const;
    Bit operator[](unsigned int idx);
    hsBitVector& operator=(const hsBitVector& cpy);

    bool isEmpty() const;
    void clear();
    void setBit(unsigned int idx);
    void clearBit(unsigned int idx);
    void compact();

    const char* getName(unsigned int idx);
    unsigned int getValue(const char* name);
    void setName(unsigned int idx, const char* name);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
