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

#include "plGBufferGroup.h"
#include "plGeometrySpan.h"
#include "plIcicle.h"
#include <cstring>
#include <string_theory/format>

/* plGBufferCell */
void plGBufferCell::read(hsStream* S)
{
    fVtxStart = S->readInt();
    fColorStart = S->readInt();
    fLength = S->readInt();
}

void plGBufferCell::write(hsStream* S)
{
    S->writeInt(fVtxStart);
    S->writeInt(fColorStart);
    S->writeInt(fLength);
}

void plGBufferCell::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plGBufferCell");
    prc->writeParam("VertexStart", fVtxStart);
    prc->writeParam("ColorStart", fColorStart);
    prc->writeParam("Length", fLength);
    prc->endTag(true);
}

void plGBufferCell::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plGBufferCell")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fVtxStart = tag->getParam("VertexStart", "0").to_uint();
    fColorStart = tag->getParam("ColorStart", "0").to_uint();
    fLength = tag->getParam("Length", "0").to_uint();
}


/* plGBufferTriangle */
void plGBufferTriangle::read(hsStream* S)
{
    fIndex1 = S->readShort();
    fIndex2 = S->readShort();
    fIndex3 = S->readShort();
    fSpanIndex = S->readShort();
    fCenter.read(S);
}

void plGBufferTriangle::write(hsStream* S)
{
    S->writeShort(fIndex1);
    S->writeShort(fIndex2);
    S->writeShort(fIndex3);
    S->writeShort(fSpanIndex);
    fCenter.write(S);
}

void plGBufferTriangle::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("plGBufferTriangle");
      prc->startTag("Indices");
      prc->writeParam("Index1", fIndex1);
      prc->writeParam("Index2", fIndex2);
      prc->writeParam("Index3", fIndex3);
      prc->writeParam("SpanIndex", fSpanIndex);
      prc->endTag(true);
      prc->writeSimpleTag("Center");
      fCenter.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}

void plGBufferTriangle::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plGBufferTriangle")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "Indices") {
            fIndex1 = child->getParam("Index1", "0").to_uint();
            fIndex2 = child->getParam("Index2", "0").to_uint();
            fIndex3 = child->getParam("Index3", "0").to_uint();
            fSpanIndex = child->getParam("SpanIndex", "0").to_uint();
        } else if (child->getName() == "Center") {
            if (child->hasChildren())
                fCenter.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}


/* plGBufferGroup */
plGBufferGroup::~plGBufferGroup()
{
    for (size_t i=0; i<fVertBuffStorage.size(); i++)
        delete[] fVertBuffStorage[i];
    for (size_t i=0; i<fIdxBuffStorage.size(); i++)
        delete[] fIdxBuffStorage[i];
    for (size_t i=0; i<fCompGBuffStorage.size(); i++)
        delete[] fCompGBuffStorage[i];
}

unsigned int plGBufferGroup::ICalcVertexSize(unsigned int& lStride)
{
    lStride = (getNumUVs() + 2) * 12;
    unsigned int numSkinWeights = getSkinWeights();
    if (numSkinWeights > 0) {
        lStride += numSkinWeights * sizeof(float);
        if (fFormat & kSkinIndices)
            lStride += sizeof(int);
    }
    return lStride + 8;
}

bool plGBufferGroup::INeedVertRecompression(PlasmaVer ver) const
{
    if ((fGBuffStorageType & kStoreIsDirty) != 0)
        return true;
    if (ver.isHexIsle())
        return (fGBuffStorageType & kStoreCompTypeMask) != kStoreCompV3;
    else if (ver.isLive())
        return (fGBuffStorageType & kStoreCompTypeMask) != kStoreCompV2;
    else
        return (fGBuffStorageType & kStoreCompTypeMask) != kStoreCompV1;
}

void plGBufferGroup::read(hsStream* S)
{
    if (S->getVer().isHexIsle()) {
        fFormat = S->readInt();
        S->readByte();
        S->readByte();
        S->readBool();
        S->readBool();
        S->readInt();
        S->readByte();
        // Don't know what the format parameters are, so better to just crash
        throw hsNotImplementedException(__FILE__, __LINE__, "HexIsle GBufferGroup");
    } else {
        fFormat = S->readByte();
        S->readInt();
        fStride = ICalcVertexSize(fLiteStride);
    }

    clearVertices();
    clearIndices();
    clearCells();

    if (!S->getVer().isUniversal() && (fFormat & kEncoded) != 0) {
        if (S->getVer().isHexIsle())
            fGBuffStorageType = kStoreCompV3;
        else if (S->getVer().isLive())
            fGBuffStorageType = kStoreCompV2;
        else
            fGBuffStorageType = kStoreCompV1;
    } else {
        fGBuffStorageType = kStoreUncompressed;
    }

    plVertCoder coder;
    size_t count = S->readInt();
    fVertBuffSizes.resize(count);
    fVertBuffStorage.resize(count);
    fCompGBuffSizes.resize(count);
    fCompGBuffStorage.resize(count);
    for (size_t i=0; i<count; i++) {
        unsigned char* vData;
        unsigned int vtxCount = 0, vtxSize = 0;
        if (fFormat & kEncoded) {
            vtxCount = S->readShort();
            vtxSize = vtxCount * fStride;
            fVertBuffSizes[i] = vtxSize;
            vData = new unsigned char[vtxSize];
            fVertBuffStorage[i] = vData;
            uint32_t compStart = S->pos();
            coder.read(S, vData, fFormat, vtxCount);

            // Store the compressed buffer too, so we don't have to
            // recompress anything later
            size_t compSize = S->pos() - compStart;
            fCompGBuffSizes[i] = compSize;
            fCompGBuffStorage[i] = new unsigned char[compSize];
            S->seek(compStart);
            S->read(compSize, fCompGBuffStorage[i]);
        } else {
            vtxSize = S->readInt();
            fVertBuffSizes[i] = vtxSize;
            vData = new unsigned char[vtxSize];
            S->read(vtxSize, vData);
            fVertBuffStorage[i] = vData;
            uint32_t colourcount = S->readInt();
            if (colourcount > 0) {
                unsigned char* cData = new unsigned char[colourcount*8];
                S->read(colourcount * 8, cData);
            }
            fCompGBuffSizes[i] = 0;
            fCompGBuffStorage[i] = nullptr;
        }
    }

    count = S->readInt();
    fIdxBuffCounts.resize(count);
    fIdxBuffStorage.resize(count);
    for (size_t i=0; i<count; i++) {
        unsigned int idxCount = S->readInt();
        fIdxBuffCounts[i] = idxCount;
        unsigned short* iData = new unsigned short[idxCount];
        S->readShorts(idxCount, iData);
        fIdxBuffStorage[i] = iData;
    }

    fCells.resize(fVertBuffStorage.size());
    for (size_t i=0; i<fVertBuffStorage.size(); i++) {
        size_t cellCount = S->readInt();
        fCells[i].resize(cellCount);
        for (size_t j=0; j<cellCount; j++)
            fCells[i][j].read(S);
    }
}

void plGBufferGroup::write(hsStream* S)
{
    fFormat |= kEncoded;
    unsigned int totalSize = 0;
    for (size_t i=0; i<fVertBuffSizes.size(); i++)
        totalSize += fVertBuffSizes[i];
    for (size_t i=0; i<fIdxBuffCounts.size(); i++)
        totalSize += fIdxBuffCounts[i] * sizeof(short);
    S->writeByte(fFormat);
    S->writeInt(totalSize);

    plVertCoder coder;
    S->writeInt(fVertBuffStorage.size());
    for (size_t i=0; i<fVertBuffStorage.size(); i++) {
        unsigned int count = fVertBuffSizes[i] / fStride;
        S->writeShort(count);
        if (S->getVer().isUniversal()) {
            S->writeInt(fVertBuffSizes[i]);
            S->write(fVertBuffSizes[i], fVertBuffStorage[i]);
        } else if (INeedVertRecompression(S->getVer()) || fCompGBuffStorage[i] == nullptr) {
            coder.write(S, fVertBuffStorage[i], fFormat, fStride, count);
        } else {
            S->write(fCompGBuffSizes[i], fCompGBuffStorage[i]);
        }
    }

    S->writeInt(fIdxBuffStorage.size());
    for (size_t i=0; i<fIdxBuffCounts.size(); i++) {
        S->writeInt(fIdxBuffCounts[i]);
        S->writeShorts(fIdxBuffCounts[i], fIdxBuffStorage[i]);
    }

    for (size_t i=0; i<fVertBuffStorage.size(); i++) {
        S->writeInt(fCells[i].size());
        for (size_t j=0; j<fCells[i].size(); j++)
            fCells[i][j].write(S);
    }
}

void plGBufferGroup::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plGBufferGroup");
    prc->writeParamHex("Format", fFormat);
    prc->endTag();

    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        for (size_t grp=0; grp<fVertBuffStorage.size(); grp++) {
            prc->writeSimpleTag("VertexGroup");
            std::vector<plGBufferVertex> verts = getVertices(grp);
            for (size_t i=0; i<verts.size(); i++) {
                prc->writeSimpleTag("Vertex");

                prc->writeSimpleTag("Position");
                verts[i].fPos.prcWrite(prc);
                prc->closeTag();

                prc->startTag("SkinWeights");
                if (fFormat & kSkinIndices)
                    prc->writeParam("SkinIndex", verts[i].fSkinIdx);
                prc->endTagNoBreak();
                for (size_t j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                    prc->directWrite(ST::format("{} ", verts[i].fSkinWeights[j]));
                prc->closeTagNoBreak();

                prc->writeSimpleTag("Normal");
                verts[i].fNormal.prcWrite(prc);
                prc->closeTag();
                prc->startTag("Color");
                prc->writeParamHex("value", verts[i].fColor);
                prc->endTag(true);

                prc->writeSimpleTag("UVWMaps");
                for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++)
                    verts[i].fUVWs[j].prcWrite(prc);
                prc->closeTag();

                prc->closeTag();  // Vertex
            }
            prc->closeTag();  // VertexGroup
        }

        for (size_t i=0; i<fIdxBuffStorage.size(); i++) {
            prc->writeSimpleTag("IndexGroup");
            for (size_t j=0; j<fIdxBuffCounts[i]; j += 3) {
                prc->writeTagNoBreak("Triangle");
                prc->directWrite(ST::format("{} {} {}",
                                 fIdxBuffStorage[i][j],
                                 fIdxBuffStorage[i][j+1],
                                 fIdxBuffStorage[i][j+2]));
                prc->closeTagNoBreak();
            }
            prc->closeTag();
        }
        for (size_t i=0; i<fVertBuffStorage.size(); i++) {
            prc->writeSimpleTag("CellGroup");
            for (size_t j=0; j<fCells[i].size(); j++)
                fCells[i][j].prcWrite(prc);
            prc->closeTag();
        }
    } else {
        prc->writeComment("Vertex data excluded");
    }
    prc->closeTag(); // plGBufferGroup
}

void plGBufferGroup::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plGBufferGroup")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFormat = tag->getParam("Format", "0").to_uint();
    fStride = ICalcVertexSize(fLiteStride);

    clearVertices();
    clearIndices();
    clearCells();

    fGBuffStorageType = kStoreUncompressed;

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "VertexGroup") {
            std::vector<plGBufferVertex> buf;
            buf.resize(child->countChildren());
            const pfPrcTag* vtxChild = child->getFirstChild();
            for (size_t i=0; i<buf.size(); i++) {
                if (vtxChild->getName() != "Vertex")
                    throw pfPrcTagException(__FILE__, __LINE__, vtxChild->getName());

                const pfPrcTag* subChild = vtxChild->getFirstChild();
                while (subChild) {
                    if (subChild->getName() == "Position") {
                        if (subChild->hasChildren())
                            buf[i].fPos.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "SkinWeights") {
                        buf[i].fSkinIdx = subChild->getParam("SkinIndex", "0").to_int();
                        std::list<ST::string> wgtList = subChild->getContents();
                        if (wgtList.size() != (size_t)((fFormat & kSkinWeightMask) >> 4))
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of Skin Weights");
                        auto wgt = wgtList.begin();
                        for (size_t j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                            buf[i].fSkinWeights[j] = (*wgt++).to_float();
                    } else if (subChild->getName() == "Normal") {
                        if (subChild->hasChildren())
                            buf[i].fNormal.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "Color") {
                        buf[i].fColor = subChild->getParam("value", "0").to_uint();
                    } else if (subChild->getName() == "UVWMaps") {
                        if ((fFormat & kUVCountMask) != subChild->countChildren())
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of UVW maps");
                        const pfPrcTag* uvwChild = subChild->getFirstChild();
                        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
                            buf[i].fUVWs[j].prcParse(uvwChild);
                            uvwChild = uvwChild->getNextSibling();
                        }
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                    }
                    subChild = subChild->getNextSibling();
                }
                vtxChild = vtxChild->getNextSibling();
            }
            addVertices(buf);
        } else if (child->getName() == "IndexGroup") {
            size_t idxCount = child->countChildren() * 3;
            fIdxBuffCounts.push_back(idxCount);
            unsigned short* idxBuff = new unsigned short[idxCount];
            fIdxBuffStorage.push_back(idxBuff);
            const pfPrcTag* idxChild = child->getFirstChild();
            for (size_t i=0; i<idxCount; i += 3) {
                if (idxChild->getName() != "Triangle")
                    throw pfPrcTagException(__FILE__, __LINE__, idxChild->getName());
                std::list<ST::string> idxList = idxChild->getContents();
                if (idxList.size() != 3)
                    throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                auto idx_iter = idxList.begin();
                idxBuff[i] = (*idx_iter++).to_uint();
                idxBuff[i+1] = (*idx_iter++).to_uint();
                idxBuff[i+2] = (*idx_iter++).to_uint();
                idxChild = idxChild->getNextSibling();
            }
        } else if (child->getName() == "CellGroup") {
            fCells.push_back(std::vector<plGBufferCell>());
            size_t idx = fCells.size() - 1;
            fCells[idx].resize(child->countChildren());
            const pfPrcTag* cellChild = child->getFirstChild();
            for (size_t i=0; i<fCells[idx].size(); i++) {
                fCells[idx][i].prcParse(cellChild);
                cellChild = cellChild->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

std::vector<plGBufferVertex> plGBufferGroup::getVertices(size_t idx, size_t start, size_t count) const
{
    std::vector<plGBufferVertex> buf;

    unsigned char* cp = fVertBuffStorage[idx] + (fStride * start);
    if (count == (size_t)-1)
        count = (fVertBuffSizes[idx] / fStride) - start;
    buf.resize(count);
    for (size_t i=0; i<count; i++) {
        buf[i].fPos.X = *(float*)cp; cp += sizeof(float);
        buf[i].fPos.Y = *(float*)cp; cp += sizeof(float);
        buf[i].fPos.Z = *(float*)cp; cp += sizeof(float);

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        if (weightCount > 0) {
            for (int j=0; j<weightCount; j++) {
                buf[i].fSkinWeights[j] = *(float*)cp;
                cp += sizeof(float);
            }
            if (fFormat & kSkinIndices) {
                buf[i].fSkinIdx = *(int*)cp;
                cp += sizeof(int);
            }
        }

        buf[i].fNormal.X = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.Y = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.Z = *(float*)cp; cp += sizeof(float);

        buf[i].fColor = *(unsigned int*)cp;
        cp += sizeof(unsigned int);

        // Zero (Color2?)
        cp += sizeof(unsigned int);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            buf[i].fUVWs[j].X = *(float*)cp; cp += sizeof(float);
            buf[i].fUVWs[j].Y = *(float*)cp; cp += sizeof(float);
            buf[i].fUVWs[j].Z = *(float*)cp; cp += sizeof(float);
        }
    }
    return buf;
}

std::vector<unsigned short> plGBufferGroup::getIndices(size_t idx, size_t start,
                                                       size_t count, size_t offset) const
{
    std::vector<unsigned short> buf;

    if (count == (size_t)-1)
        count = fIdxBuffCounts[idx] - start;
    buf.resize(count);
    for (size_t i=0; i<count; i++)
        buf[i] = fIdxBuffStorage[idx][i + start] - offset;
    return buf;
}

unsigned int plGBufferGroup::getNumVertices(size_t cell) const
{
    if (fCells.size() <= cell)
        return 0;

    unsigned int count = 0;
    for (const auto& i : fCells[cell])
        count += i.fLength;
    return count;
}

void plGBufferGroup::addVertices(const std::vector<plGBufferVertex>& verts)
{
    size_t vtxSize = verts.size() * fStride;
    fVertBuffSizes.push_back(vtxSize);
    fVertBuffStorage.push_back(new unsigned char[vtxSize]);
    fCompGBuffSizes.push_back(0);
    fCompGBuffStorage.push_back(nullptr);
    size_t idx = fVertBuffStorage.size() - 1;

    unsigned char* cp = fVertBuffStorage[idx];
    for (size_t i=0; i<(fVertBuffSizes[idx] / fStride); i++) {
        *(float*)cp = verts[i].fPos.X; cp += sizeof(float);
        *(float*)cp = verts[i].fPos.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fPos.Z; cp += sizeof(float);

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        if (weightCount > 0) {
            for (int j=0; j<weightCount; j++) {
                *(float*)cp = verts[i].fSkinWeights[j];
                cp += sizeof(float);
            }
            if (fFormat & kSkinIndices) {
                *(int*)cp = verts[i].fSkinIdx;
                cp += sizeof(int);
            }
        }

        *(float*)cp = verts[i].fNormal.X; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Z; cp += sizeof(float);

        *(unsigned int*)cp = verts[i].fColor;
        cp += sizeof(unsigned int);

        // Zero (Color2?)
        *(unsigned int*)cp = 0;
        cp += sizeof(unsigned int);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            *(float*)cp = verts[i].fUVWs[j].X; cp += sizeof(float);
            *(float*)cp = verts[i].fUVWs[j].Y; cp += sizeof(float);
            *(float*)cp = verts[i].fUVWs[j].Z; cp += sizeof(float);
        }
    }
}

void plGBufferGroup::addIndices(const std::vector<unsigned short>& indices)
{
    fIdxBuffCounts.push_back(indices.size());
    fIdxBuffStorage.push_back(new unsigned short[indices.size()]);
    size_t idx = fIdxBuffStorage.size() - 1;

    for (size_t i=0; i<fIdxBuffCounts[idx]; i++)
        fIdxBuffStorage[idx][i] = indices[i];
}

void plGBufferGroup::IPackIcicle(const plGeometrySpan* geoSpan, plIcicle* ice)
{
    size_t i;
    for (i = 0; i < fIdxBuffStorage.size(); ++i) {
        if (geoSpan->getNumIndices() + fIdxBuffCounts[i] < kMaxIndicesPerBuffer)
            break;
    }
    if (i == fIdxBuffStorage.size()) {
        fIdxBuffStorage.push_back(nullptr);
        fIdxBuffCounts.push_back(0);
    }

    unsigned int idxOffset = fIdxBuffCounts[i];
    unsigned short* idxStorage = new unsigned short[idxOffset + geoSpan->getNumIndices()];
    if (idxOffset != 0)
        memcpy(idxStorage, fIdxBuffStorage[i], idxOffset * sizeof(unsigned short));
    fIdxBuffCounts[i] += geoSpan->getNumIndices();
    delete fIdxBuffStorage[i];
    fIdxBuffStorage[i] = idxStorage;

    for (size_t j = 0; j < geoSpan->getNumIndices(); ++j)
        idxStorage[idxOffset + j] = geoSpan->getIndex(j) + (unsigned short)ice->getVStartIdx();

    ice->setIBufferIdx(i);
    ice->setIStartIdx(idxOffset);
    ice->setILength(geoSpan->getNumIndices());
}

void plGBufferGroup::IPackVertexSpan(const plGeometrySpan* geoSpan, plVertexSpan* vSpan)
{
    size_t i;
    for (i = 0; i < fVertBuffStorage.size(); ++i) {
        if (geoSpan->getNumVertices() + getNumVertices(i) < kMaxVertsPerBuffer)
            break;
    }
    if (i == fVertBuffStorage.size()) {
        fVertBuffStorage.push_back(nullptr);
        fVertBuffSizes.push_back(0);
        fCompGBuffStorage.push_back(nullptr);
        fCompGBuffSizes.push_back(0);
        fCells.emplace_back();
    }

    unsigned int vertOffset = fVertBuffSizes[i];
    unsigned int vertBuffSize = vertOffset + (geoSpan->getNumVertices() * fStride);
    unsigned char* vertStorage = new unsigned char[vertBuffSize];
    if (vertOffset != 0)
        memcpy(vertStorage, fVertBuffStorage[i], vertOffset);
    fVertBuffSizes[i] = vertBuffSize;
    delete fVertBuffStorage[i];
    fVertBuffStorage[i] = vertStorage;

    unsigned char* destp = (unsigned char*)(vertStorage + vertOffset);
    for (const auto& vertex : geoSpan->getVertices()) {
        static_assert(sizeof(vertex.fPosition) == sizeof(float) * 3, "vertex position unexpected size");
        memcpy(destp, &vertex.fPosition, sizeof(vertex.fPosition));
        destp += sizeof(vertex.fPosition);

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        if (weightCount > 0) {
            memcpy(destp, vertex.fWeights, weightCount * sizeof(float));
            destp += weightCount * sizeof(float);

            if (fFormat & kSkinIndices) {
                memcpy(destp, &vertex.fIndices, sizeof(uint32_t));
                destp += sizeof(uint32_t);
            }
        }

        static_assert(sizeof(vertex.fNormal) == sizeof(float) * 3, "vertex normal unexpected size");
        memcpy(destp, &vertex.fNormal, sizeof(vertex.fNormal));
        destp += sizeof(vertex.fNormal);

        memcpy(destp, &vertex.fColor, sizeof(uint32_t));
        destp += sizeof(uint32_t);
        memcpy(destp, &vertex.fSpecularColor, sizeof(uint32_t));
        destp += sizeof(uint32_t);

        static_assert(sizeof(vertex.fUVs[0]) == sizeof(float) * 3, "vertex uv unexpected size");
        size_t uvCount = fFormat & kUVCountMask;
        memcpy(destp, vertex.fUVs, sizeof(vertex.fUVs[0]) * uvCount);
        destp += sizeof(vertex.fUVs[0]) * uvCount;
    }

    std::vector<plGBufferCell>& cells = fCells[i];
    if (cells.empty()) {
        vSpan->setCellIdx(0);
        vSpan->setCellOffset(0);
        cells.emplace_back(vertOffset, -1, geoSpan->getNumVertices());
    } else {
        vSpan->setCellIdx(cells.size() - 1);
        vSpan->setCellOffset(cells.back().fLength);
        cells.back().fLength += geoSpan->getNumVertices();
    }

    vSpan->setVBufferIdx(i);
    for (size_t j = 0; j < cells.size() - 1; ++j)
        vSpan->setVStartIdx(vSpan->getVStartIdx() + cells[j].fLength);
    vSpan->setVStartIdx(vSpan->getVStartIdx() + vSpan->getCellOffset());
    vSpan->setVLength(geoSpan->getNumVertices());
}

void plGBufferGroup::packGeoSpan(const plGeometrySpan* geoSpan, plIcicle* ice)
{
    if (fFormat != geoSpan->getFormat())
        throw hsBadParamException(__FILE__, __LINE__, "Vertex formats do not match");

    // In Plasma-speak, this is the non-isolated interleaved format.
    IPackVertexSpan(geoSpan, ice);
    IPackIcicle(geoSpan, ice);
}

void plGBufferGroup::setFormat(unsigned int format)
{
    fFormat = format;
    fStride = ICalcVertexSize(fLiteStride);
    fGBuffStorageType |= kStoreIsDirty;
}

void plGBufferGroup::setSkinWeights(size_t skinWeights)
{
    fFormat &= ~kSkinWeightMask;
    fFormat |= (skinWeights << 4) & kSkinWeightMask;
    fGBuffStorageType |= kStoreIsDirty;
}

void plGBufferGroup::setNumUVs(size_t numUVs)
{
    fFormat &= ~kUVCountMask;
    fFormat |= numUVs & kUVCountMask;
    fGBuffStorageType |= kStoreIsDirty;
}

void plGBufferGroup::setHasSkinIndices(bool hasSI)
{
    if (hasSI)
        fFormat |= kSkinIndices;
    else
        fFormat &= ~kSkinIndices;
    fGBuffStorageType |= kStoreIsDirty;
}

void plGBufferGroup::delVertices(size_t idx)
{
    delete[] fVertBuffStorage[idx];
    delete[] fCompGBuffStorage[idx];
    fVertBuffStorage.erase(fVertBuffStorage.begin() + idx);
    fCompGBuffStorage.erase(fCompGBuffStorage.begin() + idx);
    fVertBuffSizes.erase(fVertBuffSizes.begin() + idx);
    fCompGBuffSizes.erase(fCompGBuffSizes.begin() + idx);
}

void plGBufferGroup::delIndices(size_t idx)
{
    delete[] fIdxBuffStorage[idx];
    fIdxBuffStorage.erase(fIdxBuffStorage.begin() + idx);
    fIdxBuffCounts.erase(fIdxBuffCounts.begin() + idx);
}

void plGBufferGroup::clearVertices()
{
    for (size_t i=0; i<fVertBuffStorage.size(); i++)
        delete[] fVertBuffStorage[i];
    for (size_t i=0; i<fCompGBuffStorage.size(); i++)
        delete[] fCompGBuffStorage[i];
    fVertBuffStorage.clear();
    fVertBuffSizes.clear();
    fCompGBuffStorage.clear();
    fCompGBuffSizes.clear();
}

void plGBufferGroup::clearIndices()
{
    for (size_t i=0; i<fIdxBuffStorage.size(); i++)
        delete[] fIdxBuffStorage[i];
    fIdxBuffStorage.clear();
    fIdxBuffCounts.clear();
}
