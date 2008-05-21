#ifndef _PLODEPHYSICAL_H
#define _PLODEPHYSICAL_H

#include "plPhysical.h"

DllClass plODEPhysical : public plPhysical {
public:
    plODEPhysical();
    plODEPhysical(const plODEPhysical& init);
    virtual ~plODEPhysical();

    DECLARE_CREATABLE(plODEPhysical)

    virtual class plHKPhysical* ConvertToHavok() const;
    virtual class plPXPhysical* ConvertToPhysX() const;
    virtual class plODEPhysical* ConvertToODE() const;

protected:
    virtual void readData(hsStream* S, plResManager* mgr);
    virtual void writeData(hsStream* S, plResManager* mgr);
};

#endif
