#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "Util/hsBitVector.h"
#include "plSynchedObject.h"
#include "PRP/Messages/plMessage.h"

DllClass plObjInterface : public plSynchedObject {
public:
    enum { kDisable };

protected:
    plWeakKey fOwner;
    hsBitVector fProps;

public:
    plObjInterface();
    virtual ~plObjInterface();

    DECLARE_CREATABLE(plObjInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif

