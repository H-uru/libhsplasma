#ifndef _PLBOUNDINTERFACE_H
#define _PLBOUNDINTERFACE_H

#include "PRP/Object/plObjInterface.h"
#include "PRP/Region/plConvexVolume.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plConvexVolume* getBounds() const;
    void setBounds(plConvexVolume* bounds);
};

#endif
