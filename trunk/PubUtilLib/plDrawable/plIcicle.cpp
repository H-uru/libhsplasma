#include "plIcicle.h"

/* plIcicle */
plIcicle::plIcicle()
        : fIBufferIdx(0), fIStartIdx(0), fILength(0), fSortData(NULL) { }

plIcicle::~plIcicle() {
    if (fSortData != NULL)
        delete[] fSortData;
}

const char* plIcicle::ClassName() { return "plIcicle"; }

void plIcicle::read(hsStream* S) {
    plVertexSpan::read(S);
    fIBufferIdx = S->readInt();
    fIStartIdx = S->readInt();
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

void plIcicle::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "Icicle") {
        fIBufferIdx = tag->getParam("BufferIdx", "0").toUint();
        fIStartIdx = tag->getParam("StartIdx", "0").toUint();
        fILength = tag->getParam("Length", "0").toUint();
    } else if (tag->getName() == "SortData") {
        if (tag->countChildren() != (fILength / 3))
            throw pfPrcParseException(__FILE__, __LINE__, "SortData should have exactly Length/3 triangles");
        fSortData = new plGBufferTriangle[fILength / 3];
        const pfPrcTag* child = tag->getFirstChild();
        for (unsigned int i=0; i<(fILength / 3); i++) {
            fSortData[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plVertexSpan::IPrcParse(tag);
    }
}


/* plParticleSpan */
const char* plParticleSpan::ClassName() { return "plParticleSpan"; }

void plParticleSpan::read(hsStream* S) { }
void plParticleSpan::write(hsStream* S) { }
void plParticleSpan::IPrcWrite(pfPrcHelper* prc) { }

void plParticleSpan::IPrcParse(const pfPrcTag* tag) {
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}

void plParticleSpan::setSrcSpanIdx(unsigned int idx) { fSrcSpanIdx = idx; }
