#ifndef _PLSOFTVOLUME_H
#define _PLSOFTVOLUME_H

#include "plRegionBase.h"
#include "plVolumeIsect.h"

DllClass plSoftVolume : public plRegionBase {
public:
    enum {
        kListenNone = 0,
        kListenCheck = 0x1,
        kListenPosSet = 0x2,
        kListenDirty = 0x4,
        kListenRegistered = 0x8
    };

protected:
    hsVector3 fListenPos;
    float fListenStrength;
    unsigned int fListenState;
    float fInsideStrength, fOutsideStrength;

public:
    plSoftVolume();
    virtual ~plSoftVolume();

    DECLARE_CREATABLE(plSoftVolume)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSoftVolumeSimple : public plSoftVolume {
protected:
    plVolumeIsect* fVolume;
    float fSoftDist;

public:
    plSoftVolumeSimple();
    virtual ~plSoftVolumeSimple();

    DECLARE_CREATABLE(plSoftVolumeSimple)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSoftVolumeComplex : public plSoftVolume {
protected:
    hsTArray<plKey> fSubVolumes;

public:
    plSoftVolumeComplex();
    virtual ~plSoftVolumeComplex();

    DECLARE_CREATABLE(plSoftVolumeComplex)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSoftVolumeIntersect : public plSoftVolumeComplex {
public:
    plSoftVolumeIntersect();
    virtual ~plSoftVolumeIntersect();

    DECLARE_CREATABLE(plSoftVolumeIntersect)
};

DllClass plSoftVolumeInvert : public plSoftVolumeComplex {
public:
    plSoftVolumeInvert();
    virtual ~plSoftVolumeInvert();

    DECLARE_CREATABLE(plSoftVolumeInvert)
};

DllClass plSoftVolumeUnion : public plSoftVolumeComplex {
public:
    plSoftVolumeUnion();
    virtual ~plSoftVolumeUnion();

    DECLARE_CREATABLE(plSoftVolumeUnion)
};

#endif
