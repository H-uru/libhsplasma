#include "plWaveSet7.h"

plWaveSet7::plWaveSet7() : fMaxLen(0.0f) {
    fFlags.setName(kHasRefObject, "kHasRefObject");
}

plWaveSet7::~plWaveSet7() { }

IMPLEMENT_CREATABLE(plWaveSet7, kWaveSet7, plWaveSetBase)

void plWaveSet7::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    fMaxLen = S->readFloat();
    fState.read(S);

    fShores.setSize(S->readInt());
    for (size_t i=0; i<fShores.getSize(); i++)
        fShores[i] = mgr->readKey(S);
    fDecals.setSize(S->readInt());
    for (size_t i=0; i<fDecals.getSize(); i++)
        fDecals[i] = mgr->readKey(S);
    fEnvMap = mgr->readKey(S);
    if (fFlags[kHasRefObject])
        fRefObj = mgr->readKey(S);
}

void plWaveSet7::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);

    S->writeFloat(fMaxLen);
    fState.write(S);

    S->writeInt(fShores.getSize());
    for (size_t i=0; i<fShores.getSize(); i++)
        mgr->writeKey(S, fShores[i]);
    S->writeInt(fDecals.getSize());
    for (size_t i=0; i<fDecals.getSize(); i++)
        mgr->writeKey(S, fDecals[i]);
    mgr->writeKey(S, fEnvMap);
    if (fFlags[kHasRefObject])
        mgr->writeKey(S, fRefObj);
}

void plWaveSet7::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("WaveSet7Params");
    prc->writeParam("MaxLen", fMaxLen);
    prc->endTag(true);

    fState.prcWrite(prc);

    prc->writeSimpleTag("Shores");
    for (size_t i=0; i<fShores.getSize(); i++)
        fShores[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Decals");
    for (size_t i=0; i<fDecals.getSize(); i++)
        fDecals[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("EnvMap");
    fEnvMap->prcWrite(prc);
    prc->closeTag();

    if (fFlags[kHasRefObject]) {
        prc->writeSimpleTag("RefObject");
        fRefObj->prcWrite(prc);
        prc->closeTag();
    }
}
