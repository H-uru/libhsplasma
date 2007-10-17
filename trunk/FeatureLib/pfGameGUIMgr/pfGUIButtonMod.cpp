#include "pfGUIButtonMod.h"

pfGUIButtonMod::pfGUIButtonMod()
              : fClicking(false), fTriggering(false), fOrigHandler(NULL),
                fOrigReportedDrag(false), fNotifyType(0) { }

pfGUIButtonMod::~pfGUIButtonMod() { }

IMPLEMENT_CREATABLE(pfGUIButtonMod, kGUIButtonMod, pfGUIControlMod)

void pfGUIButtonMod::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fAnimationKeys.clear();
    size_t count = S->readInt();
    for (size_t i=0; i<count; i++)
        fAnimationKeys.append(mgr->readKey(S));
    fAnimName = S->readSafeStr();

    fMouseOverAnimKeys.clear();
    count = S->readInt();
    for (size_t i=0; i<count; i++)
        fMouseOverAnimKeys.append(mgr->readKey(S));
    fMouseOverAnimName = S->readSafeStr();

    fNotifyType = S->readInt();
    if (S->getVer() == pvEoa) {
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
    if (S->getVer() == pvEoa) {
        S->writeInt(fEoaUnknown1);
        S->writeInt(fEoaUnknown2);
    }
    mgr->writeKey(S, fDraggable);
}

void pfGUIButtonMod::prcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::prcWrite(prc);

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
