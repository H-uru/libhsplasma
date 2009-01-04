#ifndef _PLCROSSFADEMSG_H
#define _PLCROSSFADEMSG_H

#include "plMessage.h"

DllClass plCrossfadeMsg : public plMessage {
public:
    DECLARE_CREATABLE(plCrossfadeMsg)
};

#endif
