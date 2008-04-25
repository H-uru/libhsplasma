#ifndef _PLSPANTEMPLATE_H
#define _PLSPANTEMPLATE_H

#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsTArray.hpp"

DllClass plSpanTemplate {
public:
    enum {
        kPosMask = 0x1,
        kNormMask = 0x2,
        kColorMask = 0x4,
        kWgtIdxMask = 0x8,
        kUVWMask = 0xF0,
        kWeightMask = 0x300,
        kColor2Mask = 0x400
    };

    DllStruct Vertex {
        hsVector3 fPosition, fNormal;
        unsigned int fColor, fColor2;
        int fWeightIdx;
        hsVector3 fUVWs[10];
        float fWeights[3];
    };

protected:
    unsigned short fNumVerts, fNumTris, fFormat, fStride;
    unsigned char* fData;
    unsigned short* fIndices;

public:
    plSpanTemplate();
    ~plSpanTemplate();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    hsTArray<Vertex> getVertices() const;
    unsigned short getNumVerts() const;

    static unsigned short CalcStride(unsigned short format);
};

#endif
