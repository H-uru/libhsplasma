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

#ifndef _PLVOLUMEISECT_H
#define _PLVOLUMEISECT_H

#include "PRP/plCreatable.h"
#include "ResManager/plResManager.h"
#include "Math/hsGeometry3.h"
#include "Math/hsMatrix44.h"
#include "hsBounds.h"

class PLASMA_DLL plVolumeIsect : public plCreatable
{
    CREATABLE(plVolumeIsect, kVolumeIsect, plCreatable)
};


class PLASMA_DLL plBoundsIsect : public plVolumeIsect
{
    CREATABLE(plBoundsIsect, kBoundsIsect, plVolumeIsect)

protected:
    hsBounds3Ext fLocalBounds, fWorldBounds;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plConeIsect : public plVolumeIsect
{
    CREATABLE(plConeIsect, kConeIsect, plVolumeIsect)

protected:
    int fCapped;
    float fRadAngle, fLength;
    hsVector3 fWorldTip, fWorldNorm;
    hsMatrix44 fWorldToNDC, fLightToNDC;
    hsVector3 fNorms[5];
    float fDists[5];

public:
    plConeIsect() : fCapped(), fRadAngle(), fLength(), fDists() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plConvexIsect : public plVolumeIsect
{
    CREATABLE(plConvexIsect, kConvexIsect, plVolumeIsect)

public:
    class PLASMA_DLL SinglePlane
    {
    protected:
        hsVector3 fNorm, fPos, fWorldNorm;
        float fDist, fWorldDist;

    public:
        SinglePlane() : fDist(), fWorldDist() { }

        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);

    public:
        hsVector3 getNorm() const { return fNorm; }
        hsVector3 getPos() const { return fPos; }
        hsVector3 getWorldNorm() const { return fWorldNorm; }
        float getDist() const { return fDist; }
        float getWorldDist() const { return fWorldDist; }

        void setNorm(hsVector3 norm) { fNorm = std::move(norm); }
        void setPos(hsVector3 pos) { fPos = std::move(pos); }
        void setWorldNorm(hsVector3 worldNorm) { fWorldNorm = std::move(worldNorm); }
        void setDist(float dist) { fDist = dist; }
        void setWorldDist(float worldDist) { fWorldDist = worldDist; }
    };

protected:
    std::vector<SinglePlane> fPlanes;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<SinglePlane>& getPlanes() const { return fPlanes; }
    std::vector<SinglePlane>& getPlanes() { return fPlanes; }

    /** Adds or updates a given plane */
    void addPlane(hsVector3 normal, const hsVector3& pos);
    void addPlane(SinglePlane plane) { fPlanes.emplace_back(std::move(plane)); };

    /** Calculates worldspace transformation for this volume  */
    void transform(const hsMatrix44& localToWorld, const hsMatrix44& worldToLocal);
};


class PLASMA_DLL plCylinderIsect : public plVolumeIsect
{
    CREATABLE(plCylinderIsect, kCylinderIsect, plVolumeIsect)

protected:
    hsVector3 fTop, fBot;
    float fRadius;
    hsVector3 fWorldBot, fWorldNorm;
    float fLength, fMin, fMax;

public:
    plCylinderIsect() : fRadius(), fLength(), fMin(), fMax() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParallelIsect : public plVolumeIsect
{
    CREATABLE(plParallelIsect, kParallelIsect, plVolumeIsect)

public:
    struct PLASMA_DLL ParPlane
    {
        hsVector3 fNorm;
        float fMin, fMax;
        hsVector3 fPosOne, fPosTwo;

        ParPlane() : fMin(), fMax() { }
    };

protected:
    std::vector<ParPlane> fPlanes;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plSphereIsect : public plVolumeIsect
{
    CREATABLE(plSphereIsect, kSphereIsect, plVolumeIsect)

protected:
    hsVector3 fCenter, fWorldCenter;
    float fRadius;
    hsVector3 fMins, fMaxs;

public:
    plSphereIsect() : fRadius() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plComplexIsect : public plVolumeIsect
{
    CREATABLE(plComplexIsect, kComplexIsect, plVolumeIsect)

protected:
    std::vector<plVolumeIsect*> fVolumes;

public:
    plComplexIsect() { }
    ~plComplexIsect();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    void clearVolumes();
};


class PLASMA_DLL plIntersectionIsect : public plComplexIsect
{
    CREATABLE(plIntersectionIsect, kIntersectionIsect, plComplexIsect)
};


class PLASMA_DLL plUnionIsect : public plComplexIsect
{
    CREATABLE(plUnionIsect, kUnionIsect, plComplexIsect)
};

#endif
