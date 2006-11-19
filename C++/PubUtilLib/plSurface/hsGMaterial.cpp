#include "hsGMaterial.h"

hsGMaterial::hsGMaterial() : Unknown(0), LayerFlags(0) { }
hsGMaterial::~hsGMaterial() { }

void hsGMaterial::read(hsStream *S) {
    plSynchedObject::read(S);

    Unknown = S->readInt();
    LayerFlags = S->readInt();
    int l1Count = S->readInt();
    int l2Count = S->readInt();

    int i;
    Layers1.clear();
    Layers1.ensureCap(l1Count);
    for (i=0; i<l1Count; i++)
        Layers1.addNew()->readRef(S);
    Layers2.clear();
    Layers2.ensureCap(l2Count);
    for (i=0; i<l2Count; i++)
        Layers2.addNew()->readRef(S);
}

void hsGMaterial::write(hsStream *S) {
    plSynchedObject::write(S);

    S->writeInt(Unknown);
    S->writeInt(LayerFlags);
    S->writeInt(Layers1.getSize());
    S->writeInt(Layers2.getSize());

    int i;
    for (i=0; i<Layers1.getSize(); i++)
        Layers1[i]->write(S);
    for (i=0; i<Layers2.getSize(); i++)
        Layers2[i]->write(S);
}

