#include "plMorphDataSet.h"

plMorphDataSet::plMorphDataSet() { }
plMorphDataSet::~plMorphDataSet() { }

IMPLEMENT_CREATABLE(plMorphDataSet, kMorphDataSet, hsKeyedObject)

void plMorphDataSet::read(hsStream* S) {
    hsKeyedObject::read(S);

    fMorphs.setSize(S->readInt());
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].read(S);
}

void plMorphDataSet::write(hsStream* S) {
    hsKeyedObject::write(S);

    S->writeInt(fMorphs.getSize());
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].write(S);
}

void plMorphDataSet::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->writeSimpleTag("Morphs");
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].prcWrite(prc);
    prc->closeTag();
}
