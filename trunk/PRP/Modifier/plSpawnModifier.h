#ifndef _PLSPAWNMODIFIER_H
#define _PLSPAWNMODIFIER_H

#include "plModifier.h"

DllClass plSpawnModifier : public plMultiModifier {
public:
    plSpawnModifier();
    virtual ~plSpawnModifier();

    DECLARE_CREATABLE(plSpawnModifier)
};

#endif
