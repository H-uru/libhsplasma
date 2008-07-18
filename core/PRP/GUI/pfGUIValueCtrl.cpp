#include "pfGUIValueCtrl.h"

pfGUIValueCtrl::pfGUIValueCtrl()
              : fMin(0.0f), fMax(0.0f), fStep(0.0f) { }

pfGUIValueCtrl::~pfGUIValueCtrl() { }

IMPLEMENT_CREATABLE(pfGUIValueCtrl, kGUIValueCtrl, pfGUIControlMod)

void pfGUIValueCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fMin = S->readFloat();
    fMax = S->readFloat();
    fStep = S->readFloat();
}

void pfGUIValueCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeFloat(fMin);
    S->writeFloat(fMax);
    S->writeFloat(fStep);
}

void pfGUIValueCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("ValueParams");
    prc->writeParam("Min", fMin);
    prc->writeParam("Max", fMax);
    prc->writeParam("Step", fStep);
    prc->endTag(true);
}

void pfGUIValueCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ValueParams") {
        fMin = tag->getParam("Min", "0").toFloat();
        fMax = tag->getParam("Max", "0").toFloat();
        fStep = tag->getParam("Step", "0").toFloat();
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
