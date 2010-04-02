#ifndef _PLVEHICLEMODIFIER_H
#define _PLVEHICLEMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

DllClass plVehicleModifier : public plSingleModifier {
    CREATABLE(plVehicleModifier, kVehicleModifier, plSingleModifier)

public:
    DllStruct Wheel {
        plKey fWheelObj;
        hsVector3 fPosition, fDirection;
        float fRadius;

        Wheel();
    };

protected:
    plKey fRoot;
    Wheel fWheels[4];

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
