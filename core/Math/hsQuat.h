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

#ifndef _HSQUAT_H
#define _HSQUAT_H

#include "hsGeometry3.h"

struct PLASMA_DLL hsQuat {
    float X, Y, Z, W;

    hsQuat();
    hsQuat(const hsQuat& init);
    hsQuat(float x, float y, float z, float w);
    hsQuat(float rad, const hsVector3& axis);

    static hsQuat Identity();

    hsQuat& operator=(const hsQuat& cpy);
    bool operator==(const hsQuat& other) const;
    bool operator!=(const hsQuat& other) const;
    hsQuat operator+(const hsQuat& rt) const;
    hsQuat operator-(const hsQuat& rt) const;
    hsQuat operator*(const hsQuat& rt) const;
    hsQuat operator*(float scale) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    hsQuat conjugate() const;
};

#endif
