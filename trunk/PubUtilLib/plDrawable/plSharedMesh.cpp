#include "plSharedMesh.h"
#include "../plResMgr/plResManager.h"

plSharedMesh::plSharedMesh() : fMorphSet(NULL), fFlags(kDontSaveMorphState) { }
plSharedMesh::~plSharedMesh() { }

IMPLEMENT_CREATABLE(plSharedMesh, kSharedMesh, hsKeyedObject)

void plSharedMesh::read(hsStream* S) {
    hsKeyedObject::read(S);

    fSpans.setSize(S->readInt());
    for (size_t i=0; i<fSpans.getSize(); i++) {
        fSpans[i] = new plGeometrySpan();
        fSpans[i]->read(S);
    }
    fMorphSet = plResManager::inst->readKey(S);
    fFlags = S->readByte();
}

void plSharedMesh::write(hsStream* S) {
    hsKeyedObject::write(S);

    S->writeInt(fSpans.getSize());
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i]->write(S);
    plResManager::inst->writeKey(S, fMorphSet);
    S->writeByte(fFlags);
}

void plSharedMesh::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->writeSimpleTag("Spans");
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MorphSet");
    fMorphSet->prcWrite(prc);
    prc->closeTag();
    prc->startTag("Flags");
    prc->writeParam("value", fFlags);
    prc->endTag(true);
}
