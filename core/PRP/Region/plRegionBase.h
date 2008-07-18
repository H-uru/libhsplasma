#ifndef _PLREGIONBASE_H
#define _PLREGIONBASE_H

#include "PRP/Object/plObjInterface.h"
#include "Math/hsGeometry3.h"

DllClass plRegionBase : public plObjInterface {
public:
    plRegionBase();
    virtual ~plRegionBase();

    DECLARE_CREATABLE(plRegionBase)
};

#endif
