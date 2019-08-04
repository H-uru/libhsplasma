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

#ifndef _PLCLIMBMSG_H
#define _PLCLIMBMSG_H

#include "plMessage.h"

class PLASMA_DLL plClimbMsg : public plMessage
{
    CREATABLE(plClimbMsg, kClimbMsg, plMessage)

public:
    enum Direction
    {
        kUp = 0x1,
        kDown = 0x2,
        kLeft = 0x4,
        kRight = 0x8,
        kCenter = 0x10
    };

    enum Command
    {
        kNoCommand = 0,
        kEnableClimb = 0x1,
        kEnableDismount = 0x2,
        kFallOff = 0x4,
        kRelease = 0x8,
        kStartClimbing = 0x8
    };

protected:
    unsigned int fCommand;
    unsigned int fDirection;
    bool fStatus;
    plKey fTarget;

public:
    plClimbMsg() : fCommand(), fDirection(), fStatus() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
