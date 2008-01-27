#ifndef _PLHARDREGION_H
#define _PLHARDREGION_H

#include "plRegionBase.h"

DllClass plHardRegion : public plRegionBase {
public:
    enum { kDirty, kCamInside };

protected:
    unsigned int fState;
    hsPoint3 fCamPos;

public:
    plHardRegion();
    virtual ~plHardRegion();

    DECLARE_CREATABLE(plHardRegion)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plHardRegionComplex : public plHardRegion {
protected:
    hsTArray<plKey> fSubRegions;

public:
    plHardRegionComplex();
    virtual ~plHardRegionComplex();

    DECLARE_CREATABLE(plHardRegionComplex)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plHardRegionIntersect : public plHardRegionComplex {
public:
    plHardRegionIntersect();
    virtual ~plHardRegionIntersect();

    DECLARE_CREATABLE(plHardRegionIntersect)
};

DllClass plHardRegionInvert : public plHardRegionComplex {
public:
    plHardRegionInvert();
    virtual ~plHardRegionInvert();

    DECLARE_CREATABLE(plHardRegionInvert)
};

DllClass plHardRegionUnion : public plHardRegionComplex {
public:
    plHardRegionUnion();
    virtual ~plHardRegionUnion();

    DECLARE_CREATABLE(plHardRegionUnion)
};

#endif
