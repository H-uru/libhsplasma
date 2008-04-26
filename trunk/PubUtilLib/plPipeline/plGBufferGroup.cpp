#include "plGBufferGroup.h"

/* plGBufferCell */
void plGBufferCell::read(hsStream* S) {
    vtxStart = S->readInt();
    colorStart = S->readInt();
    length = S->readInt();
}

void plGBufferCell::write(hsStream* S) {
    S->writeInt(vtxStart);
    S->writeInt(colorStart);
    S->writeInt(length);
}

void plGBufferCell::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGBufferCell");
    prc->writeParam("VertexStart", vtxStart);
    prc->writeParam("ColorStart", colorStart);
    prc->writeParam("Length", length);
    prc->endTag(true);
}


/* plGBufferTriangle */
plGBufferTriangle::plGBufferTriangle() { }
plGBufferTriangle::~plGBufferTriangle() { }

void plGBufferTriangle::read(hsStream* S) {
    index1 = S->readShort();
    index2 = S->readShort();
    index3 = S->readShort();
    spanIndex = S->readShort();
    center.read(S);
}

void plGBufferTriangle::write(hsStream* S) {
    S->writeShort(index1);
    S->writeShort(index2);
    S->writeShort(index3);
    S->writeShort(spanIndex);
    center.write(S);
}

void plGBufferTriangle::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plGBufferTriangle");
      prc->startTag("Indices");
      prc->writeParam("Index1", index1);
      prc->writeParam("Index2", index2);
      prc->writeParam("Index3", index3);
      prc->writeParam("SpanIndex", spanIndex);
      prc->endTag(true);
      center.prcWrite(prc);
    prc->closeTag();
}


/* plGBufferGroup */
plGBufferGroup::plGBufferGroup(unsigned char fmt, bool vVol, bool iVol, int Lod) {
    format = fmt;
    numVerts = 0;
    numIndices = 0;
    stride = ICalcVertexSize(liteStride);
    idxVolatile = iVol;
    vertsVolatile = vVol;
    LOD = Lod;
}

plGBufferGroup::~plGBufferGroup() {
    for (size_t i=0; i<fVertBuffStorage.getSize(); i++)
        delete[] fVertBuffStorage[i];
    for (size_t i=0; i<fIdxBuffStorage.getSize(); i++)
        delete[] fIdxBuffStorage[i];
    for (size_t i=0; i<fCells.getSize(); i++)
        delete fCells[i];
}

hsTArray<plGBufferVertex> plGBufferGroup::getVertices() {
    hsTArray<plGBufferVertex> buf;
    size_t vi = 0;
    
    for (size_t i=0; i<fVertBuffStorage.getSize(); i++) {
        unsigned char* cp = fVertBuffStorage[i];
        buf.setSize(buf.getSize() + (fVertBuffSizes[i] / stride));
        for (size_t i2=0; i2<(fVertBuffSizes[i] / stride); i2++) {
            plGBufferVertex v;
            v.fPos.X = *(float*)cp; cp += sizeof(float);
            v.fPos.Y = *(float*)cp; cp += sizeof(float);
            v.fPos.Z = *(float*)cp; cp += sizeof(float);

            int weightCount = (format & kSkinWeightMask) >> 4;
            if (weightCount > 0) {
                for (int j=0; j<weightCount; j++) {
                    v.fSkinWeights[j] = *(float*)cp;
                    cp += sizeof(float);
                }
                if (format & kSkinIndices) {
                    v.fSkinIdx = *(int*)cp;
                    cp += sizeof(int);
                }
            }

            v.fNormal.X = *(float*)cp; cp += sizeof(float);
            v.fNormal.Y = *(float*)cp; cp += sizeof(float);
            v.fNormal.Z = *(float*)cp; cp += sizeof(float);

            v.fColor = *(unsigned int*)cp;
            cp += sizeof(unsigned int);

            // Zero (Color2?)
            cp += sizeof(unsigned int);

            for (size_t j=0; j<(format & kUVCountMask); j++) {
                v.fUVWs[j].X = *(float*)cp; cp += sizeof(float);
                v.fUVWs[j].Y = *(float*)cp; cp += sizeof(float);
                v.fUVWs[j].Z = *(float*)cp; cp += sizeof(float);
            }
            
            buf[vi++] = v;
        }
    }
    return buf;
}

hsTList<unsigned short> plGBufferGroup::getIndices() {
    hsTList<unsigned short> buf;
    
    for (size_t i=0; i<fIdxBuffStorage.getSize(); i++) {
        for (size_t j=0; j<fIdxBuffCounts[i]; j++)
            buf.push(fIdxBuffStorage[i][j]);
    }
    return buf;
}

void plGBufferGroup::read(hsStream* S) {
    format = S->readByte();
    S->readInt();
    stride = ICalcVertexSize(liteStride);

    fVertBuffSizes.clear();
    fVertBuffStarts.clear();
    fVertBuffEnds.clear();
    //fColorBuffCounts.clear();
    fIdxBuffCounts.clear();
    fIdxBuffStarts.clear();
    fIdxBuffEnds.clear();
    fVertBuffStorage.clear();
    fIdxBuffStorage.clear();

    plVertCoder coder;
    size_t i, count = S->readInt();
    fVertBuffSizes.setSize(count);
    fVertBuffStorage.setSize(count);
    //fColorBuffCounts.setSize(count);
    //fColorBuffStorage.setSize(count);
    for (i=0; i<count; i++) {
        unsigned int colorCount = 0;
        //plGBufferColor* color = NULL;
        unsigned char* vData;
        unsigned int vtxCount = 0, vtxSize = 0;
        if (format & kEncoded) {
            vtxCount = S->readShort();
            vtxSize = vtxCount * stride;
            fVertBuffSizes[i] = vtxSize;
            //fVertBuffStarts.append(0);
            //fVertBuffEnds.append(-1);
            vData = new unsigned char[vtxSize];
            fVertBuffStorage[i] = vData;
            coder.read(S, vData, format, vtxCount);
            //fColorBuffCounts.append(colorCount);
            //fColorBuffStorage.append(color);
        } else {
            vtxSize = S->readInt();
            fVertBuffSizes[i] = vtxSize;
            //fVertBuffStarts.append(0);
            //fVertBuffEnds.append(-1);
            vData = new unsigned char[vtxSize];
            S->read(vtxSize, vData);
            fVertBuffStorage[i] = vData;
            colorCount = S->readInt();
            //fColorBuffCounts.append(colorCount);
            //color = new plGBufferColor[colorCount];
            //fColorBuffStorage.append(color);
        }
    }

    count = S->readInt();
    fIdxBuffCounts.setSize(count);
    fIdxBuffStorage.setSize(count);
    for (i=0; i<count; i++) {
        unsigned int idxCount = S->readInt();
        fIdxBuffCounts[i] = idxCount;
        //fIdxBuffStarts.append(0);
        //fIdxBuffEnds.append(-1);
        unsigned short* iData = new unsigned short[idxCount];
        S->readShorts(idxCount, iData);
        fIdxBuffStorage[i] = iData;
    }

    fCells.setSize(fVertBuffStorage.getSize());
    for (i=0; i<fVertBuffStorage.getSize(); i++) {
        size_t cellCount = S->readInt();
        hsTArray<plGBufferCell>* cell = new hsTArray<plGBufferCell>();
        fCells[i] = cell;
        cell->setSize(cellCount);
        for (size_t j=0; j<cellCount; j++)
            (*cell)[j].read(S);
    }
}

void plGBufferGroup::write(hsStream* S) {
    format |= kEncoded;
    size_t i, totalSize = 0;
    for (i=0; i<fVertBuffSizes.getSize(); i++)
        totalSize += fVertBuffSizes[i];
    for (i=0; i<fIdxBuffCounts.getSize(); i++)
        totalSize += fIdxBuffCounts[i] * sizeof(short);
    S->writeByte(format);
    S->writeInt(totalSize);

    plVertCoder coder;
    S->writeInt(fVertBuffStorage.getSize());
    for (i=0; i<fVertBuffStorage.getSize(); i++) {
        unsigned int count = fVertBuffSizes[i] / stride;
        S->writeShort(count);
        coder.write(S, fVertBuffStorage[i], format, stride, count);
    }

    S->writeInt(fIdxBuffStorage.getSize());
    for (i=0; i<fIdxBuffCounts.getSize(); i++) {
        S->writeInt(fIdxBuffCounts[i]);
        S->writeShorts(fIdxBuffCounts[i], fIdxBuffStorage[i]);
    }

    for (i=0; i<fVertBuffStorage.getSize(); i++) {
        S->writeInt(fCells[i]->getSize());
        for (size_t j=0; j<fCells[i]->getSize(); j++)
            (*fCells[i])[j].write(S);
    }
}

void plGBufferGroup::prcWrite(pfPrcHelper* prc) {
    size_t i, j;
    prc->startTag("plGBufferGroup");
    prc->writeParamHex("format", format);
    prc->endTag();
    
    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        hsTArray<plGBufferVertex> verts = getVertices();
        for (i=0; i<verts.getSize(); i++) {
            prc->writeSimpleTag("Vertex");

            prc->writeSimpleTag("Position");
            verts[i].fPos.prcWrite(prc);
            prc->closeTag();

            prc->startTag("SkinWeights");
            if (format & kSkinIndices)
                prc->writeParam("SkinIndex", verts[i].fSkinIdx);
            prc->endTagNoBreak();
            for (j=0; j<(size_t)((format & kSkinWeightMask) >> 4); j++)
                prc->getStream()->writeStr(plString::Format("%f ", verts[i].fSkinWeights[j]));
            prc->closeTagNoBreak();

            prc->writeSimpleTag("Normal");
            verts[i].fNormal.prcWrite(prc);
            prc->closeTag();
            prc->startTag("Color");
            prc->writeParamHex("value", verts[i].fColor);
            prc->endTag(true);

            prc->writeSimpleTag("UVWMaps");
            for (j=0; j<(format & kUVCountMask); j++)
                verts[i].fUVWs[j].prcWrite(prc);
            prc->closeTag();

            prc->closeTag();
        }

        for (i=0; i<fIdxBuffStorage.getSize(); i++) {
            prc->writeSimpleTag("IndexData");
            for (j=0; j<fIdxBuffCounts[i]; j += 3) {
                prc->writeTagNoBreak("Triangle");
                prc->getStream()->writeStr(plString::Format("%d %d %d",
                                           fIdxBuffStorage[i][j],
                                           fIdxBuffStorage[i][j+1],
                                           fIdxBuffStorage[i][j+2]));
                prc->closeTagNoBreak();
            }
            prc->closeTag();
        }
        prc->writeSimpleTag("CellGroups");
        for (i=0; i<fVertBuffStorage.getSize(); i++) {
            for (j=0; j<fCells[i]->getSize(); j++)
                (*fCells[i])[j].prcWrite(prc);
        }
        prc->closeTag(); // CellGroups
    } else {
        prc->writeComment("Vertex data excluded");
    }
    prc->closeTag(); // plGBufferGroup
}

unsigned char plGBufferGroup::ICalcVertexSize(unsigned char& lStride) {
    lStride = ((format & kUVCountMask) + 2) * 12;
    numSkinWeights = (format & kSkinWeightMask) >> 4;
    if (numSkinWeights != 0) {
        lStride += numSkinWeights * sizeof(float);
        if (format & kSkinIndices)
            lStride += sizeof(int);
    }
    return lStride + 8;
}

plGBufferTriangle* plGBufferGroup::ConvertToTriList(short spanIdx,
           unsigned int whichIdx, unsigned int whichVtx, unsigned int whichCell,
           unsigned int start, unsigned int numTris) {
    //
    return NULL;
}
