#ifndef _PLVOLUMEISECT_H
#define _PLVOLUMEISECT_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsMatrix44.h"
#include "CoreLib/hsBounds.h"

DllClass plVolumeIsect : public plCreatable {
public:
    plVolumeIsect();
    virtual ~plVolumeIsect();

    DECLARE_CREATABLE(plVolumeIsect)
};

DllClass plBoundsIsect : public plVolumeIsect {
protected:
    hsBounds3Ext fLocalBounds, fWorldBounds;

public:
    plBoundsIsect();
    virtual ~plBoundsIsect();

    DECLARE_CREATABLE(plBoundsIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plConeIsect : public plVolumeIsect {
protected:
    int fCapped;
    float fRadAngle, fLength;
    hsVector3 fWorldTip, fWorldNorm;
    hsMatrix44 fWorldToNDC, fLightToNDC;
    hsVector3 fNorms[5];
    float fDists[5];

public:
    plConeIsect();
    virtual ~plConeIsect();

    DECLARE_CREATABLE(plConeIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plConvexIsect : public plVolumeIsect {
public:
    DllStruct SinglePlane {
        hsVector3 fNorm;
        float fDist;
        hsVector3 fPos, fWorldNorm;
        float fWorldDist;
    };

protected:
    hsTArray<SinglePlane> fPlanes;

public:
    plConvexIsect();
    virtual ~plConvexIsect();

    DECLARE_CREATABLE(plConvexIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plCylinderIsect : public plVolumeIsect {
protected:
    hsVector3 fTop, fBot;
    float fRadius;
    hsVector3 fWorldBot, fWorldNorm;
    float fLength, fMin, fMax;

public:
    plCylinderIsect();
    virtual ~plCylinderIsect();

    DECLARE_CREATABLE(plCylinderIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plParallelIsect : public plVolumeIsect {
public:
    DllStruct ParPlane {
        hsVector3 fNorm;
        float fMin, fMax;
        hsVector3 fPosOne, fPosTwo;
    };

protected:
    hsTArray<ParPlane> fPlanes;

public:
    plParallelIsect();
    virtual ~plParallelIsect();

    DECLARE_CREATABLE(plParallelIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plSphereIsect : public plVolumeIsect {
protected:
    hsVector3 fCenter, fWorldCenter;
    float fRadius;
    hsVector3 fMins, fMaxs;

public:
    plSphereIsect();
    virtual ~plSphereIsect();

    DECLARE_CREATABLE(plSphereIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plComplexIsect : public plVolumeIsect {
protected:
    hsTArray<plVolumeIsect*> fVolumes;

public:
    plComplexIsect();
    virtual ~plComplexIsect();

    DECLARE_CREATABLE(plComplexIsect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plIntersectionIsect : public plComplexIsect {
public:
    plIntersectionIsect();
    virtual ~plIntersectionIsect();

    DECLARE_CREATABLE(plIntersectionIsect)
};

DllClass plUnionIsect : public plComplexIsect {
public:
    plUnionIsect();
    virtual ~plUnionIsect();

    DECLARE_CREATABLE(plUnionIsect)
};

#endif
