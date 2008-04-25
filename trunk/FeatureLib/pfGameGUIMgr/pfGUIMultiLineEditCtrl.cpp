#include "pfGUIMultiLineEditCtrl.h"

pfGUIMultiLineEditCtrl::pfGUIMultiLineEditCtrl() { }
pfGUIMultiLineEditCtrl::~pfGUIMultiLineEditCtrl() { }

IMPLEMENT_CREATABLE(pfGUIMultiLineEditCtrl, kGUIMultiLineEditCtrl, pfGUIControlMod)

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

    prc->writeSimpleTag("ScrollCtrl");
    fScrollCtrl->prcWrite(prc);
    prc->closeTag();
}
