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

#ifndef _PLVEHICLEMODIFIER_H
#define _PLVEHICLEMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

class HSPLASMA_EXPORT plVehicleModifier : public plSingleModifier
{
    CREATABLE(plVehicleModifier, kVehicleModifier, plSingleModifier)

public:
    struct HSPLASMA_EXPORT Wheel
    {
        plKey fWheelObj;
        hsVector3 fPosition, fDirection;
        float fRadius;

        Wheel() : fRadius(1.0f) { }
    };

    enum { kNumWheels = 4 };

protected:
    plKey fRoot;
    Wheel fWheels[kNumWheels];

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
