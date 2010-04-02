#include "plMorphArray.h"

void plMorphArray::read(hsStream* S, plResManager* mgr) {
    fDeltas.setSize(S->readInt());
    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].read(S, mgr);
}

void plMorphArray::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fDeltas.getSize());
    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].write(S, mgr);
}

void plMorphArray::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plMorphArray");
    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].prcWrite(prc);
    prc->closeTag();
}

void plMorphArray::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "plMorphArray")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fDeltas.setSize(tag->countChildren());
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fDeltas.getSize(); i++) {
        fDeltas[i].prcParse(child, mgr);
        child = child->getNextSibling();
    }
}
