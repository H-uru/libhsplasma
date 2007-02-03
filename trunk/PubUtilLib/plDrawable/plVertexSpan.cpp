#include "plVertexSpan.h"

plVertexSpan::plVertexSpan() { }
plVertexSpan::~plVertexSpan() { }

void plVertexSpan::read(hsStream* S) {
    plSpan::read(S);
    groupIdx = S->readInt();
    VBufferIdx = S->readInt();
    cellIdx = S->readInt();
    cellOffset = S->readInt();
    VStartIdx = S->readInt();
    VLength = S->readInt();
}

void plVertexSpan::write(hsStream* S) {
    plSpan::write(S);
    S->writeInt(groupIdx);
    S->writeInt(VBufferIdx);
    S->writeInt(cellIdx);
    S->writeInt(cellOffset);
    S->writeInt(VStartIdx);
    S->writeInt(VLength);
}
