#ifndef _PLCONVEXVOLUME_H
#define _PLCONVEXVOLUME_H

#include "../../NucleusLib/pnFactory/plCreatable.h"
#include "../../CoreLib/hsGeometry3.h"

DllClass plConvexVolume : public plCreatable {
protected:
    hsPlane3* fLocalPlanes;
    hsPlane3* fWorldPlanes;
    unsigned int fNumPlanes;

public:
    plConvexVolume();
    virtual ~plConvexVolume();

    DECLARE_CREATABLE(plConvexVolume)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
