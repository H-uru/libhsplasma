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

#ifndef _PLRANDOMCOMMANDMOD_H
#define _PLRANDOMCOMMANDMOD_H

#include "plModifier.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plRandomCommandMod : public plSingleModifier
{
    CREATABLE(plRandomCommandMod, kRandomCommandMod, plSingleModifier)

public:
    enum
    {
        kNormal = 0,
        kNoRepeats = 0x1,
        kCoverall = 0x2,
        kOneCycle = 0x4,
        kOneCmd = 0x8,
        kDelayFromEnd = 0x10,
        kSequential = 0x20
    };

    enum { kStopped = 0x1 };

protected:
    unsigned char fState, fMode;
    float fMinDelay, fMaxDelay;

public:
    plRandomCommandMod() : fState(), fMode(), fMinDelay(), fMaxDelay() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
