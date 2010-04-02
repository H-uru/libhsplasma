#ifndef _PLHKSUBWORLD_H
#define _PLHKSUBWORLD_H

#include "PRP/Object/plObjInterface.h"
#include "Math/hsGeometry3.h"

DllClass plHKSubWorld : public plObjInterface {
    CREATABLE(plHKSubWorld, kHKSubWorld, plObjInterface)

private:
    hsVector3 fPosition;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
