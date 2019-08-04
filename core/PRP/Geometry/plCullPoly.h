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

#ifndef _PLCULLPOLY_H
#define _PLCULLPOLY_H

#include "Util/hsBitVector.h"
#include "Math/hsGeometry3.h"

class PLASMA_DLL plCullPoly
{
public:
    enum
    {
        kNone,
        kHole = 0x1,
        kTwoSided = 0x2
    };

protected:
    unsigned int fFlags;
    std::vector<hsVector3> fVerts;
    hsVector3 fNorm, fCenter;
    float fDist, fRadius;

public:
    plCullPoly() : fFlags(kNone), fDist(), fRadius() { }
    plCullPoly(const plCullPoly& init)
        : fFlags(init.fFlags), fVerts(init.fVerts), fNorm(init.fNorm),
          fCenter(init.fCenter), fDist(init.fDist), fRadius(init.fRadius) { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    unsigned int getFlags() const { return fFlags; }
    const std::vector<hsVector3>& getVerts() const { return fVerts; }
    hsVector3 getNorm() const { return fNorm; }
    hsVector3 getCenter() const { return fCenter; }
    float getDist() const { return fDist; }
    float getRadius() const { return fRadius; }

    void setFlags(unsigned int flags) { fFlags = flags; }
    void setVerts(const std::vector<hsVector3>& verts) { fVerts = verts; }
    void setNorm(const hsVector3& norm) { fNorm = norm; }
    void setCenter(const hsVector3& center) { fCenter = center; }
    void setDist(float dist) { fDist = dist; }
    void setRadius(float radius) { fRadius = radius; }
};

#endif
