#include "plPostEffectMod.h"

plPostEffectMod::plPostEffectMod()
               : fHither(1.0f), fYon(100.0f), fFovX(0.7854f), fFovY(0.589f) { }
plPostEffectMod::~plPostEffectMod() { }

IMPLEMENT_CREATABLE(plPostEffectMod, kPostEffectMod, plSingleModifier)

void plPostEffectMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fState.read(S);
    fHither = S->readFloat();
    fYon = S->readFloat();
    fFovX = S->readFloat();
    fFovY = S->readFloat();

    fNodeKey = mgr->readKey(S);
    fDefaultW2C.read(S);
    fDefaultC2W.read(S);
}

void plPostEffectMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    fState.write(S);
    S->writeFloat(fHither);
    S->writeFloat(fYon);
    S->writeFloat(fFovX);
    S->writeFloat(fFovY);

    mgr->writeKey(S, fNodeKey);
    fDefaultW2C.write(S);
    fDefaultC2W.write(S);
}

void plPostEffectMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("State");
    fState.prcWrite(prc);
    prc->closeTag();

    prc->startTag("View");
    prc->writeParam("Hither", fHither);
    prc->writeParam("Yon", fYon);
    prc->writeParam("FovX", fFovX);
    prc->writeParam("FovY", fFovY);
    prc->endTag(true);

    prc->writeSimpleTag("SceneNode");
    fNodeKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("DefaultW2C");
    fDefaultW2C.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DefaultC2W");
    fDefaultC2W.prcWrite(prc);
    prc->closeTag();
}

void plPostEffectMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "State") {
        if (tag->hasChildren())
            fState.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "View") {
        fHither = tag->getParam("Hither", "0").toFloat();
        fYon = tag->getParam("Yon", "0").toFloat();
        fFovX = tag->getParam("FovX", "0").toFloat();
        fFovY = tag->getParam("FovY", "0").toFloat();
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fNodeKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DefaultW2C") {
        if (tag->hasChildren())
            fDefaultW2C.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DefaultC2W") {
        if (tag->hasChildren())
            fDefaultC2W.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
