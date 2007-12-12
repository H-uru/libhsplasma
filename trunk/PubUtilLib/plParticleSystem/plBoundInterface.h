#ifndef _PLBOUNDINTERFACE_H
#define _PLBOUNDINTERFACE_H

#include "../../NucleusLib/pnSceneObject/plObjInterface.h"
#include "plConvexVolume.h"

DllClass plBoundInterface : public plObjInterface {
public:
    enum { kDisable, kNumProps };

protected:
    plConvexVolume* fBounds;

public:
    plBoundInterface();
    virtual ~plBoundInterface();

    DECLARE_CREATABLE(plBoundInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
