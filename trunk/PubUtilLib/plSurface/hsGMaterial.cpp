#include "hsGMaterial.h"
#include "../plResMgr/plResManager.h"

hsGMaterial::hsGMaterial(PlasmaVer pv) : Unknown(0), LayerFlags(0) { }
hsGMaterial::~hsGMaterial() { }

unsigned short hsGMaterial::ClassIndex() { return 0x0007; }

void hsGMaterial::read(hsStream *S) {
    plSynchedObject::read(S);

    Unknown = S->readInt();
    LayerFlags = S->readInt();
    int l1Count = S->readInt();
    int l2Count = S->readInt();

    int i;
    Layers1.clear();
    Layers1.setSize(l1Count);
    for (i=0; i<l1Count; i++) {
        Layers1[i] = plResManager::inst->readKey(S);
        Layers1[i]->Ref();
    }
    Layers2.clear();
    Layers2.setSize(l2Count);
    for (i=0; i<l2Count; i++) {
        Layers2[i] = plResManager::inst->readKey(S);
        Layers2[i]->Ref();
    }
}

void hsGMaterial::write(hsStream *S) {
    plSynchedObject::write(S);

    S->writeInt(Unknown);
    S->writeInt(LayerFlags);
    S->writeInt(Layers1.getSize());
    S->writeInt(Layers2.getSize());

    int i;
    for (i=0; i<Layers1.getSize(); i++)
        plResManager::inst->writeKey(S, Layers1[i]);
    for (i=0; i<Layers2.getSize(); i++)
        plResManager::inst->writeKey(S, Layers2[i]);
}

