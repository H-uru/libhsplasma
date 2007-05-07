#include "hsGMaterial.h"
#include "../plResMgr/plResManager.h"

hsGMaterial::hsGMaterial() { }
hsGMaterial::~hsGMaterial() { }

short hsGMaterial::ClassIndex() { return kGMaterial; }
short hsGMaterial::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kGMaterial, ver);
}

void hsGMaterial::read(hsStream* S) {
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

void hsGMaterial::write(hsStream* S) {
    plSynchedObject::write(S);
    writeData(S);

    int i;
    for (i=0; i<Layers.getSize(); i++)
        plResManager::inst->writeKey(S, Layers[i]);
    for (i=0; i<PiggyBacks.getSize(); i++)
        plResManager::inst->writeKey(S, PiggyBacks[i]);
}

void hsGMaterial::readData(hsStream* S) {
    loadFlags = S->readInt();
    compFlags = S->readInt();
    Layers.clear();
    PiggyBacks.clear();
    Layers.setSize(S->readInt());
    PiggyBacks.setSize(S->readInt());
}

void hsGMaterial::writeData(hsStream* S) {
    S->writeInt(loadFlags);
    S->writeInt(compFlags);
    S->writeInt(Layers.getSize());
    S->writeInt(PiggyBacks.getSize());
}

void hsGMaterial::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);

    prc->startTag("LoadFlags");
    prc->writeParam("value", loadFlags);
    prc->endTag(true);
    prc->startTag("CompFlags");
    prc->writeParam("value", compFlags);
    prc->endTag(true);

    int i;
    prc->writeSimpleTag("Layers");
    for (i=0; i<Layers.getSize(); i++)
        Layers[i]->prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("PiggyBacks");
    for (i=0; i<PiggyBacks.getSize(); i++)
        PiggyBacks[i]->prcWrite(S, prc);
    prc->closeTag();
}
