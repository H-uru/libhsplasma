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

#ifndef _PLARMATUREEFFECTMSG_H
#define _PLARMATUREEFFECTMSG_H

#include "plMessage.h"

class PLASMA_DLL plArmatureEffectStateMsg : public plMessage
{
    CREATABLE(plArmatureEffectStateMsg, kArmatureEffectStateMsg, plMessage)

protected:
    int8_t fSurface;
    bool fAddSurface;

public:
    plArmatureEffectStateMsg() : fSurface(), fAddSurface() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    int8_t getSurface() const { return fSurface; }
    bool getAddSurface() const { return fAddSurface; }

    void setSurface(int8_t value) { fSurface = value; }
    void setAddSurface(bool value) { fAddSurface = value; }
};

#endif
