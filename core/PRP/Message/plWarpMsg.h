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

#ifndef _PLWARPMSG_H
#define _PLWARPMSG_H

#include "plMessage.h"
#include "Math/hsMatrix44.h"

class PLASMA_DLL plWarpMsg : public plMessage
{
    CREATABLE(plWarpMsg, kWarpMsg, plMessage)

public:
    enum { kFlushTransform = 0x1, kZeroVelocity = 0x2 };

private:
    uint32_t fWarpFlags;
    hsMatrix44 fTransform;

public:
    plWarpMsg() : fWarpFlags(), fTransform() { }

    uint32_t getWarpFlags() const { return fWarpFlags; }
    void setWarpFlags(uint32_t f) { fWarpFlags = f; }

    hsMatrix44 getTransform() { return fTransform; }
    void setTransform(const hsMatrix44& mat) { fTransform = mat; }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
