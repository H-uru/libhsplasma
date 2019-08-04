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

#ifndef _PLSERVERGUID_H
#define _PLSERVERGUID_H

#include "../PlasmaDefs.h"
#include "../Stream/hsStream.h"

class PLASMA_DLL plServerGuid
{
protected:
    unsigned char fGuid[8];

public:
    plServerGuid();
    bool operator==(const plServerGuid& other);
    bool operator!=(const plServerGuid& other) { return !operator==(other); }

    unsigned char operator[](size_t idx) const { return fGuid[idx]; }
    unsigned char& operator[](size_t idx) { return fGuid[idx]; }
    ST::string toString() const;
    static plServerGuid FromString(const ST::string& str);

    void read(hsStream* S);
    void write(hsStream* S);
};

#endif
