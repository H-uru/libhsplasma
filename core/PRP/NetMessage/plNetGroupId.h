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

#ifndef _PLNETGROUPID_H
#define _PLNETGROUPID_H

#include "PRP/KeyedObject/plLocation.h"

class PLASMA_DLL plNetGroupId
{
public:
    enum
    {
        kNetGroupConstant = 0x01,
        kNetGroupLocal = 0x02,
    };

private:
    plLocation fID;
    unsigned char fFlags;

public:
    plNetGroupId() : fFlags() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    plLocation getID() const { return fID; }
    unsigned char getFlags() const { return fFlags; }

    void setID(const plLocation& loc) { fID = loc; }
    void setFlags(unsigned char flags) { fFlags = flags; }
};

#endif
