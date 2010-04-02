#ifndef _PLSOFTVOLUME_H
#define _PLSOFTVOLUME_H

#include "plRegionBase.hpp"
#include "plVolumeIsect.h"

DllClass plSoftVolume : public plRegionBase {
    CREATABLE(plSoftVolume, kSoftVolume, plRegionBase)

public:
    enum {
        kListenNone = 0,
        kListenCheck = 0x1,
        kListenPosSet = 0x2,
        kListenDirty = 0x4,
        kListenRegistered = 0x8
    };

protected:
    unsigned int fListenState;
    float fInsideStrength, fOutsideStrength;

public:
    plSoftVolume();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSoftVolumeSimple : public plSoftVolume {
    CREATABLE(plSoftVolumeSimple, kSoftVolumeSimple, plSoftVolume)

protected:
    plVolumeIsect* fVolume;
    float fSoftDist;

public:
    plSoftVolumeSimple();
    virtual ~plSoftVolumeSimple();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setVolume(plVolumeIsect* vol);
};


DllClass plSoftVolumeComplex : public plSoftVolume {
    CREATABLE(plSoftVolumeComplex, kSoftVolumeComplex, plSoftVolume)

protected:
    hsTArray<plKey> fSubVolumes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSoftVolumeIntersect : public plSoftVolumeComplex {
    CREATABLE(plSoftVolumeIntersect, kSoftVolumeIntersect, plSoftVolumeComplex)
};


DllClass plSoftVolumeInvert : public plSoftVolumeComplex {
    CREATABLE(plSoftVolumeInvert, kSoftVolumeInvert, plSoftVolumeComplex)
};


DllClass plSoftVolumeUnion : public plSoftVolumeComplex {
    CREATABLE(plSoftVolumeUnion, kSoftVolumeUnion, plSoftVolumeComplex)
};

#endif
