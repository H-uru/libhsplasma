#include "plIcicle.h"

/* plIcicle */
plIcicle::plIcicle()
        : fIBufferIdx(0), fIStartIdx(0), fILength(0), fSortData(NULL) { }

plIcicle::plIcicle(const plIcicle& init)
        : plVertexSpan(init), fIBufferIdx(init.fIBufferIdx),
          fIStartIdx(init.fIStartIdx), fILength(init.fILength) {
    if (fProps & kPropFacesSortable) {
        fSortData = new plGBufferTriangle[fILength / 3];
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i] = init.fSortData[i];
    } else {
        fSortData = NULL;
    }
}

plIcicle::~plIcicle() {
    if (fSortData != NULL)
        delete[] fSortData;
}

void plIcicle::read(hsStream* S) {
    plVertexSpan::read(S);
    if (S->getVer() != pvHex) {
        fIBufferIdx = S->readInt();
        fIStartIdx = S->readInt();
    }
    fILength = S->readInt();
    if (fProps & kPropFacesSortable) {
        if (fSortData != NULL)
            delete[] fSortData;
        fSortData = new plGBufferTriangle[fILength / 3];
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i].read(S);
    } else {
        fSortData = NULL;
    }
}

void plIcicle::write(hsStream* S) {
    plVertexSpan::write(S);
    if (S->getVer() != pvHex) {
        S->writeInt(fIBufferIdx);
        S->writeInt(fIStartIdx);
    }
    S->writeInt(fILength);
    if (fProps & kPropFacesSortable) {
        for (size_t i=0; i<(fILength / 3); i++)
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
        for (size_t i=0; i<(fILength / 3); i++)
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
        if (fSortData != NULL)
            delete[] fSortData;
        fSortData = new plGBufferTriangle[fILength / 3];
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<(fILength / 3); i++) {
            fSortData[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plVertexSpan::IPrcParse(tag);
    }
}

void plIcicle::setSortData(const plGBufferTriangle* data) {
    if (fSortData != NULL)
        delete[] fSortData;
    if (data == NULL) {
        fProps &= ~kPropFacesSortable;
        fSortData = NULL;
    } else {
        fProps |= kPropFacesSortable;
        fSortData = new plGBufferTriangle[fILength / 3];
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i] = data[i];
    }
}


/* plParticleSpan */
void plParticleSpan::read(hsStream* S) { }
void plParticleSpan::write(hsStream* S) { }
void plParticleSpan::IPrcWrite(pfPrcHelper* prc) { }

void plParticleSpan::IPrcParse(const pfPrcTag* tag) {
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}
