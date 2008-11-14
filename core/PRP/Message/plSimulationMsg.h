#ifndef _PLSIMULATIONMSG_H
#define _PLSIMULATIONMSG_H

#include "plMessage.h"

DllClass plSimulationMsg : public plMessage {
public:
    plSimulationMsg();
    virtual ~plSimulationMsg();

    DECLARE_CREATABLE(plSimulationMsg)
};

#endif
