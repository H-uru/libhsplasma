#ifndef _PLELEVATORMODIFIER_H
#define _PLELEVATORMODIFIER_H

#include "PRP/Modifier/plModifier.h"

DllClass plElevatorModifier : public plSingleModifier {
public:
    plElevatorModifier();
    virtual ~plElevatorModifier();

    DECLARE_CREATABLE(plElevatorModifier)
};

#endif
