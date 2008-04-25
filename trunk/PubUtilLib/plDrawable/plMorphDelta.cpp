#include "plMorphDelta.h"

// plVertDelta //
void plVertDelta::read(hsStream* S) {
    fIdx = S->readShort();
    fPadding = S->readShort();
    fPos.read(S);
    fNorm.read(S);
}

void plVertDelta::write(hsStream* S) {
    S->writeShort(fIdx);
    S->writeShort(fPadding);
    fPos.write(S);
    fNorm.write(S);
}

void plVertDelta::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plVertDelta");
    prc->writeParam("Idx", fIdx);
    prc->writeParam("Padding", fPadding);
    prc->endTag();

    prc->writeSimpleTag("Pos");
    fPos.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Norm");
    fNorm.prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}


// plMorphSpan //
plMorphSpan::plMorphSpan() : fNumUVWChans(0), fUVWs(NULL) { }
plMorphSpan::~plMorphSpan() {
    if (fUVWs) delete[] fUVWs;
}

void plMorphSpan::read(hsStream* S) {
    size_t i;
    for (i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].read(S);
    for (i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].read(S);
}

void plMorphSpan::write(hsStream* S) {
    size_t i;
    for (i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].write(S);
    for (i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].write(S);
}

void plMorphSpan::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plMorphSpan");

    size_t i;
    prc->writeSimpleTag("Deltas");
    for (i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("UVWs");
    for (i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}


// plMorphDelta //
plMorphDelta::plMorphDelta() { }
plMorphDelta::~plMorphDelta() { }

IMPLEMENT_CREATABLE(plMorphDelta, kMorphDelta, plCreatable)

void plMorphDelta::read(hsStream* S, plResManager* mgr) {
    fWeight = S->readFloat();
    size_t spanCount = S->readInt();
    fSpans.clear();
    fSpans.setSize(spanCount);
    for (size_t i=0; i<spanCount; i++) {
        int nDel = S->readInt();
        int nUVW = S->readInt();
        allocDeltas(i, nDel, nUVW);
        fSpans[i].read(S);
    }
}

void plMorphDelta::write(hsStream* S, plResManager* mgr) {
    S->writeFloat(fWeight);
    S->writeInt(fSpans.getSize());
    for (size_t i=0; i<fSpans.getSize(); i++) {
        int nDel = fSpans[i].fDeltas.getSize();
        int nUVW = fSpans[i].fNumUVWChans;
        S->writeInt(nDel);
        S->writeInt(nUVW);
        fSpans[i].write(S);
    }
}

void plMorphDelta::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("plMorphDelta");
    prc->writeParam("Weight", fWeight);
    prc->endTag();
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i].prcWrite(prc);
    prc->closeTag();
}

void plMorphDelta::allocDeltas(int iSpan, int nDel, int nUVW) {
    fSpans[iSpan].fDeltas.setSize(nDel);
    fSpans[iSpan].fNumUVWChans = nUVW;
    if (fSpans[iSpan].fUVWs)
        delete[] fSpans[iSpan].fUVWs;
    fSpans[iSpan].fUVWs = (nUVW != 0 ? new hsVector3[nUVW * nDel] : NULL);
}
