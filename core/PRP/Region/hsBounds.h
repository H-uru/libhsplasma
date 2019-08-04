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

#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include <array>
#include "Math/hsGeometry3.h"

typedef std::array<hsVector3, 8> hsBounds3Corners;

class PLASMA_DLL hsBounds
{
protected:
    int fType;

public:
    virtual const char* ClassName() const { return "hsBounds"; }

    hsBounds() : fType() { }
    virtual ~hsBounds() { }

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    int getType() const { return fType; }
    void setType(int type) { fType = type; }
};

class PLASMA_DLL hsBounds3 : public hsBounds
{
public:
    enum
    {
        kCenterValid = 0x1,
        kIsSphere = 0x2
    };

protected:
    hsVector3 fMins, fMaxs, fCenter;

public:
    const char* ClassName() const HS_OVERRIDE { return "hsBounds3"; }

    hsBounds3() { }

    void init(const hsVector3& right);
    hsBounds3 operator+(const hsBounds3& right) const;
    hsBounds3& operator+=(const hsBounds3& right);
    hsBounds3& operator+=(const hsVector3& point);

    void read(hsStream* S) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag) HS_OVERRIDE;

public:
    hsVector3 getMins() const { return fMins; }
    hsVector3 getMaxs() const { return fMaxs; }
    hsVector3 getCenter() const { return fCenter; }
    virtual hsBounds3Corners getCorners() const;

    void setMins(const hsVector3& mins) { fMins = mins; }
    void setMaxs(const hsVector3& maxs) { fMaxs = maxs; }
    void setCenter(const hsVector3& center) { fCenter = center; }

    const hsVector3& updateCenter();
};


class PLASMA_DLL hsBounds3Ext : public hsBounds3
{
public:
    enum
    {
        kAxisAligned = 0x1,
        kSphereSet = 0x2,
        kDistsSet = 0x4,
        kAxisZeroZero = 0x100000,
        kAxisOneZero = 0x200000,
        kAxisTwoZero = 0x400000
    };

protected:
    unsigned int fExtFlags;
    hsVector3 fCorner;
    hsVector3 fAxes[3];
    hsFloatPoint2 fDists[3];
    float fRadius;

public:
    const char* ClassName() const HS_OVERRIDE { return "hsBounds3Ext"; }

    hsBounds3Ext() : fExtFlags(), fRadius() { }

    hsBounds3Ext operator+(const hsBounds3Ext& right) const;

    void read(hsStream* S) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag) HS_OVERRIDE;

public:
    unsigned int getFlags() const { return fExtFlags; }
    hsVector3 getCorner() const { return fCorner; }
    hsBounds3Corners getCorners() const HS_OVERRIDE;
    hsVector3 getAxis(size_t idx) const { return fAxes[idx]; }
    hsFloatPoint2 getDist(size_t idx) const { return fDists[idx]; }
    float getRadius() const { return fRadius; }

    void unalign();
    void setFlags(unsigned int flags) { fExtFlags = flags; }
    void setCorner(const hsVector3& corner) { fCorner = corner; }
    void setAxis(size_t idx, const hsVector3& ax) { fAxes[idx] = ax; }
    void setDist(size_t idx, const hsFloatPoint2& dist) { fDists[idx] = dist; }
    void setRadius(float rad) { fRadius = rad; }
};


class PLASMA_DLL hsBoundsOriented : public hsBounds
{
protected:
    unsigned int fCenterValid;
    hsVector3 fCenter;
    hsPlane3* fPlanes;
    unsigned int fNumPlanes;

public:
    const char* ClassName() const HS_OVERRIDE { return "hsBoundsOriented"; }

    hsBoundsOriented() : fCenterValid(), fPlanes(), fNumPlanes() { }
    hsBoundsOriented(const hsBoundsOriented&);
    ~hsBoundsOriented();

    void read(hsStream* S) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag) HS_OVERRIDE;

public:
    unsigned int getCenterValid() const { return fCenterValid; }
    hsVector3 getCenter() const { return fCenter; }
    unsigned int getNumPlanes() const { return fNumPlanes; }
    const hsPlane3* getPlanes() const { return fPlanes; }

    void setCenterValid(unsigned int valid) { fCenterValid = valid; }
    void setCenter(const hsVector3& center) { fCenter = center; }
    void setPlanes(unsigned int numPlanes, const hsPlane3* planes);
};

#endif

