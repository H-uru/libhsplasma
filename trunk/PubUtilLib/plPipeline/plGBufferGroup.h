#ifndef _PLGBUFFERGROUP_H
#define _PLGBUFFERGROUP_H

#include "../../CoreLib/hsGeometry3.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsTList.hpp"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"
#include "hsGDeviceRef.h"
#include "plVertCoder.h"

class plGBufferCell {
public:
    unsigned int vtxStart, colorStart, length;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};


class plGBufferColor {
public:
    unsigned int diffuse, specular;
};


class plGBufferTriangle {
public:
    unsigned short index1, index2, index3, spanIndex;
    hsPoint3 center;

public:
    plGBufferTriangle();
    ~plGBufferTriangle();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};


struct plGBufferVertex {
    hsPoint3 fPos, fNormal;
    int fSkinIdx;
    float fSkinWeights[3];
    unsigned int fColor;
    hsPoint3 fUVWs[10];
};


class plGBufferGroup {
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
    unsigned char format, stride, liteStride, numSkinWeights;
    unsigned int numVerts, numIndices;
    bool vertsVolatile, idxVolatile;
    int LOD;
    hsTArray<hsGDeviceRef*> fVertexBufferRefs, fIndexBufferRefs;
    hsTArray<unsigned int> fVertBuffSizes, fIdxBuffCounts, fColorBuffCounts;
    hsTArray<unsigned char*> fVertBuffStorage;
    hsTArray<unsigned short*> fIdxBuffStorage;
    hsTArray<unsigned int> fVertBuffStarts;
    hsTArray<int> fVertBuffEnds;
    hsTArray<unsigned int> fIdxBuffStarts;
    hsTArray<int> fIdxBuffEnds;
    hsTArray<plGBufferColor*> fColorBuffStorage;
    hsTArray<hsTArray<plGBufferCell>*> fCells;

    unsigned char ICalcVertexSize(unsigned char& lStride);

public:
    plGBufferGroup(unsigned char fmt, bool vVol, bool iVol, int Lod);
    ~plGBufferGroup();

    hsTArray<plGBufferVertex> getVertices();
    hsTList<unsigned short> getIndices();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    plGBufferTriangle* ConvertToTriList(short spanIdx, unsigned int whichIdx,
           unsigned int whichVtx, unsigned int whichCell, unsigned int start,
           unsigned int numTris);
};

#endif
