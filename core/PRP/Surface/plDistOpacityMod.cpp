#include "plDistOpacityMod.h"

plDistOpacityMod::plDistOpacityMod() {
    for (size_t i=0; i<4; i++)
        fDists[i] = 0.0;
}

plDistOpacityMod::~plDistOpacityMod() { }

void plDistOpacityMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);
    for (size_t i=0; i<4; i++)
        fDists[i] = S->readFloat();
}

void plDistOpacityMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);
    for (size_t i=0; i<4; i++)
        S->writeFloat(fDists[i]);
}

void plDistOpacityMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("DistOpacity");
    prc->writeParam("Dist0", fDists[0]);
    prc->writeParam("Dist1", fDists[1]);
    prc->writeParam("Dist2", fDists[2]);
    prc->writeParam("Dist3", fDists[3]);
    prc->endTag(true);
}

void plDistOpacityMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DistOpacity") {
        fDists[0] = tag->getParam("Dist0", "0").toFloat();
        fDists[1] = tag->getParam("Dist1", "0").toFloat();
        fDists[2] = tag->getParam("Dist2", "0").toFloat();
        fDists[3] = tag->getParam("Dist3", "0").toFloat();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
