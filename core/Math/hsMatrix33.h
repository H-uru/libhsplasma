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

#ifndef _HSMATRIX33_H
#define _HSMATRIX33_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

struct PLASMA_DLL hsMatrix33
{
private:
    float data[3*3];

public:
    float operator()(int y, int x) const { return data[y+(x*3)]; }
    float& operator()(int y, int x) { return data[y+(x*3)]; }
    const float* glMatrix() const { return data; }

    void Reset();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
