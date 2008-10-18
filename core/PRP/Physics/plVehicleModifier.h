#ifndef _PLVEHICLEMODIFIER_H
#define _PLVEHICLEMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

DllClass plVehicleModifier : public plSingleModifier {
public:
    struct Wheel {
        plKey fWheelObj;
        hsVector3 fPosition, fDirection;
        float fRadius;
    };

protected:
    plKey fRoot;
    Wheel fWheels[4];

public:
    plVehicleModifier();
    virtual ~plVehicleModifier();

    DECLARE_CREATABLE(plVehicleModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
