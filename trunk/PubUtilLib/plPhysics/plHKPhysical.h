#ifndef _PLHKPHYSICAL_H
#define _PLHKPHYSICAL_H

#include "plPhysical.h"

DllClass plHKPhysical : public plPhysical {
public:
    plHKPhysical();
    plHKPhysical(const plHKPhysical& init);
    virtual ~plHKPhysical();

    DECLARE_CREATABLE(plHKPhysical)

    virtual class plHKPhysical* ConvertToHavok() const;
    virtual class plPXPhysical* ConvertToPhysX() const;
    virtual class plODEPhysical* ConvertToODE() const;

protected:
    virtual void readData(hsStream* S, plResManager* mgr);
    virtual void writeData(hsStream* S, plResManager* mgr);
};

#endif
