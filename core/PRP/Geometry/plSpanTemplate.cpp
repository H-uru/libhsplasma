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

#include "plSpanTemplate.h"
#include <string_theory/format>
#include <cstring>

plSpanTemplate::~plSpanTemplate()
{
    delete[] fData;
    delete[] fIndices;
}

void plSpanTemplate::read(hsStream* S)
{
    delete[] fData;
    delete[] fIndices;

    fNumVerts = S->readShort();
    setFormat(S->readShort());
    fNumTris = S->readShort();
    fData = new unsigned char[fNumVerts * fStride];
    fIndices = new unsigned short[fNumTris * 3];
    S->read(fStride * fNumVerts, fData);
    S->read(fNumTris * 3 * sizeof(unsigned short), fIndices);
}

void plSpanTemplate::write(hsStream* S)
{
    S->writeShort(fNumVerts);
    S->writeShort(fFormat);
    S->writeShort(fNumTris);
    S->write(fStride * fNumVerts, fData);
    S->write(fNumTris * 3 * sizeof(unsigned short), fIndices);
}

void plSpanTemplate::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plSpanTemplate");
    prc->writeParam("Format", fFormat);
    prc->endTag();

    prc->writeSimpleTag("Vertices");
    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        std::vector<Vertex> verts = getVertices();
        for (size_t i=0; i<verts.size(); i++) {
            prc->startTag("Vertex");
            if (fFormat & kColorMask)
                prc->writeParamHex("Color1", verts[i].fColor1);
            if (fFormat & kColor2Mask)
                prc->writeParamHex("Color2", verts[i].fColor2);
            if (fFormat & kWgtIdxMask)
                prc->writeParam("WeightIdx", verts[i].fWeightIdx);
            prc->endTag();

            if (fFormat & kPosMask) {
                prc->writeSimpleTag("Position");
                verts[i].fPosition.prcWrite(prc);
                prc->closeTag();
            }
            if (fFormat & kNormMask) {
                prc->writeSimpleTag("Normal");
                verts[i].fNormal.prcWrite(prc);
                prc->closeTag();
            }
            if (fFormat & kUVWMask) {
                prc->writeSimpleTag("UVWs");
                for (size_t j=0; j<(size_t)((fFormat & kUVWMask) / 0x10); j++)
                    verts[i].fUVWs[j].prcWrite(prc);
                prc->closeTag();
            }
            if (fFormat & kWeightMask) {
                prc->writeTagNoBreak("Weights");
                for (size_t j=0; j<(size_t)((fFormat & kWeightMask) / 0x100); j++)
                    prc->directWrite(ST::format("{f} ", verts[i].fWeights[j]));
                prc->closeTagNoBreak();
            }

            prc->closeTag();
        }
    } else {
        prc->writeComment("Vertex data excluded");
    }
    prc->closeTag();

    prc->writeSimpleTag("Indices");
    for (size_t i=0; i<(size_t)(fNumTris * 3); i += 3) {
        prc->writeTagNoBreak("Triangle");
        prc->directWrite(ST::format("{} {} {}",
                         fIndices[i], fIndices[i+1], fIndices[i+2]));
        prc->closeTagNoBreak();
    }
    prc->closeTag();

    prc->closeTag(); // plSpanTemplate
}

void plSpanTemplate::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plSpanTemplate")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFormat = tag->getParam("Format", "0").to_uint();
    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "Vertices") {
            fNumVerts = child->countChildren();
            std::vector<Vertex> verts(fNumVerts);
            const pfPrcTag* vertChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                if (vertChild->getName() != "Vertex")
                    throw pfPrcTagException(__FILE__, __LINE__, vertChild->getName());
                verts[i].fColor1 = tag->getParam("Color1", "0").to_uint();
                verts[i].fColor2 = tag->getParam("Color2", "0").to_uint();
                verts[i].fWeightIdx = tag->getParam("WeightIdx", "0").to_int();
                const pfPrcTag* subChild = vertChild->getFirstChild();
                while (subChild) {
                    if (subChild->getName() == "Position") {
                        if (subChild->hasChildren())
                            verts[i].fPosition.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "Normal") {
                        if (subChild->hasChildren())
                            verts[i].fNormal.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "UVWs") {
                        if ((fFormat & kUVWMask) / 0x10 != subChild->countChildren())
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of UVW maps");
                        const pfPrcTag* uvwChild = subChild->getFirstChild();
                        for (size_t j=0; j<(size_t)((fFormat & kUVWMask) / 0x10); j++) {
                            verts[i].fUVWs[j].prcParse(uvwChild);
                            uvwChild = uvwChild->getNextSibling();
                        }
                    } else if (subChild->getName() == "Weights") {
                        std::list<ST::string> wgtList = subChild->getContents();
                        if (wgtList.size() != (fFormat & kWeightMask) / 0x100)
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of Weights");
                        auto wgt = wgtList.begin();
                        for (size_t j=0; j<(size_t)((fFormat & kWeightMask) / 0x100); j++)
                            verts[i].fWeights[j] = (*wgt++).to_float();
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                    }
                    subChild = subChild->getNextSibling();
                }
                vertChild = vertChild->getNextSibling();
            }
            setVertices(verts);
        } else if (child->getName() == "Indices") {
            fNumTris = child->countChildren();
            fIndices = new unsigned short[fNumTris * 3];
            const pfPrcTag* idxChild = child->getFirstChild();
            for (size_t i=0; i<(size_t)(fNumTris * 3); i += 3) {
                std::list<ST::string> idxList = idxChild->getContents();
                if (idxList.size() != 3)
                    throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                auto idx_iter = idxList.begin();
                fIndices[i] = (*idx_iter++).to_uint();
                fIndices[i+1] = (*idx_iter++).to_uint();
                fIndices[i+2] = (*idx_iter++).to_uint();
                idxChild = idxChild->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

std::vector<plSpanTemplate::Vertex> plSpanTemplate::getVertices() const
{
    std::vector<Vertex> verts(fNumVerts);
    unsigned char* dataPtr = fData;
    for (size_t i=0; i<fNumVerts; i++) {
        if (fFormat & kPosMask) {
            verts[i].fPosition.X = *(float*)dataPtr;
            dataPtr += sizeof(float);
            verts[i].fPosition.Y = *(float*)dataPtr;
            dataPtr += sizeof(float);
            verts[i].fPosition.Z = *(float*)dataPtr;
            dataPtr += sizeof(float);
        }
        if (fFormat & kWeightMask) {
            for (size_t j=0; j<(size_t)((fFormat & kWeightMask) / 0x100); j++) {
                verts[i].fWeights[j] = *(float*)dataPtr;
                dataPtr += sizeof(float);
            }
        }
        if (fFormat & kWgtIdxMask) {
            verts[i].fWeightIdx = *(int*)dataPtr;
            dataPtr += sizeof(int);
        }
        if (fFormat & kNormMask) {
            verts[i].fNormal.X = *(float*)dataPtr;
            dataPtr += sizeof(float);
            verts[i].fNormal.Y = *(float*)dataPtr;
            dataPtr += sizeof(float);
            verts[i].fNormal.Z = *(float*)dataPtr;
            dataPtr += sizeof(float);
        }
        if (fFormat & kColorMask) {
            verts[i].fColor1 = *(unsigned int*)dataPtr;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kColor2Mask) {
            verts[i].fColor2 = *(unsigned int*)dataPtr;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kUVWMask) {
            for (size_t j=0; j<(size_t)((fFormat & kUVWMask) / 0x10); j++) {
                verts[i].fUVWs[j].X = *(float*)dataPtr;
                dataPtr += sizeof(float);
                verts[i].fUVWs[j].Y = *(float*)dataPtr;
                dataPtr += sizeof(float);
                verts[i].fUVWs[j].Z = *(float*)dataPtr;
                dataPtr += sizeof(float);
            }
        }
    }
    return verts;
}

void plSpanTemplate::setVertices(const std::vector<Vertex>& verts)
{
    delete[] fData;
    if (verts.empty()) {
        fData = nullptr;
        return;
    }

    fStride = CalcStride(fFormat);
    fNumVerts = verts.size();
    fData = new unsigned char[fNumVerts * fStride];

    unsigned char* dataPtr = fData;
    for (size_t i=0; i<fNumVerts; i++) {
        if (fFormat & kPosMask) {
            *(float*)dataPtr = verts[i].fPosition.X;
            dataPtr += sizeof(float);
            *(float*)dataPtr = verts[i].fPosition.Y;
            dataPtr += sizeof(float);
            *(float*)dataPtr = verts[i].fPosition.Z;
            dataPtr += sizeof(float);
        }
        if (fFormat & kWeightMask) {
            for (size_t j=0; j<(size_t)((fFormat & kWeightMask) / 0x100); j++) {
                *(float*)dataPtr = verts[i].fWeights[j];
                dataPtr += sizeof(float);
            }
        }
        if (fFormat & kWgtIdxMask) {
            *(int*)dataPtr = verts[i].fWeightIdx;
            dataPtr += sizeof(int);
        }
        if (fFormat & kNormMask) {
            *(float*)dataPtr = verts[i].fNormal.X;
            dataPtr += sizeof(float);
            *(float*)dataPtr = verts[i].fNormal.Y;
            dataPtr += sizeof(float);
            *(float*)dataPtr = verts[i].fNormal.Z;
            dataPtr += sizeof(float);
        }
        if (fFormat & kColorMask) {
            *(unsigned int*)dataPtr = verts[i].fColor1;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kColor2Mask) {
            *(unsigned int*)dataPtr = verts[i].fColor2;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kUVWMask) {
            for (size_t j=0; j<(size_t)((fFormat & kUVWMask) / 0x10); j++) {
                *(float*)dataPtr = verts[i].fUVWs[j].X;
                dataPtr += sizeof(float);
                *(float*)dataPtr = verts[i].fUVWs[j].Y;
                dataPtr += sizeof(float);
                *(float*)dataPtr = verts[i].fUVWs[j].Z;
                dataPtr += sizeof(float);
            }
        }
    }
}

void plSpanTemplate::setIndices(unsigned short count, const unsigned short* indices)
{
    delete[] fIndices;
    if (count == 0) {
        fIndices = nullptr;
        return;
    }
    fIndices = new unsigned short[count];
    memcpy(fIndices, indices, count * sizeof(unsigned short));
}

void plSpanTemplate::setFormat(unsigned short fmt)
{
    fFormat = fmt;
    fStride = CalcStride(fFormat);
}

unsigned short plSpanTemplate::CalcStride(unsigned short format)
{
    unsigned short stride = 0;
    if (format & kPosMask)
        stride = sizeof(float) * 3; //hsPoint3
    if (format & kNormMask)
        stride += sizeof(float) * 3; //hsPoint3
    if (format & kColorMask)
        stride += sizeof(unsigned int);
    if (format & kColor2Mask)
        stride += sizeof(unsigned int);
    if (format & kWgtIdxMask)
        stride += sizeof(unsigned int);
    if (format & kUVWMask)
        stride += ((format & kUVWMask) / 0x10) * sizeof(float) * 3; // hsPoint3
    if (format & kWeightMask)
        stride += ((format & kWeightMask) / 0x100) * sizeof(unsigned int);
    return stride;
}
