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

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"
#include "3rdPartyLibs/AL/EFX-Util.h"

class PLASMA_DLL plEAXListenerMod : public plSingleModifier
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
};

class PLASMA_DLL plEAXEffect : public plSingleModifier
{
    CREATABLE(plEAXEffect, kEAXEffect, plSingleModifier)
};

class PLASMA_DLL plEAXReverbEffect : public plEAXEffect
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
};

#endif
