#include "plBlower.h"

plBlower::plBlower()
        : fMasterPower(0.0f), fDirectRate(0.0f), fImpulseRate(0.0f),
          fSpringKonst(0.0f) { }

plBlower::~plBlower() { }

IMPLEMENT_CREATABLE(plBlower, kBlower, plSingleModifier)

void plBlower::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fMasterPower = S->readFloat();
    fDirectRate = S->readFloat();
    fImpulseRate = S->readFloat();
    fSpringKonst = S->readFloat();
}

void plBlower::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeFloat(fMasterPower);
    S->writeFloat(fDirectRate);
    S->writeFloat(fImpulseRate);
    S->writeFloat(fSpringKonst);
}

void plBlower::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("BlowerParams");
    prc->writeParam("MasterPower", fMasterPower);
    prc->writeParam("DirectRate", fDirectRate);
    prc->writeParam("ImpulseRate", fImpulseRate);
    prc->writeParam("SpringKonst", fSpringKonst);
    prc->endTag(true);
}
