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

#ifndef _PLEAXLISTENERMOD_H
#define _PLEAXLISTENERMOD_H

#include "plEAXStructures.h"
#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

class HSPLASMA_EXPORT plEAXListenerMod : public plSingleModifier
{
    CREATABLE(plEAXListenerMod, kEAXListenerMod, plSingleModifier)

protected:
    plKey fSoftRegion;
    EAXREVERBPROPERTIES fListenerProps;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getSoftRegion() const { return fSoftRegion; }
    EAXREVERBPROPERTIES& getListenerProps() { return fListenerProps; }
    const EAXREVERBPROPERTIES& getListenerProps() const { return fListenerProps; }

    void setSoftRegion(plKey region) { fSoftRegion = std::move(region); }
    void setListenerProps(EAXREVERBPROPERTIES properties) { fListenerProps = std::move(properties); }
};

class HSPLASMA_EXPORT plEAXEffect : public plSingleModifier
{
    CREATABLE(plEAXEffect, kEAXEffect, plSingleModifier)
};

class HSPLASMA_EXPORT plEAXReverbEffect : public plEAXEffect
{
    CREATABLE(plEAXReverbEffect, kEAXReverbEffect, plEAXEffect)

public:
    struct Aperture
    {
        hsVector3 fX;
        hsVector3 fY;
        hsVector3 fZ;
    };

protected:
    plKey fSoftRegion;
    EAXREVERBPROPERTIES fListenerProps;
    std::vector<Aperture> fApertures;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getSoftRegion() const { return fSoftRegion; }
    const EAXREVERBPROPERTIES& getListenerProps() const { return fListenerProps; }
    EAXREVERBPROPERTIES& getListenerProps() { return fListenerProps; }
    const std::vector<Aperture>& getApertures() const { return fApertures; }
    std::vector<Aperture>& getApertures() { return fApertures; }

    void setSoftRegion(plKey region) { fSoftRegion = std::move(region); }
};

#endif
