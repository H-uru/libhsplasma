#ifndef _PLSPANINSTANCE_H
#define _PLSPANINSTANCE_H

#include "FeatureLib/pfPRC/pfPrcHelper.h"
#include "FeatureLib/pfPRC/pfPrcParser.h"

DllClass plSpanEncoding {
public:
    enum {
        kPosNone = 0,
        kPos888 = 0x1,
        kPos161616 = 0x2,
        kPos101010 = 0x4,
        kPos008 = 0x8,
        kPosMask = kPos888 | kPos161616 | kPos101010 | kPos008,

        kColNone = 0,
        kColA8 = 0x10,
        kColI8 = 0x20,
        kColAI88 = 0x40,
        kColRGB888 = 0x80,
        kColARGB8888 = 0x100,
        kColMask = kColA8 | kColI8 | kColAI88 | kColRGB888 | kColARGB8888
    };

protected:
    unsigned int fCode;
    float fPosScale;

public:
    plSpanEncoding();
    ~plSpanEncoding();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    unsigned int getCode() const;
    float getPosScale() const;
};

DllClass plSpanInstance {
protected:
    unsigned char* fPosDelta;
    unsigned char* fCol;
    float fL2W[3][4];   // OpenGL ordering

public:
    plSpanInstance();
    ~plSpanInstance();

    void read(hsStream* S, const plSpanEncoding& encoding, unsigned int numVerts);
    void write(hsStream* S, const plSpanEncoding& encoding, unsigned int numVerts);
    void prcWrite(pfPrcHelper* prc, const plSpanEncoding& encoding, unsigned int numVerts);
    void prcParse(const pfPrcTag* tag, const plSpanEncoding& encoding, unsigned int numVerts);

    static unsigned int CalcPosStride(const plSpanEncoding& encoding);
    static unsigned int CalcColStride(const plSpanEncoding& encoding);
};

#endif
