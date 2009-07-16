#include "pfGUIProgressCtrl.h"

pfGUIProgressCtrl::pfGUIProgressCtrl() {
    fFlags.setName(kReverseValues, "kReverseValues");
    fFlags.setName(kLeftRightOrientation, "kLeftRightOrientation");
    fFlags.setName(kMapToScreenRange, "kMapToScreenRange");
    fFlags.setName(kTriggerOnlyOnMouseUp, "kTriggerOnlyOnMouseUp");
    fFlags.setName(kMapToAnimationRange, "kMapToAnimationRange");
}

pfGUIProgressCtrl::~pfGUIProgressCtrl() { }

IMPLEMENT_CREATABLE(pfGUIProgressCtrl, kGUIProgressCtrl, pfGUIValueCtrl)

void pfGUIProgressCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::read(S, mgr);

    fAnimationKeys.setSize(S->readInt());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i] = mgr->readKey(S);

    fAnimName = S->readSafeStr();
}

void pfGUIProgressCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::write(S, mgr);

    S->writeInt(fAnimationKeys.getSize());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        mgr->writeKey(S, fAnimationKeys[i]);

    S->writeSafeStr(fAnimName);
}

void pfGUIProgressCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIValueCtrl::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->endTag();
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i]->prcWrite(prc);
    prc->closeTag();
}

void pfGUIProgressCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fAnimationKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimationKeys.getSize(); i++) {
            fAnimationKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIValueCtrl::IPrcParse(tag, mgr);
    }
}

size_t pfGUIProgressCtrl::getNumAnimKeys() const { return fAnimationKeys.getSize(); }
plKey pfGUIProgressCtrl::getAnimKey(size_t idx) const { return fAnimationKeys[idx]; }
void pfGUIProgressCtrl::addAnimKey(plKey key) { fAnimationKeys.append(key); }
void pfGUIProgressCtrl::delAnimKey(size_t idx) { fAnimationKeys.remove(idx); }
void pfGUIProgressCtrl::clearAnimKeys() { fAnimationKeys.clear(); }

const plString& pfGUIProgressCtrl::getAnimName() const { return fAnimName; }
void pfGUIProgressCtrl::setAnimName(const plString& name) { fAnimName = name; }
