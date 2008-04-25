#include "plSpanTemplate.h"
#include "CoreLib/plDebug.h"

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
                prc->writeParam("Color", verts[i].fColor);
            if (fFormat & kColor2Mask)
                prc->writeParam("Color2", verts[i].fColor2);
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
