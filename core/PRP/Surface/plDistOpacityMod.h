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

#ifndef _PLDISTOPACITYMOD_H
#define _PLDISTOPACITYMOD_H

#include "../Modifier/plModifier.h"

class PLASMA_DLL plDistOpacityMod : public plSingleModifier
{
    CREATABLE(plDistOpacityMod, kDistOpacityMod, plSingleModifier)

protected:
    float fDists[4];

public:
    enum
    {
        kNearTrans,
        kNearOpaq,
        kFarOpaq,
        kFarTrans
    };

    plDistOpacityMod() : fDists() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getDistance(int pos) const { return fDists[pos]; }
    void  setDistance(int pos, float dist) { fDists[pos] = dist; }
};

#endif
