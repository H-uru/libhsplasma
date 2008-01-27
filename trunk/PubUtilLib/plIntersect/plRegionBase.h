#ifndef _PLREGIONBASE_H
#define _PLREGIONBASE_H

#include "NucleusLib/pnSceneObject/plObjInterface.h"
#include "CoreLib/hsGeometry3.h"

DllClass plRegionBase : public plObjInterface {
public:
    plRegionBase();
    virtual ~plRegionBase();

    DECLARE_CREATABLE(plRegionBase)
};

#endif
