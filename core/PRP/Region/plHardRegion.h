#ifndef _PLHARDREGION_H
#define _PLHARDREGION_H

#include "plRegionBase.h"

DllClass plHardRegion : public plRegionBase {
public:
    plHardRegion();
    virtual ~plHardRegion();

    DECLARE_CREATABLE(plHardRegion)
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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
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
