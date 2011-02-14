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

#ifndef _PLHARDREGIONPLANES_H
#define _PLHARDREGIONPLANES_H

#include "plHardRegion.h"

class PLASMA_DLL plHardRegionPlanes : public virtual plHardRegion {
    CREATABLE(plHardRegionPlanes, kHardRegionPlanes, plHardRegion)

public:
    class PLASMA_DLL HardPlane {
    public:
        hsVector3 fNorm, fWorldNorm;
        hsVector3 fPos, fWorldPos;

    public:
        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);

        float getWorldDist() const;
    };

protected:
    hsTArray<HardPlane> fPlanes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
