#include "plRandomCommandMod.h"

plRandomCommandMod::plRandomCommandMod()
                  : fState(0), fMode(0), fMinDelay(0.0f), fMaxDelay(0.0f) { }

void plRandomCommandMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fMode = S->readByte();
    fState = S->readByte();
    fMinDelay = S->readFloat();
    fMaxDelay = S->readFloat();
}

void plRandomCommandMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeByte(fMode);
    S->writeByte(fState);
    S->writeFloat(fMinDelay);
    S->writeFloat(fMaxDelay);
}

void plRandomCommandMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("RandomCommandParams");
    prc->writeParam("Mode", fMode);
    prc->writeParam("State", fState);
    prc->writeParam("MinDelay", fMinDelay);
    prc->writeParam("MaxDelay", fMaxDelay);
    prc->endTag(true);
}

void plRandomCommandMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "RandomCommandParams") {
        fMode = tag->getParam("Mode", "0").toUint();
        fState = tag->getParam("State", "0").toUint();
        fMinDelay = tag->getParam("MinDelay", "0").toFloat();
        fMaxDelay = tag->getParam("MaxDelay", "0").toFloat();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
