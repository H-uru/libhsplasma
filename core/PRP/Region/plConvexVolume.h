#ifndef _PLCONVEXVOLUME_H
#define _PLCONVEXVOLUME_H

#include "PRP/plCreatable.h"
#include "Math/hsGeometry3.h"
#include "Util/hsTArray.hpp"

DllClass plConvexVolume : public plCreatable {
    CREATABLE(plConvexVolume, kConvexVolume, plCreatable)

protected:
    hsTArray<hsPlane3> fLocalPlanes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
