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


/* plGBufferGroup */
plGBufferGroup::plGBufferGroup(unsigned char fmt, bool vVol, bool iVol, int Lod) {
    format = fmt;
    //stride = ICalcVertexSize(liteStride);
    idxVolatile = iVol;
    vertsVolatile = vVol;
    LOD = Lod;
}

plGBufferGroup::~plGBufferGroup() { }

void plGBufferGroup::read(hsStream* S) {
    format = S->readByte();
    S->readInt();
    //stride = ICalcVertexSize(&liteStride);

    fVertBuffSizes.clear();
    fVertBuffStarts.clear();
    fVertBuffEnds.clear();
    fColorBuffCounts.clear();
    fIdxBuffCounts.clear();
    fIdxBuffStarts.clear();
    fIdxBuffEnds.clear();
    fVertBuffStorage.clear();
    fIdxBuffStorage.clear();

    plVertCoder coder;
    int i, count = S->readInt();
    for (i=0; i<count; i++) {
        unsigned int colorCount = 0;
        plGBufferColor* color = NULL;
        unsigned char* vData;
        unsigned int vtxCount = 0, vtxSize = 0;
        if (format & kEncoded) {
            vtxCount = S->readShort();
            vtxSize = vtxCount * stride;
            fVertBuffSizes.append(vtxSize);
            //fVertBuffStarts.append(0);
            //fVertBuffEnds.append(-1);
            vData = new unsigned char[vtxCount * stride];
            fVertBuffStorage.append(vData);
            coder.read(S, vData, format, stride, vtxCount);
            fColorBuffCounts.append(colorCount);
            fColorBuffStorage.append(color);
        } else {
            vtxSize = S->readInt();
            fVertBuffSizes.append(vtxSize);
            //fVertBuffStarts.append(0);
            //fVertBuffEnds.append(-1);
            vData = new unsigned char[vtxSize];
            S->read(vtxSize, vData);
            fVertBuffStorage.append(vData);
            colorCount = S->readInt();
            fColorBuffCounts.append(colorCount);
            color = new plGBufferColor[colorCount];
            fColorBuffStorage.append(color);
        }
    }

    count = S->readInt();
    for (i=0; i<count; i++) {
        unsigned int idxCount = S->readInt();
        fIdxBuffCounts.append(idxCount);
        //fIdxBuffStarts.append(0);
        //fIdxBuffEnds.append(-1);
        unsigned short* iData = new unsigned short[idxCount];
        S->readShorts(idxCount, (short*)iData);
        fIdxBuffStorage.append(iData);
    }

    for (i=0; i<fVertBuffStorage.getSize(); i++) {
        unsigned int cellCount = S->readInt();
        hsTArray<plGBufferCell>* cell = new hsTArray<plGBufferCell>();
        fCells.append(cell);
        cell->setSize(cellCount);
        for (unsigned int j=0; j<cellCount; j++)
            cell->get(j).read(S);
    }
}

void plGBufferGroup::write(hsStream* S) {
    format |= kEncoded;
    int i, totalSize = 0;
    for (i=0; i<fVertBuffSizes.getSize(); i++)
        totalSize += fVertBuffSizes[i];
    for (i=0; i<fIdxBuffCounts.getSize(); i++)
        totalSize += fIdxBuffCounts[i] * sizeof(short);
    S->writeByte(format);
    S->writeInt(totalSize);

    plVertCoder coder;
    S->writeInt(fVertBuffStorage.getSize());
    for (i=0; i<fVertBuffStorage.getSize(); i++) {
        S->writeShort(fVertBuffSizes[i] / stride);
        //coder.write(S, fVertBuffStorage[i], format, stride, fVertBuffSizes[i]);
    }

    S->writeInt(fVertBuffStorage.getSize());
    for (i=0; i<fIdxBuffCounts.getSize(); i++) {
        S->writeInt(fIdxBuffCounts[i]);
        S->writeShorts(fIdxBuffCounts[i], (short*)fIdxBuffStorage[i]);
    }

    for (i=0; i<fVertBuffStorage.getSize(); i++) {
        S->writeInt(fCells[i]->getSize());
        for (int j=0; j<fCells[i]->getSize(); j++)
            fCells[i]->get(j).write(S);
    }
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

