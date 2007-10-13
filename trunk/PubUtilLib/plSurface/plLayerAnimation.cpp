#include "plLayerAnimation.h"
#include "../plResMgr/plResManager.h"

/* plLayerAnimationBase */
plLayerAnimationBase::plLayerAnimationBase()
                    : fEvalTime(-1.0), fCurrentTime(-1.0f),
                      fPreshadeColorCtl(NULL), fRuntimeColorCtl(NULL),
                      fAmbientColorCtl(NULL), fSpecularColorCtl(NULL),
                      fOpacityCtl(NULL), fTransformCtl(NULL) { }

plLayerAnimationBase::~plLayerAnimationBase() {
    if (fPreshadeColorCtl) delete fPreshadeColorCtl;
    if (fRuntimeColorCtl) delete fRuntimeColorCtl;
    if (fAmbientColorCtl) delete fAmbientColorCtl;
    if (fSpecularColorCtl) delete fSpecularColorCtl;
    if (fOpacityCtl) delete fOpacityCtl;
    if (fTransformCtl) delete fTransformCtl;
}

IMPLEMENT_CREATABLE(plLayerAnimationBase, kLayerAnimationBase, plLayerInterface)

void plLayerAnimationBase::read(hsStream* S, plResManager* mgr) {
    plLayerInterface::read(S, mgr);

    fPreshadeColorCtl = plController::Convert(mgr->ReadCreatable(S));
    fRuntimeColorCtl = plController::Convert(mgr->ReadCreatable(S));
    fAmbientColorCtl = plController::Convert(mgr->ReadCreatable(S));
    fSpecularColorCtl = plController::Convert(mgr->ReadCreatable(S));
    fOpacityCtl = plController::Convert(mgr->ReadCreatable(S));
    fTransformCtl = plController::Convert(mgr->ReadCreatable(S));

    if (fOpacityCtl != NULL)
        fOwnedChannels |= kOpacity;
    if (fPreshadeColorCtl != NULL)
        fOwnedChannels |= kPreshadeColor;
    if (fRuntimeColorCtl != NULL)
        fOwnedChannels |= kRuntimeColor;
    if (fAmbientColorCtl != NULL)
        fOwnedChannels |= kAmbientColor;
    if (fSpecularColorCtl != NULL)
        fOwnedChannels |= kSpecularColor;
    if (fTransformCtl != NULL)
        fOwnedChannels |= kTransform;
}

void plLayerAnimationBase::write(hsStream* S, plResManager* mgr) {
    plLayerInterface::write(S, mgr);

    mgr->WriteCreatable(S, fPreshadeColorCtl);
    mgr->WriteCreatable(S, fRuntimeColorCtl);
    mgr->WriteCreatable(S, fAmbientColorCtl);
    mgr->WriteCreatable(S, fSpecularColorCtl);
    mgr->WriteCreatable(S, fOpacityCtl);
    mgr->WriteCreatable(S, fTransformCtl);
}

void plLayerAnimationBase::prcWrite(pfPrcHelper* prc) {
    plLayerInterface::prcWrite(prc);

    if (fPreshadeColorCtl != NULL) {
        prc->writeSimpleTag("PreshadeColorCtl");
        fPreshadeColorCtl->prcWrite(prc); prc->closeTag();
        prc->closeTag();
    }
    if (fRuntimeColorCtl != NULL) {
        prc->writeSimpleTag("RuntimeColorCtl");
        fRuntimeColorCtl->prcWrite(prc); prc->closeTag();
        prc->closeTag();
    }
    if (fAmbientColorCtl != NULL) {
        prc->writeSimpleTag("AmbientColorCtl");
        fAmbientColorCtl->prcWrite(prc); prc->closeTag();
        prc->closeTag();
    }
    if (fSpecularColorCtl != NULL) {
        prc->writeSimpleTag("SpecularColorCtl");
        fSpecularColorCtl->prcWrite(prc); prc->closeTag();
        prc->closeTag();
    }
    if (fOpacityCtl != NULL) {
        prc->writeSimpleTag("OpacityCtl");
        fOpacityCtl->prcWrite(prc); prc->closeTag();
        prc->closeTag();
    }
    if (fTransformCtl != NULL) {
        prc->writeSimpleTag("TransformCtl");
        fTransformCtl->prcWrite(prc); prc->closeTag();
        prc->closeTag();
    }
}


/* plLayerAnimation */
plLayerAnimation::plLayerAnimation() { }
plLayerAnimation::~plLayerAnimation() { }

IMPLEMENT_CREATABLE(plLayerAnimation, kLayerAnimation, plLayerAnimationBase)

void plLayerAnimation::read(hsStream* S, plResManager* mgr) {
    plLayerAnimationBase::read(S, mgr);
    fTimeConvert.read(S, mgr);
}

void plLayerAnimation::write(hsStream* S, plResManager* mgr) {
    plLayerAnimationBase::write(S, mgr);
    fTimeConvert.write(S, mgr);
}

void plLayerAnimation::prcWrite(pfPrcHelper* prc) {
    plLayerAnimationBase::prcWrite(prc);
    fTimeConvert.prcWrite(prc); prc->closeTag();
}


/* plLayerLinkAnimation */
plLayerLinkAnimation::plLayerLinkAnimation()
                    : fEnabled(true), fFadeFlags(0), fLastFadeFlag(0),
                      fFadeFlagsDirty(false), fLeavingAge(true) { }
plLayerLinkAnimation::~plLayerLinkAnimation() { }

IMPLEMENT_CREATABLE(plLayerLinkAnimation, kLayerLinkAnimation, plLayerAnimation)

void plLayerLinkAnimation::read(hsStream* S, plResManager* mgr) {
    plLayerAnimation::read(S, mgr);

    fLinkKey = mgr->readKey(S);
    fLeavingAge = S->readBool();
}

void plLayerLinkAnimation::write(hsStream* S, plResManager* mgr) {
    plLayerAnimation::write(S, mgr);

    mgr->writeKey(S, fLinkKey);
    S->writeBool(fLeavingAge);
}

void plLayerLinkAnimation::prcWrite(pfPrcHelper* prc) {
    plLayerAnimation::prcWrite(prc);

    prc->startTag("LinkParams");
    prc->writeParam("LeavingAge", fLeavingAge);
    prc->endTag();
    fLinkKey->prcWrite(prc);
    prc->closeTag();
}


/* plLayerSDLAnimation */
plLayerSDLAnimation::plLayerSDLAnimation() { }
plLayerSDLAnimation::~plLayerSDLAnimation() { }

IMPLEMENT_CREATABLE(plLayerSDLAnimation, kLayerSDLAnimation, plLayerAnimationBase)

void plLayerSDLAnimation::read(hsStream* S, plResManager* mgr) {
    plLayerAnimationBase::read(S, mgr);
    fVarName = S->readSafeStr();
}

void plLayerSDLAnimation::write(hsStream* S, plResManager* mgr) {
    plLayerAnimationBase::write(S, mgr);
    S->writeSafeStr(fVarName);
}

void plLayerSDLAnimation::prcWrite(pfPrcHelper* prc) {
    plLayerAnimationBase::prcWrite(prc);

    prc->startTag("VarName");
    prc->writeParam("value", fVarName);
    prc->endTag(true);
}
