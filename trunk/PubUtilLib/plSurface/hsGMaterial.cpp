#include "hsGMaterial.h"
#include "../plResMgr/plResManager.h"

hsGMaterial::hsGMaterial(PlasmaVer pv) { }
hsGMaterial::~hsGMaterial() { }

short hsGMaterial::ClassIndex() { return 0x0007; }

void hsGMaterial::read(hsStream *S) {
    plSynchedObject::read(S);
    readData(S);

    int i;
    for (i=0; i<Layers.getSize(); i++) {
        Layers[i] = plResManager::inst->readKey(S);
        Layers[i]->Ref();
    }
    for (i=0; i<PiggyBacks.getSize(); i++) {
        PiggyBacks[i] = plResManager::inst->readKey(S);
        PiggyBacks[i]->Ref();
    }
}

void hsGMaterial::write(hsStream *S) {
    plSynchedObject::write(S);
    writeData(S);

    int i;
    for (i=0; i<Layers.getSize(); i++)
        plResManager::inst->writeKey(S, Layers[i]);
    for (i=0; i<PiggyBacks.getSize(); i++)
        plResManager::inst->writeKey(S, PiggyBacks[i]);
}

void hsGMaterial::readData(hsStream *S) {
    loadFlags = S->readInt();
    compFlags = S->readInt();
    Layers.clear();
    PiggyBacks.clear();
    Layers.setSize(S->readInt());
    PiggyBacks.setSize(S->readInt());
}

void hsGMaterial::writeData(hsStream *S) {
    S->writeInt(loadFlags);
    S->writeInt(compFlags);
    S->writeInt(Layers.getSize());
    S->writeInt(PiggyBacks.getSize());
}
