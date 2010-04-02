#include "plWaveSet.h"

/* plWaveSet6 */
void plWaveSet6::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plWaveSet6::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plWaveSet6::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);
    prc->writeComment("plWaveSet6 Not Implemented");
}

void plWaveSet6::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}


/* plWaveSet7 */
plWaveSet7::plWaveSet7() : fMaxLen(0.0f) {
    fFlags.setName(kHasRefObject, "kHasRefObject");
}

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

void plWaveSet7::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WaveSet7Params") {
        fMaxLen = tag->getParam("MaxLen", "0").toFloat();
    } else if (tag->getName() == "plFixedWaterState7") {
        fState.prcParse(tag);
    } else if (tag->getName() == "Shores") {
        fShores.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fShores.getSize(); i++) {
            fShores[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Decals") {
        fDecals.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDecals.getSize(); i++) {
            fDecals[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "EnvMap") {
        if (tag->hasChildren())
            fEnvMap = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RefObject") {
        if (tag->hasChildren())
            fRefObj = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
