#ifndef _PLCONVEXVOLUME_H
#define _PLCONVEXVOLUME_H

#include "PRP/plCreatable.h"
#include "Math/hsGeometry3.h"

DllClass plConvexVolume : public plCreatable {
protected:
    hsPlane3* fLocalPlanes;
    unsigned int fNumPlanes;

public:
    plConvexVolume();
    virtual ~plConvexVolume();

    DECLARE_CREATABLE(plConvexVolume)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
