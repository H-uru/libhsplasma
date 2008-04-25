#ifndef _PLSIMSTATEMSG_H
#define _PLSIMSTATEMSG_H

#include "plSimulationMsg.h"

DllClass plSimStateMsg : public plSimulationMsg {
public:
    plSimStateMsg();
    virtual ~plSimStateMsg();

    DECLARE_CREATABLE(plSimStateMsg)
};

DllClass plSimSuppressMsg : public plSimStateMsg {
protected:
    bool fSuppress;

public:
    plSimSuppressMsg();
    virtual ~plSimSuppressMsg();

    DECLARE_CREATABLE(plSimSuppressMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
