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
    plGBufferCell();
    plGBufferCell(const plGBufferCell& init);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


DllClass plGBufferTriangle {
public:
    unsigned short fIndex1, fIndex2, fIndex3, fSpanIndex;
    hsVector3 fCenter;

public:
    plGBufferTriangle();
    plGBufferTriangle(const plGBufferTriangle& init);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


DllClass plGBufferVertex {
public:
    hsVector3 fPos, fNormal;
    int fSkinIdx;
    float fSkinWeights[3];
    unsigned int fColor;
    hsVector3 fUVWs[10];

public:
    plGBufferVertex();
    plGBufferVertex(const plGBufferVertex& init);
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

protected:
    unsigned char fFormat, fStride, fLiteStride;
    hsTArray<unsigned int> fVertBuffSizes, fIdxBuffCounts;
    hsTArray<unsigned char*> fVertBuffStorage;
    hsTArray<unsigned short*> fIdxBuffStorage;
    hsTArray<hsTArray<plGBufferCell> > fCells;

    unsigned char ICalcVertexSize(unsigned char& lStride);

public:
    plGBufferGroup(unsigned char fmt);
    ~plGBufferGroup();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    hsTArray<plGBufferVertex> getVertices(size_t idx) const;
    hsTArray<unsigned short> getIndices(size_t idx) const;
    hsTArray<plGBufferCell> getCells(size_t idx) const;
    unsigned char getFormat() const;
    size_t getSkinWeights() const;
    size_t getNumUVs() const;
    bool getHasSkinIndices() const;

    void addVertices(const hsTArray<plGBufferVertex>& verts);
    void addIndices(const hsTArray<unsigned short>& indices);
    void addCells(const hsTArray<plGBufferCell>& cells);
    void setFormat(unsigned char format);
    void setSkinWeights(size_t skinWeights);
    void setNumUVs(size_t numUVs);
    void setHasSkinIndices(bool hasSI);

    void delVertices(size_t idx);
    void delIndices(size_t idx);
    void delCells(size_t idx);
    void clearVertices();
    void clearIndices();
    void clearCells();
};

#endif
