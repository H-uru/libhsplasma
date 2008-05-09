#include "plMorphDataSet.h"

plMorphDataSet::plMorphDataSet() { }
plMorphDataSet::~plMorphDataSet() { }

IMPLEMENT_CREATABLE(plMorphDataSet, kMorphDataSet, hsKeyedObject)

void plMorphDataSet::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fMorphs.setSize(S->readInt());
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].read(S, mgr);
}

void plMorphDataSet::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fMorphs.getSize());
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].write(S, mgr);
}

void plMorphDataSet::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Morphs");
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].prcWrite(prc);
    prc->closeTag();
}

void plMorphDataSet::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Morphs") {
        fMorphs.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMorphs.getSize(); i++) {
            fMorphs[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
