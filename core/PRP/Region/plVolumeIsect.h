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
#include "Math/hsGeometry3.h"
#include "Math/hsMatrix44.h"
#include "hsBounds.h"

class PLASMA_DLL plVolumeIsect : public virtual plCreatable {
    CREATABLE(plVolumeIsect, kVolumeIsect, plCreatable)
};


class PLASMA_DLL plBoundsIsect : public virtual plVolumeIsect {
    CREATABLE(plBoundsIsect, kBoundsIsect, plVolumeIsect)

protected:
    hsBounds3Ext fLocalBounds, fWorldBounds;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plConeIsect : public virtual plVolumeIsect {
    CREATABLE(plConeIsect, kConeIsect, plVolumeIsect)

protected:
    int fCapped;
    float fRadAngle, fLength;
    hsVector3 fWorldTip, fWorldNorm;
    hsMatrix44 fWorldToNDC, fLightToNDC;
    hsVector3 fNorms[5];
    float fDists[5];

public:
    plConeIsect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plConvexIsect : public virtual plVolumeIsect {
    CREATABLE(plConvexIsect, kConvexIsect, plVolumeIsect)

public:
    struct PLASMA_DLL SinglePlane {
        hsVector3 fNorm, fPos, fWorldNorm;
        float fDist, fWorldDist;

        SinglePlane() : fDist(0.0f), fWorldDist(0.0f) { }
    };

protected:
    hsTArray<SinglePlane> fPlanes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plCylinderIsect : public virtual plVolumeIsect {
    CREATABLE(plCylinderIsect, kCylinderIsect, plVolumeIsect)

protected:
    hsVector3 fTop, fBot;
    float fRadius;
    hsVector3 fWorldBot, fWorldNorm;
    float fLength, fMin, fMax;

public:
    plCylinderIsect() : fRadius(0.0f), fLength(0.0f), fMin(0.0f), fMax(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plParallelIsect : public virtual plVolumeIsect {
    CREATABLE(plParallelIsect, kParallelIsect, plVolumeIsect)

public:
    struct PLASMA_DLL ParPlane {
        hsVector3 fNorm;
        float fMin, fMax;
        hsVector3 fPosOne, fPosTwo;

        ParPlane() : fMin(0.0f), fMax(0.0f) { }
    };

protected:
    hsTArray<ParPlane> fPlanes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plSphereIsect : public virtual plVolumeIsect {
    CREATABLE(plSphereIsect, kSphereIsect, plVolumeIsect)

protected:
    hsVector3 fCenter, fWorldCenter;
    float fRadius;
    hsVector3 fMins, fMaxs;

public:
    plSphereIsect() : fRadius(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plComplexIsect : public virtual plVolumeIsect {
    CREATABLE(plComplexIsect, kComplexIsect, plVolumeIsect)

protected:
    hsTArray<plVolumeIsect*> fVolumes;

public:
    plComplexIsect() { }
    virtual ~plComplexIsect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearVolumes();
};


class PLASMA_DLL plIntersectionIsect : public virtual plComplexIsect {
    CREATABLE(plIntersectionIsect, kIntersectionIsect, plComplexIsect)
};


class PLASMA_DLL plUnionIsect : public virtual plComplexIsect {
    CREATABLE(plUnionIsect, kUnionIsect, plComplexIsect)
};

#endif
