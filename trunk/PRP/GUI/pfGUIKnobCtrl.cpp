#include "pfGUIKnobCtrl.h"

pfGUIKnobCtrl::pfGUIKnobCtrl()
             : fDragValue(0.0f), fDragging(false), fDragRangeMin(0.0f),
               fDragRangeMax(0.0f), fAnimBegin(0.0f), fAnimEnd(0.0f),
               fAnimTimesCalced(false) {
    fFlags.setName(kReverseValues, "kReverseValues");
    fFlags.setName(kLeftRightOrientation, "kLeftRightOrientation");
    fFlags.setName(kMapToScreenRange, "kMapToScreenRange");
    fFlags.setName(kTriggerOnlyOnMouseUp, "kTriggerOnlyOnMouseUp");
    fFlags.setName(kMapToAnimationRange, "kMapToAnimationRange");
}

pfGUIKnobCtrl::~pfGUIKnobCtrl() { }

IMPLEMENT_CREATABLE(pfGUIKnobCtrl, kGUIKnobCtrl, pfGUIValueCtrl)

void pfGUIKnobCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::read(S, mgr);

    fAnimationKeys.setSize(S->readInt());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i] = mgr->readKey(S);

    fAnimName = S->readSafeStr();
    fAnimStartPos.read(S);
    fAnimEndPos.read(S);
    fAnimTimesCalced = false;
}

void pfGUIKnobCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::write(S, mgr);

    S->writeInt(fAnimationKeys.getSize());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        mgr->writeKey(S, fAnimationKeys[i]);

    S->writeSafeStr(fAnimName);
    fAnimStartPos.write(S);
    fAnimEndPos.write(S);
}

void pfGUIKnobCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIValueCtrl::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->endTag();
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("AnimStartPos");
    fAnimStartPos.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("AnimEndPos");
    fAnimEndPos.prcWrite(prc);
    prc->closeTag();
}

void pfGUIKnobCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fAnimationKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimationKeys.getSize(); i++) {
            fAnimationKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "AnimStartPos") {
        if (tag->hasChildren())
            fAnimStartPos.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "AnimEndPos") {
        if (tag->hasChildren())
            fAnimEndPos.prcParse(tag->getFirstChild());
    } else {
        pfGUIValueCtrl::IPrcParse(tag, mgr);
    }
}
