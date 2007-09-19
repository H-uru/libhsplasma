#include "hsGMaterial.h"
#include "../plResMgr/plResManager.h"

hsGMaterial::hsGMaterial() { }
hsGMaterial::~hsGMaterial() { }

IMPLEMENT_CREATABLE(hsGMaterial, kGMaterial, plSynchedObject)

void hsGMaterial::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    readData(S);

    size_t i;
    for (i=0; i<Layers.getSize(); i++)
        Layers[i] = mgr->readKey(S);
    for (i=0; i<PiggyBacks.getSize(); i++)
        PiggyBacks[i] = mgr->readKey(S);
}

void hsGMaterial::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    writeData(S);

    size_t i;
    for (i=0; i<Layers.getSize(); i++)
        mgr->writeKey(S, Layers[i]);
    for (i=0; i<PiggyBacks.getSize(); i++)
        mgr->writeKey(S, PiggyBacks[i]);
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

void hsGMaterial::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->startTag("LoadFlags");
    prc->writeParam("value", loadFlags);
    prc->endTag(true);
    prc->startTag("CompFlags");
    prc->writeParam("value", compFlags);
    prc->endTag(true);

    size_t i;
    prc->writeSimpleTag("Layers");
    for (i=0; i<Layers.getSize(); i++)
        Layers[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PiggyBacks");
    for (i=0; i<PiggyBacks.getSize(); i++)
        PiggyBacks[i]->prcWrite(prc);
    prc->closeTag();
}
