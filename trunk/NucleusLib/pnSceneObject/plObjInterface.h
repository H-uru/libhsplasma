#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "CoreLib/hsBitVector.h"
#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "NucleusLib/pnMessage/plMessage.h"

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

