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

class PLASMA_DLL plLayerAnimationBase : public plLayerInterface
{
    CREATABLE(plLayerAnimationBase, kLayerAnimationBase, plLayerInterface)

protected:
    plController* fPreshadeColorCtl;
    plController* fRuntimeColorCtl;
    plController* fAmbientColorCtl;
    plController* fSpecularColorCtl;
    plController* fOpacityCtl;
    plController* fTransformCtl;

public:
    plLayerAnimationBase()
        : fPreshadeColorCtl(), fRuntimeColorCtl(), fAmbientColorCtl(),
          fSpecularColorCtl(), fOpacityCtl(), fTransformCtl() { }
    ~plLayerAnimationBase();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

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


class PLASMA_DLL plLayerAnimation : public plLayerAnimationBase
{
    CREATABLE(plLayerAnimation, kLayerAnimation, plLayerAnimationBase)

protected:
    plAnimTimeConvert fTimeConvert;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const plAnimTimeConvert& getTimeConvert() const { return fTimeConvert; }
    plAnimTimeConvert& getTimeConvert() { return fTimeConvert; }
};


class PLASMA_DLL plLayerLinkAnimation : public plLayerAnimation
{
    CREATABLE(plLayerLinkAnimation, kLayerLinkAnimation, plLayerAnimation)

protected:
    plKey fLinkKey;
    bool fLeavingAge;

public:
    plLayerLinkAnimation() : fLeavingAge(true) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getLinkKey() const { return fLinkKey; }
    bool getLeavingAge() const { return fLeavingAge; }

    void setLinkKey(plKey key) { fLinkKey = std::move(key); }
    void setLeavingAge(bool leaving) { fLeavingAge = leaving; }
};


class PLASMA_DLL plLayerSDLAnimation : public plLayerAnimation
{
    CREATABLE(plLayerSDLAnimation, kLayerSDLAnimation, plLayerAnimationBase)

protected:
    ST::string fVarName;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    ST::string getVarName() const { return fVarName; }
    void setVarName(const ST::string& name) { fVarName = name; }
};

#endif
