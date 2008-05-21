#include "plSpanTemplate.h"

plSpanTemplate::plSpanTemplate()
              : fNumVerts(0), fNumTris(0), fFormat(0), fStride(0),
                fData(NULL), fIndices(NULL) { }

plSpanTemplate::~plSpanTemplate() {
    if (fData != NULL)
        delete[] fData;
    if (fIndices != NULL)
        delete[] fIndices;
}

void plSpanTemplate::read(hsStream* S) {
    if (fData != NULL)
        delete[] fData;
    if (fIndices != NULL)
        delete[] fIndices;

    fNumVerts = S->readShort();
    fFormat = S->readShort();
    fNumTris = S->readShort();
    fStride = CalcStride(fFormat);
    fData = new unsigned char[fNumVerts * fStride];
    fIndices = new unsigned short[fNumTris * 3];
    S->read(fStride * fNumVerts, fData);
    S->read(fNumTris * 3 * sizeof(unsigned short), fIndices);
}

void plSpanTemplate::write(hsStream* S) {
    S->writeShort(fNumVerts);
    S->writeShort(fFormat);
    S->writeShort(fNumTris);
    S->write(fStride * fNumVerts, fData);
    S->write(fNumTris * 3 * sizeof(unsigned short), fIndices);
}

void plSpanTemplate::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plSpanTemplate");
    prc->writeParam("Format", fFormat);
    prc->endTag();

    prc->writeSimpleTag("Vertices");
    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        hsTArray<Vertex> verts = getVertices();
        for (size_t i=0; i<verts.getSize(); i++) {
            prc->startTag("Vertex");
            if (fFormat & kColorMask)
                prc->writeParamHex("Color", verts[i].fColor);
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
                for (size_t j=0; j<(fFormat & kUVWMask) / 0x10; j++)
                    verts[i].fUVWs[j].prcWrite(prc);
                prc->closeTag();
            }
            if (fFormat & kWeightMask) {
                prc->writeTagNoBreak("Weights");
                for (size_t j=0; j<(fFormat & kWeightMask) / 0x100; j++)
                    prc->getStream()->writeStr(plString::Format("%f ", verts[i].fWeights[j]));
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
        prc->getStream()->writeStr(plString::Format("%d %d %d",
                                   fIndices[i], fIndices[i+1], fIndices[i+2]));
        prc->closeTagNoBreak();
    }
    prc->closeTag();

    prc->closeTag(); // plSpanTemplate
}

void plSpanTemplate::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plSpanTemplate")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    
    fFormat = tag->getParam("Format", "0").toUint();
    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Vertices") {
            fNumVerts = child->countChildren();
            hsTArray<Vertex> verts;
            verts.setSize(fNumVerts);
            const pfPrcTag* vertChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                if (vertChild->getName() != "Vertex")
                    throw pfPrcTagException(__FILE__, __LINE__, vertChild->getName());
                verts[i].fColor = tag->getParam("Color", "0").toUint();
                verts[i].fColor2 = tag->getParam("Color2", "0").toUint();
                verts[i].fWeightIdx = tag->getParam("WeightIdx", "0").toInt();
                const pfPrcTag* subChild = vertChild->getFirstChild();
                while (subChild != NULL) {
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
                        for (size_t j=0; j<(fFormat & kUVWMask) / 0x10; j++) {
                            verts[i].fUVWs[j].prcParse(uvwChild);
                            uvwChild = uvwChild->getNextSibling();
                        }
                    } else if (subChild->getName() == "Weights") {
                        hsTList<plString> wgtList = subChild->getContents();
                        if (wgtList.getSize() != (fFormat & kWeightMask) / 0x100)
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of Weights");
                        for (size_t j=0; j<(fFormat & kWeightMask) / 0x100; j++)
                            verts[i].fWeights[j] = wgtList.pop().toFloat();
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
                hsTList<plString> idxList = idxChild->getContents();
                if (idxList.getSize() != 3)
                    throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                fIndices[i] = idxList.pop().toUint();
                fIndices[i+1] = idxList.pop().toUint();
                fIndices[i+2] = idxList.pop().toUint();
                idxChild = idxChild->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

hsTArray<plSpanTemplate::Vertex> plSpanTemplate::getVertices() const {
    hsTArray<Vertex> verts;
    verts.setSize(fNumVerts);
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
            for (size_t j=0; j<(fFormat & kWeightMask) / 0x100; j++) {
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
            verts[i].fColor = *(unsigned int*)dataPtr;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kColor2Mask) {
            verts[i].fColor2 = *(unsigned int*)dataPtr;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kUVWMask) {
            for (size_t j=0; j<(fFormat & kUVWMask) / 0x10; j++) {
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

unsigned short plSpanTemplate::getNumVerts() const { return fNumVerts; }

void plSpanTemplate::setVertices(const hsTArray<Vertex>& verts) {
    fStride = CalcStride(fFormat);
    fNumVerts = verts.getSize();
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
            for (size_t j=0; j<(fFormat & kWeightMask) / 0x100; j++) {
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
            *(unsigned int*)dataPtr = verts[i].fColor;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kColor2Mask) {
            *(unsigned int*)dataPtr = verts[i].fColor2;
            dataPtr += sizeof(unsigned int);
        }
        if (fFormat & kUVWMask) {
            for (size_t j=0; j<(fFormat & kUVWMask) / 0x10; j++) {
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

unsigned short plSpanTemplate::CalcStride(unsigned short format) {
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
