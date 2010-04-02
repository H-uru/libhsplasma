#include "plLinkEffectsTriggerMsg.h"

plLinkEffectsTriggerMsg::plLinkEffectsTriggerMsg() 
                       : fInvisLevel(0), fEffects(0), fLeavingAge(false) { }

void plLinkEffectsTriggerMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fInvisLevel = S->readInt();
    fLeavingAge = S->readBool();
    fLinkKey = mgr->readKey(S);
    fEffects = S->readInt();
    fLinkInAnimKey = mgr->readKey(S);
}

void plLinkEffectsTriggerMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeInt(fInvisLevel);
    S->writeBool(fLeavingAge);
    mgr->writeKey(S, fLinkKey);
    S->writeInt(fEffects);
    mgr->writeKey(S, fLinkInAnimKey);
}

void plLinkEffectsTriggerMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("LinkEffectsTriggerParams");
    prc->writeParam("InvisLevel", fInvisLevel);
    prc->writeParam("Effects", fEffects);
    prc->writeParam("LeavingAge", fLeavingAge);
    prc->endTag(true);

    prc->writeSimpleTag("LinkKey");
    fLinkKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LinkInAnimKey");
    fLinkInAnimKey->prcWrite(prc);
    prc->closeTag();
}

void plLinkEffectsTriggerMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LinkEffectsTriggerParams") {
        fInvisLevel = tag->getParam("InvisLevel", "0").toUint();
        fEffects = tag->getParam("Effects", "0").toUint();
        fLeavingAge = tag->getParam("LeavingAge", "False").toBool();
    } else if (tag->getName() == "LinkKey") {
        if (tag->hasChildren())
            fLinkKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "LinkInAnimKey") {
        if (tag->hasChildren())
            fLinkInAnimKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
