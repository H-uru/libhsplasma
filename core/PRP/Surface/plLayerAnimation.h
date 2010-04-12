/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLLAYERANIMATION_H
#define _PLLAYERANIMATION_H

#include "plLayerInterface.h"
#include "PRP/Animation/plController.h"
#include "PRP/Animation/plAnimTimeConvert.h"

DllClass plLayerAnimationBase : public plLayerInterface {
    CREATABLE(plLayerAnimationBase, kLayerAnimationBase, plLayerInterface)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getPreshadeCtl() const { return fPreshadeColorCtl; }
    plController* getRuntimeCtl() const { return fSpecularColorCtl; }
    plController* getAmbientCtl() const { return fAmbientColorCtl; }
    plController* getSpecularCtl() const { return fSpecularColorCtl; }
    plController* getOpacityCtl() const { return fOpacityCtl; }
    plController* getTransformCtl() const { return fTransformCtl; }

    void setPreshadeCtl(plController* ctrl);
    void setRuntimeCtl(plController* ctrl);
    void setAmbientCtl(plController* ctrl);
    void setSpecularCtl(plController* ctrl);
    void setOpacityCtl(plController* ctrl);
    void setTransformCtl(plController* ctrl);
};


DllClass plLayerAnimation : public plLayerAnimationBase {
    CREATABLE(plLayerAnimation, kLayerAnimation, plLayerAnimationBase)

protected:
    plAnimTimeConvert fTimeConvert;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plAnimTimeConvert& getTimeConvert() const { return fTimeConvert; }
    plAnimTimeConvert& getTimeConvert() { return fTimeConvert; }
};


DllClass plLayerLinkAnimation : public plLayerAnimation {
    CREATABLE(plLayerLinkAnimation, kLayerLinkAnimation, plLayerAnimation)

protected:
    plKey fLinkKey;
    bool fLeavingAge;

public:
    plLayerLinkAnimation();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getLinkKey() const { return fLinkKey; }
    bool getLeavingAge() const { return fLeavingAge; }

    void setLinkKey(plKey key) { fLinkKey = key; }
    void setLeavingAge(bool leaving) { fLeavingAge = leaving; }
};


DllClass plLayerSDLAnimation : public plLayerAnimation {
    CREATABLE(plLayerSDLAnimation, kLayerSDLAnimation, plLayerAnimationBase)

protected:
    plString fVarName;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getVarName() const { return fVarName; }
    void setVarName(const plString& name) { fVarName = name; }
};

#endif
