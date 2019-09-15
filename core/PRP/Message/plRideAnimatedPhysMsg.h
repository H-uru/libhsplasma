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

#ifndef _PLRIDEANIMATEDPHYSMSG_H
#define _PLRIDEANIMATEDPHYSMSG_H

#include "plMessage.h"

class PLASMA_DLL plRideAnimatedPhysMsg : public plMessage
{
    CREATABLE(plRideAnimatedPhysMsg, kRideAnimatedPhysMsg, plMessage)

private:
    bool fEntering;
    plKey fRegion;

public:
    plRideAnimatedPhysMsg() : fEntering() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* s, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool getEntering() const { return fEntering; }
    plKey getRegion() const { return fRegion; }

    void setEntering(bool entering) { fEntering = entering; }
    void setRegion(plKey region) { fRegion = std::move(region); }
};

#endif
