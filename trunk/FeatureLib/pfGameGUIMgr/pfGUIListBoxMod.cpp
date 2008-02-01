#include "pfGUIListBoxMod.h"

/* pfScrollProc */
pfScrollProc::pfScrollProc(pfGUIListBoxMod* parent) : fParent(parent) { }

void pfScrollProc::DoSomething(pfGUIControlMod* ctrl) {
    //TODO: Scroll...
}

/* pfGUIListElement */
pfGUIListElement::pfGUIListElement()
                : fSelected(false), fCollapsed(false), fType(kText),
                  fIndentLevel(0), fColors(NULL), fSkin(NULL) { }

pfGUIListElement::~pfGUIListElement() { }

void pfGUIListElement::read(hsStream* S) {
    fSelected = S->readBool();
}

void pfGUIListElement::write(hsStream* S) {
    S->writeBool(fSelected);
}

void pfGUIListElement::prcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUIListElement");
    prc->writeParam("Selected", fSelected);
    prc->endTag(true);
}


/* pfGUIListBoxMod */
pfGUIListBoxMod::pfGUIListBoxMod()
               : fScrollProc(NULL), fCurrClick(0), fScrollPos(0), fCurrHover(0),
                 fModsAtDragTime(0), fMinSel(0), fMaxSel(0), fCheckSel(false),
                 fClicking(false), fSingleSelElement(0), fLocked(false),
                 fReadyToRoll(false) {
    fFlags.setName(kSingleSelect, "kSingleSelect");
    fFlags.setName(kDragAndDropCapable, "kDragAndDropCapable");
    fFlags.setName(kDisableSelection, "kDisableSelection");
    fFlags.setName(kDisableKeyActions, "kDisableKeyActions");
    fFlags.setName(kAllowMultipleElementsPerRow, "kAllowMultipleElementsPerRow");
    fFlags.setName(kScrollLeftToRight, "kScrollLeftToRight");
    fFlags.setName(kAllowMousePassThrough, "kAllowMousePassThrough");
    fFlags.setName(kGrowLeavesAndProcessOxygen, "kGrowLeavesAndProcessOxygen");
    fFlags.setName(kHandsOffMultiSelect, "kHandsOffMultiSelect");
    fFlags.setName(kForbidNoSelection, "kForbidNoSelection");
}

pfGUIListBoxMod::~pfGUIListBoxMod() {
    if (fScrollProc) delete fScrollProc;
}

IMPLEMENT_CREATABLE(pfGUIListBoxMod, kGUIListBoxMod, pfGUIControlMod)

void pfGUIListBoxMod::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    if (fScrollProc != NULL)
        delete fScrollProc;
    if (S->readBool()) {
        fScrollProc = new pfScrollProc(this);
        fScrollCtrl = mgr->readKey(S);
    }

    if (fFlags[kAllowMultipleElementsPerRow])
        fFlags.clearBit(kWantsInterest);
}

void pfGUIListBoxMod::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    if (fScrollCtrl.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fScrollCtrl);
    } else {
        S->writeBool(false);
    }
}

void pfGUIListBoxMod::prcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::prcWrite(prc);

    prc->writeSimpleTag("ScrollControl");
    fScrollCtrl->prcWrite(prc);
    prc->closeTag();
}
