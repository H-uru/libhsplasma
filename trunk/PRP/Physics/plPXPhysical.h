#ifndef _PLPXPHYSICAL_H
#define _PLPXPHYSICAL_H

#include "plPhysical.h"

DllClass plPXPhysical : public plPhysical {
public:
    plPXPhysical();
    plPXPhysical(const plPXPhysical& init);
    virtual ~plPXPhysical();

    DECLARE_CREATABLE(plPXPhysical)

    virtual class plHKPhysical* ConvertToHavok() const;
    virtual class plPXPhysical* ConvertToPhysX() const;
    virtual class plODEPhysical* ConvertToODE() const;

protected:
    virtual void readData(hsStream* S, plResManager* mgr);
    virtual void writeData(hsStream* S, plResManager* mgr);
};

#endif
