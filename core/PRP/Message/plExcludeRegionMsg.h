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

#ifndef _PLEXCLUDEREGIONMSG_H
#define _PLEXCLUDEREGIONMSG_H

#include "plMessage.h"

class PLASMA_DLL plExcludeRegionMsg : public plMessage
{
    CREATABLE(plExcludeRegionMsg, kExcludeRegionMsg, plMessage)

public:
    enum CmdType { kClear, kRelease };

protected:
    unsigned char fCmd;
    unsigned int fSynchFlags;

public:
    plExcludeRegionMsg() : fCmd(), fSynchFlags() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getCmd() const { return fCmd; }
    unsigned int getSynchFlags() const { return fSynchFlags; }

    void setCmd(unsigned char value) { fCmd = value; }
    void setSynchFlags(unsigned int value) { fSynchFlags = value; }
};

#endif
