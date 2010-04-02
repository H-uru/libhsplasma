#ifndef _PLVISREGION_H
#define _PLVISREGION_H

#include "PRP/Object/plObjInterface.h"

DllClass plVisRegion : public plObjInterface {
    CREATABLE(plVisRegion, kVisRegion, plObjInterface)

public:
    enum { kDisable, kIsNot, kReplaceNormal, kDisableNormal };

protected:
    plKey fRegion, fVisMgr;

public:
    plVisRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
