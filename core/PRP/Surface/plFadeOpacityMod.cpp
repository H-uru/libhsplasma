#include "plFadeOpacityMod.h"

plFadeOpacityMod::plFadeOpacityMod() : fFadeUp(0.0f), fFadeDown(0.0f) {
    fFlags.setName(kBoundsCenter, "kBoundsCenter");
}

void plFadeOpacityMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);
    fFadeUp = S->readFloat();
    fFadeDown = S->readFloat();
}

void plFadeOpacityMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);
    S->writeFloat(fFadeUp);
    S->writeFloat(fFadeDown);
}

void plFadeOpacityMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("FadeParams");
    prc->writeParam("Up", fFadeUp);
    prc->writeParam("Down", fFadeDown);
    prc->endTag(true);
}

void plFadeOpacityMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FadeParams") {
        fFadeUp = tag->getParam("Up", "0").toFloat();
        fFadeDown = tag->getParam("Down", "0").toFloat();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
