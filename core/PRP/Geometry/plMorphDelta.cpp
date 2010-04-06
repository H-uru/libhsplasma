#include "plMorphDelta.h"

/* plVertDelta */
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

void plVertDelta::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plVertDelta")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fIdx = tag->getParam("Idx", "0").toUint();
    fPadding = tag->getParam("Padding", "0").toUint();

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Pos") {
            if (child->hasChildren())
                fPos.prcParse(child->getFirstChild());
        } else if (child->getName() == "Norm") {
            if (child->hasChildren())
                fNorm.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}


/* plMorphSpan */
plMorphSpan::plMorphSpan() : fNumUVWChans(0), fUVWs(NULL) { }

plMorphSpan::~plMorphSpan() {
    delete[] fUVWs;
}

void plMorphSpan::read(hsStream* S) {
    fDeltas.setSize(S->readInt());
    fNumUVWChans = S->readInt();
    delete[] fUVWs;
    if (fNumUVWChans > 0)
        fUVWs = new hsVector3[fNumUVWChans * fDeltas.getSize()];
    else
        fUVWs = NULL;

    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].read(S);
    for (size_t i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].read(S);
}

void plMorphSpan::write(hsStream* S) {
    S->writeInt(fDeltas.getSize());
    S->writeInt(fNumUVWChans);

    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].write(S);
    for (size_t i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].write(S);
}

void plMorphSpan::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plMorphSpan");

    prc->writeSimpleTag("Deltas");
    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].prcWrite(prc);
    prc->closeTag();

    prc->startTag("UVWs");
    prc->writeParam("Channels", fNumUVWChans);
    prc->endTag();
    for (size_t i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}

void plMorphSpan::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plMorphSpan")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Deltas") {
            fDeltas.setSize(child->countChildren());
            const pfPrcTag* subchild = child->getFirstChild();
            for (size_t i=0; i<fDeltas.getSize(); i++) {
                fDeltas[i].prcParse(subchild);
                subchild = subchild->getNextSibling();
            }
        } else if (child->getName() == "UVWs") {
            delete[] fUVWs;
            fNumUVWChans = child->getParam("Channels", "0").toUint();
            size_t nUVWs = fDeltas.getSize() * fNumUVWChans;
            if (child->countChildren() != nUVWs)
                throw pfPrcParseException(__FILE__, __LINE__, "UVW count mismatch");
            fUVWs = new hsVector3[nUVWs];
            const pfPrcTag* subchild = child->getFirstChild();
            for (size_t i=0; i<nUVWs; i++) {
                fUVWs[i].prcParse(subchild);
                subchild = subchild->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}


/* plMorphDelta */
plMorphDelta::plMorphDelta() : fWeight(0.0f) { }

void plMorphDelta::read(hsStream* S, plResManager* mgr) {
    fWeight = S->readFloat();
    fSpans.setSize(S->readInt());
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i].read(S);
}

void plMorphDelta::write(hsStream* S, plResManager* mgr) {
    S->writeFloat(fWeight);
    S->writeInt(fSpans.getSize());
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i].write(S);
}

void plMorphDelta::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Weight");
    prc->writeParam("value", fWeight);
    prc->endTag(true);

    prc->writeSimpleTag("Spans");
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i].prcWrite(prc);
    prc->closeTag();
}

void plMorphDelta::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Weight") {
        fWeight = tag->getParam("value", "0").toFloat();
    } else if (tag->getName() == "Spans") {
        fSpans.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSpans.getSize(); i++) {
            fSpans[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
