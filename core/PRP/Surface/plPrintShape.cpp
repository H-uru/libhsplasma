#include "plPrintShape.h"

/* plPrintShape */
plPrintShape::plPrintShape() : fWidth(0.0f), fLength(0.0f), fHeight(0.0f) { }

void plPrintShape::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fWidth = S->readFloat();
    fLength = S->readFloat();
    fHeight = S->readFloat();
}

void plPrintShape::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    S->writeFloat(fWidth);
    S->writeFloat(fLength);
    S->writeFloat(fHeight);
}

void plPrintShape::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->startTag("Dimensions");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Length", fLength);
    prc->writeParam("Height", fHeight);
    prc->endTag(true);
}

void plPrintShape::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Dimensions") {
        fWidth = tag->getParam("Width", "0").toFloat();
        fLength = tag->getParam("Length", "0").toFloat();
        fHeight = tag->getParam("Height", "0").toFloat();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}


/* plActivePrintShape */
void plActivePrintShape::read(hsStream* S, plResManager* mgr) {
    plPrintShape::read(S, mgr);

    fDecalMgrs.setSize(S->readInt());
    for (size_t i=0; i<fDecalMgrs.getSize(); i++)
        fDecalMgrs[i] = mgr->readKey(S);
}

void plActivePrintShape::write(hsStream* S, plResManager* mgr) {
    plPrintShape::write(S, mgr);

    S->writeInt(fDecalMgrs.getSize());
    for (size_t i=0; i<fDecalMgrs.getSize(); i++)
        mgr->writeKey(S, fDecalMgrs[i]);
}

void plActivePrintShape::IPrcWrite(pfPrcHelper* prc) {
    plPrintShape::IPrcWrite(prc);

    prc->writeSimpleTag("DecalMgrs");
    for (size_t i=0; i<fDecalMgrs.getSize(); i++)
        fDecalMgrs[i]->prcWrite(prc);
    prc->closeTag();
}

void plActivePrintShape::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DecalMgrs") {
        fDecalMgrs.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDecalMgrs.getSize(); i++) {
            fDecalMgrs[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plPrintShape::IPrcParse(tag, mgr);
    }
}
