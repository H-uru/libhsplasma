#include "plGBufferGroup.h"

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
    //
}

void plGBufferGroup::write(hsStream* S) {
    //
}

plGBufferTriangle* plGBufferGroup::ConvertToTriList(short spanIdx,
           unsigned int whichIdx, unsigned int whichVtx, unsigned int whichCell,
           unsigned int start, unsigned int numTris) {
    //
    return NULL;
}
