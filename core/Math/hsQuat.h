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

struct PLASMA_DLL hsQuat
{
    float X, Y, Z, W;

    hsQuat() : X(), Y(), Z(), W() { }
    hsQuat(float _x, float _y, float _z, float _w) : X(_x), Y(_y), Z(_z), W(_w) { }
    hsQuat(float rad, const hsVector3& axis);

    static hsQuat Identity() { return hsQuat(0.0f, 0.0f, 0.0f, 1.0f); }

    bool operator==(const hsQuat& other) const
    {
        return (X == other.X) && (Y == other.Y) && (Z == other.Z) && (W == other.W);
    }

    bool operator!=(const hsQuat& other) const
    {
        return (X != other.X) || (Y != other.Y) || (Z != other.Z) || (W != other.W);
    }

    hsQuat operator+(const hsQuat& rt) const
    {
        return hsQuat(X + rt.X, Y + rt.Y, Z + rt.Z, W + rt.W);
    }

    hsQuat operator-(const hsQuat& rt) const
    {
        return hsQuat(X - rt.X, Y - rt.Y, Z - rt.Z, W - rt.W);
    }

    hsQuat operator*(const hsQuat& rt) const
    {
        return hsQuat((Y * rt.Z) - (Z * rt.Y) + (Z * rt.X) + (X * rt.Z),
                      (Z * rt.X) - (X * rt.Z) + (Z * rt.Y) + (Y * rt.Z),
                      (X * rt.Y) - (Y * rt.X) + (Z * rt.Y) + (Y * rt.Z),
                      (W * rt.W) - (X * rt.X) - (Y * rt.Y) - (Z * rt.Z));
    }

    hsQuat operator*(float scale) const
    {
        return hsQuat(X * scale, Y * scale, Z * scale, W * scale);
    }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    hsQuat conjugate() const { return hsQuat(-X, -Y, -Z, W); }
};

#endif
