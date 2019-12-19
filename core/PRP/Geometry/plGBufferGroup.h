/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLGBUFFERGROUP_H
#define _PLGBUFFERGROUP_H

#include "Math/hsGeometry3.h"
#include "plVertCoder.h"

class PLASMA_DLL plGBufferCell
{
public:
    unsigned int fVtxStart, fColorStart, fLength;

public:
    plGBufferCell() : fVtxStart(), fColorStart(), fLength() { }
    plGBufferCell(unsigned int vtxStart, unsigned int colorStart, unsigned int length)
        : fVtxStart(vtxStart), fColorStart(colorStart), fLength(length)
    { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


class PLASMA_DLL plGBufferTriangle
{
public:
    unsigned short fIndex1, fIndex2, fIndex3, fSpanIndex;
    hsVector3 fCenter;

public:
    plGBufferTriangle() : fIndex1(), fIndex2(), fIndex3(), fSpanIndex() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


class PLASMA_DLL plGBufferVertex
{
public:
    hsVector3 fPos, fNormal;
    int fSkinIdx;
    float fSkinWeights[3];
    unsigned int fColor;
    hsVector3 fUVWs[10];

public:
    plGBufferVertex() : fSkinIdx(), fSkinWeights(), fColor() { }
};


class PLASMA_DLL plGBufferGroup
{
public:
    enum Formats
    {
        kUVCountMask = 0xF,
        kSkinNoWeights = 0x0,
        kSkin1Weight = 0x10,
        kSkin2Weights = 0x20,
        kSkin3Weights = 0x30,
        kSkinWeightMask = 0x30,
        kSkinIndices = 0x40,
        kEncoded = 0x80
    };

    enum GeometryStorage
    {
        kStoreUncompressed = 0,
        kStoreCompV1 = 0x1,
        kStoreCompV2 = 0x2,
        kStoreCompV3 = 0x3,
        kStoreCompTypeMask = 0x3,
        kStoreIsDirty = 0x4
    };

    enum
    {
        kMaxVertsPerBuffer = 32000,
        kMaxIndicesPerBuffer = 32000,
    };

protected:
    unsigned int fFormat, fStride, fLiteStride, fGBuffStorageType;
    std::vector<unsigned int> fVertBuffSizes, fIdxBuffCounts, fCompGBuffSizes;
    std::vector<unsigned char*> fVertBuffStorage;
    std::vector<unsigned short*> fIdxBuffStorage;
    std::vector<std::vector<plGBufferCell> > fCells;
    std::vector<unsigned char*> fCompGBuffStorage;

    unsigned int ICalcVertexSize(unsigned int& lStride);
    bool INeedVertRecompression(PlasmaVer ver) const;

    void IPackVertexSpan(const class plGeometrySpan* geoSpan, class plVertexSpan* vSpan);
    void IPackIcicle(const class plGeometrySpan* geoSpan, class plIcicle* ice);

public:
    plGBufferGroup(unsigned char fmt) : fGBuffStorageType(kStoreUncompressed)
    {
        setFormat(fmt);
    }
    ~plGBufferGroup();

    plGBufferGroup(const plGBufferGroup&) = delete;
    plGBufferGroup& operator=(const plGBufferGroup&) = delete;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    std::vector<plGBufferVertex> getVertices(size_t idx, size_t start = 0, size_t count = (size_t)-1) const;
    std::vector<unsigned short> getIndices(size_t idx, size_t start = 0, size_t count = (size_t)-1, size_t offset = 0) const;
    std::vector<plGBufferCell> getCells(size_t idx) const { return fCells[idx]; }

    unsigned int getNumVertices(size_t cell = 0) const;

    unsigned int getFormat() const { return fFormat; }
    size_t getSkinWeights() const { return (fFormat & kSkinWeightMask) >> 4; }
    size_t getNumUVs() const { return (fFormat & kUVCountMask); }
    bool getHasSkinIndices() const { return (fFormat & kSkinIndices) != 0; }

    void addVertices(const std::vector<plGBufferVertex>& verts);
    void addIndices(const std::vector<unsigned short>& indices);
    void addCells(std::vector<plGBufferCell> cells) { fCells.emplace_back(std::move(cells)); }
    void packGeoSpan(const class plGeometrySpan* geoSpan, class plIcicle* ice);
    void setFormat(unsigned int format);
    void setSkinWeights(size_t skinWeights);
    void setNumUVs(size_t numUVs);
    void setHasSkinIndices(bool hasSI);

    void delVertices(size_t idx);
    void delIndices(size_t idx);
    void delCells(size_t idx) { fCells.erase(fCells.begin() + idx); }
    void clearVertices();
    void clearIndices();
    void clearCells() { fCells.clear(); }

    size_t getNumVertBuffers() const { return fVertBuffStorage.size(); }
    size_t getNumIdxBuffers() const { return fIdxBuffStorage.size(); }
    const unsigned char* getVertBufferStorage(size_t idx) const { return fVertBuffStorage[idx]; }
    const unsigned short* getIdxBufferStorage(size_t idx) const { return fIdxBuffStorage[idx]; }
    unsigned char* getMutableVertBuffer(size_t idx) { return fVertBuffStorage[idx]; }
    unsigned short* getMutableIdxBuffer(size_t idx) { return fIdxBuffStorage[idx]; }
    size_t getVertBufferSize(size_t idx) const { return fVertBuffSizes[idx]; }
    size_t getIdxBufferCount(size_t idx) const { return fIdxBuffCounts[idx]; }
    unsigned int getStride() const { return fStride; }
};

#endif
