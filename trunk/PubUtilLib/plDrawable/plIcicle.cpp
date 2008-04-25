#include "plIcicle.h"

/* plIcicle */
plIcicle::plIcicle() { }
plIcicle::~plIcicle() { }

const char* plIcicle::ClassName() { return "plIcicle"; }

void plIcicle::read(hsStream* S) {
    plVertexSpan::read(S);
    fIBufferIdx = S->readInt();
    fIPackedIdx = fIStartIdx = S->readInt();
    fILength = S->readInt();
    if (fProps & kPropFacesSortable) {
        fSortData = new plGBufferTriangle[fILength / 3];
        for (unsigned int i=0; i<(fILength / 3); i++)
            fSortData[i].read(S);
    } else
        fSortData = NULL;
}

void plIcicle::write(hsStream* S) {
    plVertexSpan::write(S);
    S->writeInt(fIBufferIdx);
    S->writeInt(fIStartIdx);
    S->writeInt(fILength);
    if (fProps & kPropFacesSortable) {
        for (unsigned int i=0; i<(fILength / 3); i++)
            fSortData[i].write(S);
    }
}

void plIcicle::IPrcWrite(pfPrcHelper* prc) {
    plVertexSpan::IPrcWrite(prc);
    prc->startTag("Icicle");
    prc->writeParam("BufferIdx", fIBufferIdx);
    prc->writeParam("StartIdx", fIStartIdx);
    prc->writeParam("Length", fILength);
    prc->endTag(true);
    if (fProps & kPropFacesSortable) {
        prc->writeSimpleTag("SortData");
        for (unsigned int i=0; i<(fILength / 3); i++)
            fSortData[i].prcWrite(prc);
        prc->closeTag();
    }
}


/* plParticleSpan */
const char* plParticleSpan::ClassName() { return "plParticleSpan"; }

void plParticleSpan::read(hsStream* S) { }
void plParticleSpan::write(hsStream* S) { }
void plParticleSpan::IPrcWrite(pfPrcHelper* prc) { }

void plParticleSpan::setSrcSpanIdx(unsigned int idx) { fSrcSpanIdx = idx; }
