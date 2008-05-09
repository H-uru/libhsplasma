#include "pfGUIListBoxMod.h"

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

void pfGUIListElement::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "pfGUIListElement")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fSelected = tag->getParam("Selected", "false").toBool();
}


/* pfGUIListBoxMod */
pfGUIListBoxMod::pfGUIListBoxMod() {
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

pfGUIListBoxMod::~pfGUIListBoxMod() { }

IMPLEMENT_CREATABLE(pfGUIListBoxMod, kGUIListBoxMod, pfGUIControlMod)

void pfGUIListBoxMod::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    if (S->readBool())
        fScrollCtrl = mgr->readKey(S);

    if (fFlags[kAllowMultipleElementsPerRow])
        fFlags[kWantsInterest] = false;
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

void pfGUIListBoxMod::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("ScrollControl");
    fScrollCtrl->prcWrite(prc);
    prc->closeTag();
}

void pfGUIListBoxMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ScrollControl") {
        if (tag->hasChildren())
            fScrollCtrl = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
