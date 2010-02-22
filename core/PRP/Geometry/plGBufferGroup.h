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

    enum GeometryStorage {
        kStoreUncompressed = 0,
        kStoreCompV1 = 0x1,
        kStoreCompV2 = 0x2,
        kStoreCompV3 = 0x3,
        kStoreCompTypeMask = 0x3,
        kStoreIsDirty = 0x4
    };

protected:
    unsigned int fFormat, fStride, fLiteStride, fGBuffStorageType;
    hsTArray<unsigned int> fVertBuffSizes, fIdxBuffCounts, fCompGBuffSizes;
    hsTArray<unsigned char*> fVertBuffStorage;
    hsTArray<unsigned short*> fIdxBuffStorage;
    hsTArray<hsTArray<plGBufferCell> > fCells;
    hsTArray<unsigned char*> fCompGBuffStorage;

    unsigned int ICalcVertexSize(unsigned int& lStride);
    bool INeedVertRecompression(PlasmaVer ver) const;

public:
    plGBufferGroup(unsigned char fmt);
    ~plGBufferGroup();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    hsTArray<plGBufferVertex> getVertices(size_t idx, size_t start = 0, size_t count = (size_t)-1) const;
    hsTArray<unsigned short> getIndices(size_t idx, size_t start = 0, size_t count = (size_t)-1, size_t offset = 0) const;
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
    
    const unsigned char* getVertBufferStorage(size_t idx) const;
    const unsigned short* getIdxBufferStorage(size_t idx) const;
    unsigned char* getMutableVertBuffer(size_t idx);
    unsigned short* getMutableIdxBuffer(size_t idx);
    size_t getVertBufferSize(size_t idx) const;
    size_t getIdxBufferCount(size_t idx) const;
    unsigned int getStride() const;
};

#endif
