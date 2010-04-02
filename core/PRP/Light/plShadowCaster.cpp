#include "plShadowCaster.h"

plShadowCaster::plShadowCaster()
              : fCastFlags(0), fBoost(0.0f), fAttenScale(0.0f),
                fBlurScale(0.0f), fMaxOpacity(0.0f) { }

void plShadowCaster::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    fCastFlags = S->readByte();
    fBoost = S->readFloat();
    fAttenScale = S->readFloat();
    fBlurScale = S->readFloat();
}

void plShadowCaster::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);

    S->writeByte(fCastFlags);
    S->writeFloat(fBoost);
    S->writeFloat(fAttenScale);
    S->writeFloat(fBlurScale);
}

void plShadowCaster::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("CastParams");
    prc->writeParamHex("Flags", fCastFlags);
    prc->writeParam("Boost", fBoost);
    prc->writeParam("AttenScale", fAttenScale);
    prc->writeParam("BlurScale", fBlurScale);
    prc->endTag(true);
}

void plShadowCaster::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CastParams") {
        fCastFlags = tag->getParam("Flags", "0").toUint();
        fBoost = tag->getParam("Boost", "0").toFloat();
        fAttenScale = tag->getParam("AttenScale", "0").toFloat();
        fBlurScale = tag->getParam("BlurScale", "0").toFloat();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
