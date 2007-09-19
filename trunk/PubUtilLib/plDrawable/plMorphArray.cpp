#include "plMorphArray.h"

plMorphArray::plMorphArray() { }
plMorphArray::~plMorphArray() { }

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
    prc->writeSimpleTag("Deltas");
    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].prcWrite(prc);
    prc->closeTag();
}
