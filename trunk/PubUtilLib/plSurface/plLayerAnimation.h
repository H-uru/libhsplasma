#ifndef _PLLAYERANIMATION_H
#define _PLLAYERANIMATION_H

#include "plLayerInterface.h"
#include "PubUtilLib/plInterp/plController.h"
#include "PubUtilLib/plInterp/plAnimTimeConvert.h"

DllClass plLayerAnimationBase : public plLayerInterface {
protected:
    plString fSegmentID;
    double fEvalTime;
    float fCurrentTime, fLength;
    plController* fPreshadeColorCtl;
    plController* fRuntimeColorCtl;
    plController* fAmbientColorCtl;
    plController* fSpecularColorCtl;
    plController* fOpacityCtl;
    plController* fTransformCtl;

public:
    plLayerAnimationBase();
    virtual ~plLayerAnimationBase();

    DECLARE_CREATABLE(plLayerAnimationBase)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plLayerAnimation : public plLayerAnimationBase {
protected:
    plAnimTimeConvert fTimeConvert;
    //plLayerSDLModifier* fLayerSDLMod;

public:
    plLayerAnimation();
    virtual ~plLayerAnimation();

    DECLARE_CREATABLE(plLayerAnimation);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plLayerLinkAnimation : public plLayerAnimation {
public:
    enum {
        kFadeLinkPrep = 0x1,
        kFadeLinking = 0x2,
        kFadeCamera = 0x4,
        kFadeIFace = 0x8,
        kFadeCCR = 0x10
    };

protected:
    plKey fLinkKey;
    bool fEnabled;
    //plEventCallbackMsg* fIFaceCallback;
    unsigned char fFadeFlags, fLastFadeFlag;
    bool fFadeFlagsDirty, fLeavingAge;

public:
    plLayerLinkAnimation();
    virtual ~plLayerLinkAnimation();

    DECLARE_CREATABLE(plLayerLinkAnimation)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plLayerSDLAnimation : public plLayerAnimation {
protected:
    //plSimpleStateVariable* fVar;
    plString fVarName;

public:
    plLayerSDLAnimation();
    virtual ~plLayerSDLAnimation();

    DECLARE_CREATABLE(plLayerSDLAnimation)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
