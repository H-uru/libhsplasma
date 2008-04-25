#include "pfGUIUpDownPairMod.h"
#include "pfGUIButtonMod.h"

pfGUIUpDownPairMod::pfGUIUpDownPairMod() { }
pfGUIUpDownPairMod::~pfGUIUpDownPairMod() { }

IMPLEMENT_CREATABLE(pfGUIUpDownPairMod, kGUIUpDownPairMod, pfGUIValueCtrl)

void pfGUIUpDownPairMod::read(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::read(S, mgr);

    fUpControl = mgr->readKey(S);
    fDownControl = mgr->readKey(S);
    fMin = S->readFloat();  // Seriously...
    fMax = S->readFloat();
    fStep = S->readFloat();
}

void pfGUIUpDownPairMod::write(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::write(S, mgr);

    mgr->writeKey(S, fUpControl);
    mgr->writeKey(S, fDownControl);
    S->writeFloat(fMin);
    S->writeFloat(fMax);
    S->writeFloat(fStep);
}

void pfGUIUpDownPairMod::IPrcWrite(pfPrcHelper* prc) {
    pfGUIValueCtrl::IPrcWrite(prc);

    prc->writeSimpleTag("UpControl");
    fUpControl->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DownControl");
    fDownControl->prcWrite(prc);
    prc->closeTag();
}
