#ifndef _PLHARDREGION_H
#define _PLHARDREGION_H

#include "plRegionBase.hpp"

DllClass plHardRegion : public plRegionBase {
    CREATABLE(plHardRegion, kHardRegion, plRegionBase)
};


DllClass plHardRegionComplex : public plHardRegion {
    CREATABLE(plHardRegionComplex, kHardRegionComplex, plHardRegion)

protected:
    hsTArray<plKey> fSubRegions;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plHardRegionIntersect : public plHardRegionComplex {
    CREATABLE(plHardRegionIntersect, kHardRegionIntersect, plHardRegionComplex)
};


DllClass plHardRegionInvert : public plHardRegionComplex {
    CREATABLE(plHardRegionInvert, kHardRegionInvert, plHardRegionComplex)
};


DllClass plHardRegionUnion : public plHardRegionComplex {
    CREATABLE(plHardRegionUnion, kHardRegionUnion, plHardRegionComplex)
};

#endif
