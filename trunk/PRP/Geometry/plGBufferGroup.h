#ifndef _PLGBUFFERGROUP_H
#define _PLGBUFFERGROUP_H

#include "Math/hsGeometry3.h"
#include "Util/hsTArray.hpp"
#include "Util/hsTList.hpp"
#include "hsGDeviceRef.h"
#include "plVertCoder.h"

DllClass plGBufferCell {
public:
    unsigned int fVtxStart, fColorStart, fLength;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


DllClass plGBufferColor {
public:
    unsigned int fDiffuse, fSpecular;
};


DllClass plGBufferTriangle {
public:
    unsigned short fIndex1, fIndex2, fIndex3, fSpanIndex;
    hsVector3 fCenter;

public:
    plGBufferTriangle();
    ~plGBufferTriangle();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


DllStruct plGBufferVertex {
    hsVector3 fPos, fNormal;
    int fSkinIdx;
    float fSkinWeights[3];
    unsigned int fColor;
    hsVector3 fUVWs[10];
};


DllClass plGBufferGroup {
public:
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
    
    enum {
        kReserveInterleaved = 0x1,
        kReserveVerts = 0x2,
        kReserveColors = 0x4,
        kReserveSeparated = 0x8,
        kReserveIsolate = 0x10
    };

protected:
    unsigned char fFormat, fStride, fLiteStride, fNumSkinWeights;
    unsigned int fNumVerts, fNumIndices;
    bool fVertsVolatile, fIdxVolatile;
    int fLOD;
    hsTArray<unsigned int> fVertBuffSizes, fIdxBuffCounts;
    hsTArray<unsigned char*> fVertBuffStorage;
    hsTArray<unsigned short*> fIdxBuffStorage;
    hsTArray<unsigned int> fVertBuffStarts;
    hsTArray<int> fVertBuffEnds;
    hsTArray<unsigned int> fIdxBuffStarts;
    hsTArray<int> fIdxBuffEnds;
    hsTArray<hsTArray<plGBufferCell>*> fCells;

    unsigned char ICalcVertexSize(unsigned char& lStride);

public:
    plGBufferGroup(unsigned char fmt, bool vVol, bool iVol, int Lod);
    ~plGBufferGroup();

    hsTArray<plGBufferVertex> getVertices(size_t idx) const;
    hsTArray<unsigned short> getIndices(size_t idx) const;

    void addVertices(const hsTArray<plGBufferVertex>& verts);
    void addIndices(const hsTArray<unsigned short>& indices);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
