#ifndef _PLPHYSICAL_H
#define _PLPHYSICAL_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"

DllClass plPhysical : public plSynchedObject {
public:
    DECLARE_CREATABLE(plPhysical)

    virtual class plHKPhysical* ConvertToHavok() const =0;
    virtual class plPXPhysical* ConvertToPhysX() const =0;
    virtual class plODEPhysical* ConvertToODE() const =0;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);

protected:
    virtual void readData(hsStream* S, plResManager* mgr);
    virtual void writeData(hsStream* S, plResManager* mgr);
};

#endif
