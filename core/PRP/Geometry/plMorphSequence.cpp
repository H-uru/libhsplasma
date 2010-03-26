#include "plMorphSequence.h"

plMorphSequence::plMorphSequence() { }
plMorphSequence::~plMorphSequence() { }

IMPLEMENT_CREATABLE(plMorphSequence, kMorphSequence, plSingleModifier)

void plMorphSequence::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fMorphs.setSize(S->readInt());
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].read(S, mgr);

    fSharedMeshes.setSize(S->readInt());
    for (size_t i=0; i<fSharedMeshes.getSize(); i++)
        fSharedMeshes[i] = mgr->readKey(S);
}

void plMorphSequence::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fMorphs.getSize());
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].write(S, mgr);

    S->writeInt(fSharedMeshes.getSize());
    for (size_t i=0; i<fSharedMeshes.getSize(); i++)
        mgr->writeKey(S, fSharedMeshes[i]);
}

void plMorphSequence::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Morphs");
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SharedMeshes");
    for (size_t i=0; i<fSharedMeshes.getSize(); i++)
        fSharedMeshes[i]->prcWrite(prc);
    prc->closeTag();
}

void plMorphSequence::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Morphs") {
        size_t count = tag->countChildren();
        fMorphs.setSize(count);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<count; i++) {
            fMorphs[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SharedMeshes") {
        size_t count = tag->countChildren();
        fSharedMeshes.setSize(count);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<count; i++) {
            fSharedMeshes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
