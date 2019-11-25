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

#include "plGeometrySpan.h"
#include "Debug/plDebug.h"

unsigned int plGeometrySpan::CalcVertexSize(unsigned char format)
{
    unsigned int size = ((format & kUVCountMask) + 2) * 12;
    size += ((format & kSkinWeightMask) >> 4) * sizeof(float);
    if (format & kSkinIndices)
        size += sizeof(int);
    return size;
}

void plGeometrySpan::read(hsStream* S)
{
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLocalBounds.read(S);
    fOBBToLocal.read(S);
    fLocalToOBB.read(S);

    fBaseMatrix = S->readInt();
    fNumMatrices = S->readByte();
    fLocalUVWChans = S->readShort();
    fMaxBoneIdx = S->readShort();
    fPenBoneIdx = S->readShort();
    fMinDist = S->readFloat();
    fMaxDist = S->readFloat();
    if (S->getVer().isHexIsle()) {
        fFormat = S->readInt();
        S->readByte();
        S->readByte();
        // Don't know what the format parameters are, so better to just crash
        throw hsNotImplementedException(__FILE__, __LINE__, "HexIsle GSpans");
    } else {
        fFormat = S->readByte();
    }
    fProps = S->readInt();
    fNumVerts = S->readInt();
    uint32_t numIndices = S->readInt();
    if (!S->getVer().isHexIsle()) {
        S->readInt();  // Discarded
        S->readByte(); // Discarded
    }
    fDecalLevel = S->readInt();

    if (fProps & kWaterHeight)
        fWaterHeight = S->readFloat();

    if (fNumVerts > 0) {
        unsigned int stride = CalcVertexSize(fFormat);
        fVertexData.resize(fNumVerts * stride);
        S->read(fNumVerts * stride, &fVertexData[0]);

        fMultColor.resize(fNumVerts);
        fAddColor.resize(fNumVerts);
        for (unsigned int i=0; i<fNumVerts; i++) {
            fMultColor[i].read(S);
            fAddColor[i].read(S);
        }
        fDiffuseRGBA.resize(fNumVerts);
        fSpecularRGBA.resize(fNumVerts);
        S->readInts(fNumVerts, (uint32_t*)&fDiffuseRGBA[0]);
        S->readInts(fNumVerts, (uint32_t*)&fSpecularRGBA[0]);
    } else {
        fVertexData.clear();
        fMultColor.clear();
        fAddColor.clear();
        fDiffuseRGBA.clear();
        fSpecularRGBA.clear();
    }

    if (numIndices > 0) {
        fIndexData.resize(numIndices);
        S->readShorts(numIndices, (uint16_t*)&fIndexData[0]);
    } else {
        fIndexData.clear();
    }

    fInstanceGroup = S->readInt();
    if (fInstanceGroup != 0) {
        plDebug::Warning("WARNING: plGeometrySpan::read Incomplete");
        numInstanceRefs = S->readInt();
    }
}

void plGeometrySpan::write(hsStream* S)
{
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    fLocalBounds.write(S);
    fOBBToLocal.write(S);
    fLocalToOBB.write(S);

    S->writeInt(fBaseMatrix);
    S->writeByte(fNumMatrices);
    S->writeShort(fLocalUVWChans);
    S->writeShort(fMaxBoneIdx);
    S->writeShort(fPenBoneIdx);
    S->writeFloat(fMinDist);
    S->writeFloat(fMaxDist);
    S->writeByte(fFormat);
    S->writeInt(fProps);
    S->writeInt(fNumVerts);
    S->writeInt(fIndexData.size());
    S->writeInt(0);
    S->writeByte(0);
    S->writeInt(fDecalLevel);

    if (fProps & kWaterHeight)
        S->writeFloat(fWaterHeight);

    if (fNumVerts > 0) {
        S->write(fNumVerts * CalcVertexSize(fFormat), &fVertexData[0]);
        for (unsigned int i=0; i<fNumVerts; i++) {
            fMultColor[i].write(S);
            fAddColor[i].write(S);
        }
        S->writeInts(fNumVerts, (uint32_t*)&fDiffuseRGBA[0]);
        S->writeInts(fNumVerts, (uint32_t*)&fSpecularRGBA[0]);

    }
    if (!fIndexData.empty())
        S->writeShorts(fIndexData.size(), (uint16_t*)&fIndexData[0]);

    S->writeInt(fInstanceGroup);
    if (fInstanceGroup != 0) {
        plDebug::Warning("WARNING: plGeometrySpan::write Incomplete");
        S->writeInt(numInstanceRefs);
    }
}

void plGeometrySpan::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plGeometrySpan");
    prc->writeParam("BaseMatrix", fBaseMatrix);
    prc->writeParam("NumMatrices", fNumMatrices);
    prc->writeParam("LocalUVWChans", fLocalUVWChans);
    prc->writeParam("MaxBoneIdx", fMaxBoneIdx);
    prc->writeParam("PenBoneIdx", fPenBoneIdx);
    prc->writeParam("MinDist", fMinDist);
    prc->writeParam("MaxDist", fMaxDist);
    prc->writeParamHex("Format", fFormat);
    prc->writeParamHex("Props", fProps);
    prc->writeParam("DecalLevel", fDecalLevel);
    if (fProps & kWaterHeight)
        prc->writeParam("WaterHeight", fWaterHeight);
    prc->endTag();

    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        std::vector<TempVertex> verts = getVertices();
        prc->writeSimpleTag("Vertices");
        for (size_t i=0; i<verts.size(); i++) {
            prc->writeSimpleTag("Vertex");

            prc->writeSimpleTag("Position");
            verts[i].fPosition.prcWrite(prc);
            prc->closeTag();

            prc->writeSimpleTag("Normal");
            verts[i].fNormal.prcWrite(prc);
            prc->closeTag();

            prc->writeSimpleTag("UVWMaps");
            for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++)
                verts[i].fUVs[j].prcWrite(prc);
            prc->closeTag();

            prc->startTag("Weights");
            if (fFormat & kSkinIndices)
                prc->writeParam("Index", verts[i].fIndices);
            prc->endTagNoBreak();
            for (size_t j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                prc->directWrite(ST::format("{f} ", verts[i].fWeights[j]));
            prc->closeTagNoBreak();

            prc->closeTag();    // Vertex
        }
        prc->closeTag();    // Vertices

        prc->writeSimpleTag("MultColors");
        for (size_t i=0; i<fNumVerts; i++)
            fMultColor[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("AddColors");
        for (size_t i=0; i<fNumVerts; i++)
            fAddColor[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("DiffuseColors");
        for (size_t i=0; i<fNumVerts; i++) {
            hsColor32 cl(fDiffuseRGBA[i]);
            cl.prcWrite(prc);
        }
        prc->closeTag();
        prc->writeSimpleTag("SpecularColors");
        for (size_t i=0; i<fNumVerts; i++) {
            hsColor32 cl(fSpecularRGBA[i]);
            cl.prcWrite(prc);
        }
        prc->closeTag();

        prc->writeSimpleTag("Triangles");
        for (size_t i=0; i<fIndexData.size(); i += 3) {
            prc->writeTagNoBreak("Triangle");
            prc->directWrite(ST::format("{} {} {}",
                             fIndexData[i], fIndexData[i+1], fIndexData[i+2]));
            prc->closeTagNoBreak();
        }
        prc->closeTag();

        prc->startTag("InstanceGroup");
        prc->writeParam("value", fInstanceGroup);
        if (fInstanceGroup != 0)
            prc->writeParam("NumRefs", numInstanceRefs);
        prc->endTag(true);
    } else {
        prc->writeComment("Vertex data excluded");
    }
    prc->closeTag();    // plGeometrySpan
}

void plGeometrySpan::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plGeometrySpan")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fBaseMatrix = tag->getParam("BaseMatrix", "0").to_uint();
    fNumMatrices = tag->getParam("NumMatrices", "0").to_uint();
    fLocalUVWChans = tag->getParam("LocalUVWChans", "0").to_uint();
    fMaxBoneIdx = tag->getParam("MaxBoneIdx", "0").to_uint();
    fPenBoneIdx = tag->getParam("PenBoneIdx", "0").to_uint();
    fMinDist = tag->getParam("MinDist", "0").to_float();
    fMaxDist = tag->getParam("MaxDist", "0").to_float();
    fFormat = tag->getParam("Format", "0").to_uint();
    fProps = tag->getParam("Props", "0").to_uint();
    fDecalLevel = tag->getParam("DecalLevel", "0").to_uint();
    fWaterHeight = tag->getParam("WaterHeight", "0").to_float();

    fVertexData.clear();
    fMultColor.clear();
    fAddColor.clear();
    fDiffuseRGBA.clear();
    fSpecularRGBA.clear();
    fIndexData.clear();

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "Vertices") {
            fNumVerts = child->countChildren();
            std::vector<TempVertex> verts(fNumVerts);
            const pfPrcTag* vertChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                if (vertChild->getName() != "Vertex")
                    throw pfPrcTagException(__FILE__, __LINE__, vertChild->getName());
                const pfPrcTag* subChild = vertChild->getFirstChild();
                while (subChild) {
                    if (subChild->getName() == "Position") {
                        if (subChild->hasChildren())
                            verts[i].fPosition.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "Normal") {
                        if (subChild->hasChildren())
                            verts[i].fNormal.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "UVWMaps") {
                        if (subChild->countChildren() != (size_t)(fFormat & kUVCountMask))
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of UV maps");
                        const pfPrcTag* uvChild = subChild->getFirstChild();
                        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
                            verts[i].fUVs[j].prcParse(uvChild);
                            uvChild = uvChild->getNextSibling();
                        }
                    } else if (subChild->getName() == "Weights") {
                        verts[i].fIndices = subChild->getParam("Index", "0").to_uint();
                        std::list<ST::string> wgtList = subChild->getContents();
                        if (wgtList.size() != (size_t)((fFormat & kSkinWeightMask) >> 4))
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of Weights");
                        auto wgt = wgtList.begin();
                        for (size_t j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                            verts[i].fWeights[j] = (*wgt++).to_float();
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                    }
                    subChild = subChild->getNextSibling();
                }
                vertChild = vertChild->getNextSibling();
            }
            setVertices(verts);
        } else if (child->getName() == "MultColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fMultColor.resize(fNumVerts);
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                fMultColor[i].prcParse(clrChild);
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "AddColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fAddColor.resize(fNumVerts);
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                fAddColor[i].prcParse(clrChild);
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "DiffuseColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fDiffuseRGBA.resize(fNumVerts);
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                hsColor32 cl;
                cl.prcParse(clrChild);
                fDiffuseRGBA[i] = cl.color;
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "SpecularColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fSpecularRGBA.resize(fNumVerts);
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                hsColor32 cl;
                cl.prcParse(clrChild);
                fSpecularRGBA[i] = cl.color;
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "Triangles") {
            size_t numIndices = child->countChildren() * 3;
            fIndexData.resize(numIndices);
            const pfPrcTag* triChild = child->getFirstChild();
            for (size_t i=0; i<numIndices; i += 3) {
                if (triChild->getName() != "Triangle")
                    throw pfPrcTagException(__FILE__, __LINE__, triChild->getName());
                std::list<ST::string> idxList = triChild->getContents();
                if (idxList.size() != 3)
                    throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                auto idx_iter = idxList.begin();
                fIndexData[i] = (*idx_iter++).to_uint();
                fIndexData[i+1] = (*idx_iter++).to_uint();
                fIndexData[i+2] = (*idx_iter++).to_uint();
                triChild = triChild->getNextSibling();
            }
        } else if (child->getName() == "InstanceGroup") {
            fInstanceGroup = child->getParam("value", "0").to_uint();
            numInstanceRefs = child->getParam("NumRefs", "0").to_uint();
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

std::vector<plGeometrySpan::TempVertex> plGeometrySpan::getVertices() const
{
    std::vector<TempVertex> buf(fNumVerts);

    const unsigned char* cp = &fVertexData[0];
    for (size_t i=0; i<fNumVerts; i++) {
        buf[i].fPosition.X = *(float*)cp; cp += sizeof(float);
        buf[i].fPosition.Y = *(float*)cp; cp += sizeof(float);
        buf[i].fPosition.Z = *(float*)cp; cp += sizeof(float);

        buf[i].fNormal.X = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.Y = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.Z = *(float*)cp; cp += sizeof(float);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            buf[i].fUVs[j].X = *(float*)cp; cp += sizeof(float);
            buf[i].fUVs[j].Y = *(float*)cp; cp += sizeof(float);
            buf[i].fUVs[j].Z = *(float*)cp; cp += sizeof(float);
        }

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        for (int j=0; j<weightCount; j++) {
            buf[i].fWeights[j] = *(float*)cp;
            cp += sizeof(float);
        }
        if (fFormat & kSkinIndices) {
            buf[i].fIndices = *(int*)cp;
            cp += sizeof(int);
        }
        buf[i].fColor = fDiffuseRGBA[i];
        buf[i].fSpecularColor = fSpecularRGBA[i];
        buf[i].fMultColor = fMultColor[i];
        buf[i].fAddColor = fAddColor[i];
    }
    return buf;
}

void plGeometrySpan::setVertices(const std::vector<TempVertex>& verts)
{
    fVertexData.clear();
    fDiffuseRGBA.clear();
    fSpecularRGBA.clear();
    fMultColor.clear();
    fAddColor.clear();

    unsigned int stride = CalcVertexSize(fFormat);
    fNumVerts = verts.size();
    fVertexData.resize(fNumVerts * stride);
    fDiffuseRGBA.resize(fNumVerts);
    fSpecularRGBA.resize(fNumVerts);
    fMultColor.resize(fNumVerts);
    fAddColor.resize(fNumVerts);

    unsigned char* cp = &fVertexData[0];
    for (size_t i=0; i<fNumVerts; i++) {
        *(float*)cp = verts[i].fPosition.X; cp += sizeof(float);
        *(float*)cp = verts[i].fPosition.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fPosition.Z; cp += sizeof(float);

        *(float*)cp = verts[i].fNormal.X; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Z; cp += sizeof(float);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            *(float*)cp = verts[i].fUVs[j].X; cp += sizeof(float);
            *(float*)cp = verts[i].fUVs[j].Y; cp += sizeof(float);
            *(float*)cp = verts[i].fUVs[j].Z; cp += sizeof(float);
        }

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        for (int j=0; j<weightCount; j++) {
            *(float*)cp = verts[i].fWeights[j];
            cp += sizeof(float);
        }
        if (fFormat & kSkinIndices) {
            *(int*)cp = verts[i].fIndices;
            cp += sizeof(int);
        }

        fDiffuseRGBA[i] = verts[i].fColor;
        fSpecularRGBA[i] = verts[i].fSpecularColor;
        fMultColor[i] = verts[i].fMultColor;
        fAddColor[i] = verts[i].fAddColor;
    }
}
