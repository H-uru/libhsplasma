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

#ifndef _HSMATRIX44_H
#define _HSMATRIX44_H

#include "hsGeometry3.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

// Just remember: http://xkcd.org/184/

struct PLASMA_DLL hsMatrix44
{
public:
    enum { kRight, kUp, kView };  // Axes

private:
    float data[4*4];

public:
    hsMatrix44() { Reset(); }

    static hsMatrix44 Identity();
    static hsMatrix44 TranslateMat(const hsVector3& translate);
    static hsMatrix44 RotateMat(int axis, float angle);
    static hsMatrix44 ScaleMat(const hsVector3& scale);

    void Reset();
    bool IsIdentity() const;

    float operator()(int y, int x) const { return data[y+(x*4)]; }
    float& operator()(int y, int x) { return data[y+(x*4)]; }
    bool operator==(const hsMatrix44& other) const;
    const float* glMatrix() const { return data; }

    hsMatrix44 operator*(const hsMatrix44& right) const;
    hsVector3 multPoint(const hsVector3& point) const;
    hsVector3 multVector(const hsVector3& vec) const;

    hsMatrix44 inverse() const;

    hsMatrix44& translate(const hsVector3& translate);
    hsMatrix44& rotate(int axis, float angle);
    hsMatrix44& scale(const hsVector3& scale);
    hsMatrix44& setTranslate(const hsVector3& translate);
    hsMatrix44& setRotate(int axis, float angle);
    hsMatrix44& setScale(const hsVector3& scale);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    ST::string toString() const;
};

#endif
