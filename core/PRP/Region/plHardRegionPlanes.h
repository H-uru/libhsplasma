#ifndef _PLHARDREGIONPLANES_H
#define _PLHARDREGIONPLANES_H

#include "plHardRegion.h"

DllClass plHardRegionPlanes : public plHardRegion {
public:
    DllClass HardPlane {
    public:
        hsVector3 fNorm, fWorldNorm;
        hsVector3 fPos, fWorldPos;

    public:
        HardPlane();
        ~HardPlane();

        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);

        float getWorldDist() const;
    };

protected:
    hsTArray<HardPlane> fPlanes;

public:
    plHardRegionPlanes();
    virtual ~plHardRegionPlanes();

    DECLARE_CREATABLE(plHardRegionPlanes)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
