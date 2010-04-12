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

DllClass plVolumeIsect : public plCreatable {
    CREATABLE(plVolumeIsect, kVolumeIsect, plCreatable)
};


DllClass plBoundsIsect : public plVolumeIsect {
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


DllClass plConeIsect : public plVolumeIsect {
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


DllClass plConvexIsect : public plVolumeIsect {
    CREATABLE(plConvexIsect, kConvexIsect, plVolumeIsect)

public:
    DllStruct SinglePlane {
        hsVector3 fNorm, fPos, fWorldNorm;
        float fDist, fWorldDist;

        SinglePlane();
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


DllClass plCylinderIsect : public plVolumeIsect {
    CREATABLE(plCylinderIsect, kCylinderIsect, plVolumeIsect)

protected:
    hsVector3 fTop, fBot;
    float fRadius;
    hsVector3 fWorldBot, fWorldNorm;
    float fLength, fMin, fMax;

public:
    plCylinderIsect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParallelIsect : public plVolumeIsect {
    CREATABLE(plParallelIsect, kParallelIsect, plVolumeIsect)

public:
    DllStruct ParPlane {
        hsVector3 fNorm;
        float fMin, fMax;
        hsVector3 fPosOne, fPosTwo;

        ParPlane();
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


DllClass plSphereIsect : public plVolumeIsect {
    CREATABLE(plSphereIsect, kSphereIsect, plVolumeIsect)

protected:
    hsVector3 fCenter, fWorldCenter;
    float fRadius;
    hsVector3 fMins, fMaxs;

public:
    plSphereIsect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plComplexIsect : public plVolumeIsect {
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


DllClass plIntersectionIsect : public plComplexIsect {
    CREATABLE(plIntersectionIsect, kIntersectionIsect, plComplexIsect)
};


DllClass plUnionIsect : public plComplexIsect {
    CREATABLE(plUnionIsect, kUnionIsect, plComplexIsect)
};

#endif
