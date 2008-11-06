#ifndef _PLLAYERANIMATION_H
#define _PLLAYERANIMATION_H

#include "plLayerInterface.h"
#include "PRP/Animation/plController.h"
#include "PRP/Animation/plAnimTimeConvert.h"

DllClass plLayerAnimationBase : public plLayerInterface {
protected:
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
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getPreshadeCtl() const;
    plController* getRuntimeCtl() const;
    plController* getAmbientCtl() const;
    plController* getSpecularCtl() const;
    plController* getOpacityCtl() const;
    plController* getTransformCtl() const;

    void setPreshadeCtl(plController* ctrl);
    void setRuntimeCtl(plController* ctrl);
    void setAmbientCtl(plController* ctrl);
    void setSpecularCtl(plController* ctrl);
    void setOpacityCtl(plController* ctrl);
    void setTransformCtl(plController* ctrl);
};

DllClass plLayerAnimation : public plLayerAnimationBase {
protected:
    plAnimTimeConvert fTimeConvert;

public:
    plLayerAnimation();
    virtual ~plLayerAnimation();

    DECLARE_CREATABLE(plLayerAnimation);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAnimTimeConvert& getTimeConvert();
};

DllClass plLayerLinkAnimation : public plLayerAnimation {
protected:
    plKey fLinkKey;
    bool fLeavingAge;

public:
    plLayerLinkAnimation();
    virtual ~plLayerLinkAnimation();

    DECLARE_CREATABLE(plLayerLinkAnimation)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getLinkKey() const;
    bool getLeavingAge() const;

    void setLinkKey(plKey key);
    void setLeavingAge(bool leaving);
};

DllClass plLayerSDLAnimation : public plLayerAnimation {
protected:
    plString fVarName;

public:
    plLayerSDLAnimation();
    virtual ~plLayerSDLAnimation();

    DECLARE_CREATABLE(plLayerSDLAnimation)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getVarName() const;
    void setVarName(const plString& name);
};

#endif
