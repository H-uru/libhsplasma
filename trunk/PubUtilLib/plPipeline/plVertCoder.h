#ifndef _PLVERTCODER_H
#define _PLVERTCODER_H

#include "../../CoreLib/hsStream.h"

class plVertCoder {
public:
    enum { kPosition, kWeight, kUVW, kNumFloatFields = 10 };

    enum Formats {
        kUVCountMask = 0xF,
        kSkinNoWeights = 0x0,
        kSkin1Weight = 0x10,
        kSkin2Weights = 0x20,
        kSkin3Weights = 0x30,
        kSkinWeightMask = 0x30,
        kSkinIndices = 0x40,
        kEncoded = 0x80
    };

    static float FieldScales[kNumFloatFields];

private:
    struct FloatCode {
        float fOffset;
        bool fAllSame;
        unsigned short fCount;
    } fFloats[3][kNumFloatFields];

    struct ByteCode {
        unsigned short fCount;
        unsigned char fVal;
        bool fSame;
    } fColors[4];

    void IDecode(hsStream* S, unsigned char* dest, unsigned int stride,
                 unsigned char format);
    void IDecodeFloat(hsStream* S, int field, int chan, unsigned char* dest,
                      unsigned int stride);
    void IDecodeNormal(hsStream* S, unsigned char* dest, unsigned int stride);
    void IDecodeByte(hsStream* S, int chan, unsigned char* dest,
                     unsigned int stride);

public:
    plVertCoder();
    ~plVertCoder();

    void read(hsStream* S, unsigned char* dest, unsigned char format,
              unsigned int stride, unsigned short numVerts);
};

#endif

