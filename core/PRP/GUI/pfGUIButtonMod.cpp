#include "pfGUIButtonMod.h"

/* pfGUIButtonMod */
pfGUIButtonMod::pfGUIButtonMod()
              : fNotifyType(0), fEoaUnknown1(0), fEoaUnknown2(0) { }

pfGUIButtonMod::~pfGUIButtonMod() { }

IMPLEMENT_CREATABLE(pfGUIButtonMod, kGUIButtonMod, pfGUIControlMod)

void pfGUIButtonMod::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fAnimationKeys.setSize(S->readInt());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i] = mgr->readKey(S);
    fAnimName = S->readSafeStr();

    fMouseOverAnimKeys.setSize(S->readInt());
    for (size_t i=0; i<fMouseOverAnimKeys.getSize(); i++)
        fMouseOverAnimKeys[i] = mgr->readKey(S);
    fMouseOverAnimName = S->readSafeStr();

    fNotifyType = S->readInt();
    if (S->getVer() >= pvEoa) {
        fEoaUnknown1 = S->readInt();
        fEoaUnknown2 = S->readInt();
    }
    fDraggable = mgr->readKey(S);
}

void pfGUIButtonMod::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fAnimationKeys.getSize());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        mgr->writeKey(S, fAnimationKeys[i]);
    S->writeSafeStr(fAnimName);

    S->writeInt(fMouseOverAnimKeys.getSize());
    for (size_t i=0; i<fMouseOverAnimKeys.getSize(); i++)
        mgr->writeKey(S, fMouseOverAnimKeys[i]);
    S->writeSafeStr(fMouseOverAnimName);

    S->writeInt(fNotifyType);
    if (S->getVer() >= pvEoa) {
        S->writeInt(fEoaUnknown1);
        S->writeInt(fEoaUnknown2);
    }
    mgr->writeKey(S, fDraggable);
}

void pfGUIButtonMod::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->endTag();
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("MouseOverAnimation");
    prc->writeParam("Name", fMouseOverAnimName);
    prc->endTag();
    for (size_t i=0; i<fMouseOverAnimKeys.getSize(); i++)
        fMouseOverAnimKeys[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("NotifyType");
    prc->writeParam("value", fNotifyType);
    prc->endTag(true);

    prc->writeSimpleTag("Draggable");
    fDraggable->prcWrite(prc);
    prc->closeTag();
}

void pfGUIButtonMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fAnimationKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimationKeys.getSize(); i++) {
            fAnimationKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MouseOverAnimation") {
        fMouseOverAnimName = tag->getParam("Name", "");
        fMouseOverAnimKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMouseOverAnimKeys.getSize(); i++) {
            fMouseOverAnimKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "NotifyType") {
        fNotifyType = tag->getParam("value", "0").toInt();
    } else if (tag->getName() == "Draggable") {
        if (tag->hasChildren())
            fDraggable = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}

size_t pfGUIButtonMod::getNumAnimationKeys() const { return fAnimationKeys.getSize(); }
plKey pfGUIButtonMod::getAnimationKey(size_t idx) const { return fAnimationKeys[idx]; }
void pfGUIButtonMod::addAnimationKey(plKey key) { fAnimationKeys.append(key); }
void pfGUIButtonMod::delAnimationKey(size_t idx) { fAnimationKeys.remove(idx); }
void pfGUIButtonMod::clearAnimationKeys() { fAnimationKeys.clear(); }

size_t pfGUIButtonMod::getNumMouseOverKeys() const { return fMouseOverAnimKeys.getSize(); }
plKey pfGUIButtonMod::getMouseOverKey(size_t idx) const { return fMouseOverAnimKeys[idx]; }
void pfGUIButtonMod::addMouseOverKey(plKey key) { fMouseOverAnimKeys.append(key); }
void pfGUIButtonMod::delMouseOverKey(size_t idx) { fMouseOverAnimKeys.remove(idx); }
void pfGUIButtonMod::clearMouseOverKeys() { fMouseOverAnimKeys.clear(); }

const plString& pfGUIButtonMod::getAnimationName() const { return fAnimName; }
const plString& pfGUIButtonMod::getMouseOverAnimName() const { return fMouseOverAnimName; }
plKey pfGUIButtonMod::getDraggable() const { return fDraggable; }
int pfGUIButtonMod::getNotifyType() const { return fNotifyType; }

void pfGUIButtonMod::setAnimationName(const plString& name) { fAnimName = name; }
void pfGUIButtonMod::setMouseOverAnimName(const plString& name) { fMouseOverAnimName = name; }
void pfGUIButtonMod::setDraggable(plKey draggable) { fDraggable = draggable; }
void pfGUIButtonMod::setNotifyType(int type) { fNotifyType = type; }


/* pfGUIMenuItem */
pfGUIMenuItem::pfGUIMenuItem() {
    fFlags.setName(kDrawSubMenuArrow, "kDrawSubMenuArrow");
    fFlags.setName(kReportHovers, "kReportHovers");
}

IMPLEMENT_CREATABLE(pfGUIMenuItem, kGUIMenuItem, pfGUIButtonMod)
