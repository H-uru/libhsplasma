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

#ifndef _PLLOADMASK_H
#define _PLLOADMASK_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

class PLASMA_DLL plLoadMask
{
protected:
    union
    {
        unsigned char fQuality[2];
        unsigned short fMask;
    };

public:
    plLoadMask() : fMask(0xFFFF) { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    bool isUsed() { return (fMask != 0xFFFF); }
    void setQuality(unsigned char low, unsigned char high);
    void setMask(unsigned short mask) { fMask = mask; }
    void setAlways() { fMask = 0xFFFF; }
    unsigned short getMask() const { return fMask; }
    unsigned char getQuality(size_t which) const { return fQuality[which]; }
};

#endif
