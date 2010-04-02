#include "pfGUIMultiLineEditCtrl.h"

void pfGUIMultiLineEditCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    if (S->readBool())
        fScrollCtrl = mgr->readKey(S);
}

void pfGUIMultiLineEditCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    if (fScrollCtrl.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fScrollCtrl);
    } else {
        S->writeBool(false);
    }
}

void pfGUIMultiLineEditCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("ScrollControl");
    fScrollCtrl->prcWrite(prc);
    prc->closeTag();
}

void pfGUIMultiLineEditCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ScrollControl") {
        if (tag->hasChildren())
            fScrollCtrl = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
