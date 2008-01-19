#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "CoreLib/hsBitVector.h"
#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "NucleusLib/pnMessage/plMessage.h"

DllClass plObjInterface : public plSynchedObject {
public:
    plKey Owner;
    hsBitVector Props;

public:
    plObjInterface();
    virtual ~plObjInterface();

    DECLARE_CREATABLE(plObjInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

