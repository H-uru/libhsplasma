#include "plVertexSpan.h"

plVertexSpan::plVertexSpan()
            : fGroupIdx(0), fVBufferIdx(0), fCellIdx(0), fCellOffset(0),
              fVStartIdx(0), fVLength(0) { }

plVertexSpan::plVertexSpan(const plVertexSpan& init)
            : plSpan(init), fGroupIdx(init.fGroupIdx),
              fVBufferIdx(init.fVBufferIdx), fCellIdx(init.fCellIdx),
              fCellOffset(init.fCellOffset), fVStartIdx(init.fVStartIdx),
              fVLength(init.fVLength) { }

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

void plVertexSpan::IPrcWrite(pfPrcHelper* prc) {
    plSpan::IPrcWrite(prc);
    prc->startTag("VertexSpan");
    prc->writeParam("GroupIdx", fGroupIdx);
    prc->writeParam("BufferIdx", fVBufferIdx);
    prc->writeParam("CellIdx", fCellIdx);
    prc->writeParam("CellOffset", fCellOffset);
    prc->writeParam("StartIdx", fVStartIdx);
    prc->writeParam("Length", fVLength);
    prc->endTag(true);
}

void plVertexSpan::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "VertexSpan") {
        fGroupIdx = tag->getParam("GroupIdx", "0").toUint();
        fVBufferIdx = tag->getParam("BufferIdx", "0").toUint();
        fCellIdx = tag->getParam("CellIdx", "0").toUint();
        fCellOffset = tag->getParam("CellOffset", "0").toUint();
        fVStartIdx = tag->getParam("StartIdx", "0").toUint();
        fVLength = tag->getParam("Length", "0").toUint();
    } else {
        plSpan::IPrcParse(tag);
    }
}

unsigned int plVertexSpan::getGroupIdx() const { return fGroupIdx; }
unsigned int plVertexSpan::getVBufferIdx() const { return fVBufferIdx; }
unsigned int plVertexSpan::getCellIdx() const { return fCellIdx; }
unsigned int plVertexSpan::getCellOffset() const { return fCellOffset; }
unsigned int plVertexSpan::getVStartIdx() const { return fVStartIdx; }
unsigned int plVertexSpan::getVLength() const { return fVLength; }
