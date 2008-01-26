#include "plRandomCommandMod.h"

plRandomCommandMod::plRandomCommandMod()
                  : fState(0), fMode(0), fCurrent(0),
                    fMinDelay(0.0f), fMaxDelay(0.0f) { }

plRandomCommandMod::~plRandomCommandMod() { }

IMPLEMENT_CREATABLE(plRandomCommandMod, kRandomCommandMod, plSingleModifier)

void plRandomCommandMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fMode = S->readByte();
    fState = S->readByte();
    fMinDelay = S->readFloat();
    fMaxDelay = S->readFloat();
    fCurrent = -1;
}

void plRandomCommandMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeByte(fMode);
    S->writeByte(fState);
    S->writeFloat(fMinDelay);
    S->writeFloat(fMaxDelay);
}

void plRandomCommandMod::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("RandomCommandParams");
    prc->writeParam("Mode", fMode);
    prc->writeParam("State", fState);
    prc->writeParam("MinDelay", fMinDelay);
    prc->writeParam("MaxDelay", fMaxDelay);
    prc->endTag(true);
}
