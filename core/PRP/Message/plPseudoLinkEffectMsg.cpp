#include "plPseudoLinkEffectMsg.h"

plPseudoLinkEffectMsg::plPseudoLinkEffectMsg() {
    fBCastFlags |= (kNetPropagate | kBCastByExactType);
}

void plPseudoLinkEffectMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fLinkObjKey = mgr->readKey(S);
    fAvatarKey = mgr->readKey(S);
}

void plPseudoLinkEffectMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    mgr->writeKey(S, fLinkObjKey);
    mgr->writeKey(S, fAvatarKey);
}

void plPseudoLinkEffectMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("LinkObject");
    fLinkObjKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Avatar");
    fAvatarKey->prcWrite(prc);
    prc->closeTag();
}

void plPseudoLinkEffectMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LinkObject") {
        if (tag->hasChildren())
            fLinkObjKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Avatar") {
        if (tag->hasChildren())
            fAvatarKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
