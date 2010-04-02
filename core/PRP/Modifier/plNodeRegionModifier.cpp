#include "plNodeRegionModifier.h"

plNodeRegionModifier::plNodeRegionModifier() : fEnabled(true) { }

void plNodeRegionModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);
    fEnabled = S->readBool();
}

void plNodeRegionModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);
    S->writeBool(fEnabled);
}

void plNodeRegionModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("NodeRegionParams");
    prc->writeParam("Enabled", fEnabled);
    prc->endTag(true);
}

void plNodeRegionModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "NodeRegionParams") {
        fEnabled = tag->getParam(fEnabled, "true").toBool();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
