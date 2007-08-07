#include "plVertexSpan.h"

plVertexSpan::plVertexSpan() { }
plVertexSpan::~plVertexSpan() { }

const char* plVertexSpan::ClassName() { return "plVertexSpan"; }

void plVertexSpan::read(hsStream* S) {
    plSpan::read(S);
    fGroupIdx = S->readInt();
    fVBufferIdx = S->readInt();
    fCellIdx = S->readInt();
    fCellOffset = S->readInt();
    fVStartIdx = S->readInt();
    fVLength = S->readInt();
}

void plVertexSpan::write(hsStream* S) {
    plSpan::write(S);
    S->writeInt(fGroupIdx);
    S->writeInt(fVBufferIdx);
    S->writeInt(fCellIdx);
    S->writeInt(fCellOffset);
    S->writeInt(fVStartIdx);
    S->writeInt(fVLength);
}

void plVertexSpan::prcWrite(pfPrcHelper* prc) {
    plSpan::prcWrite(prc);
    prc->startTag("VertexSpan");
    prc->writeParam("GroupIdx", fGroupIdx);
    prc->writeParam("BufferIdx", fVBufferIdx);
    prc->writeParam("CellIdx", fCellIdx);
    prc->writeParam("CellOffset", fCellOffset);
    prc->writeParam("StartIdx", fVStartIdx);
    prc->writeParam("Length", fVLength);
    prc->endTag(true);
}
