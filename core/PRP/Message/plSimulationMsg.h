#ifndef _PLSIMULATIONMSG_H
#define _PLSIMULATIONMSG_H

#include "plMessage.h"

DllClass plSimulationMsg : public plMessage {
    CREATABLE(plSimulationMsg, kSimulationMsg, plMessage)
};


DllClass plSimStateMsg : public plSimulationMsg {
    CREATABLE(plSimStateMsg, kSimStateMsg, plSimulationMsg)
};


DllClass plSimSuppressMsg : public plSimStateMsg {
    CREATABLE(plSimSuppressMsg, kSimSuppressMsg, plSimStateMsg)

protected:
    bool fSuppress;

public:
    plSimSuppressMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSubWorldMsg : public plSimulationMsg {
    CREATABLE(plSubWorldMsg, kSubWorldMsg, plSimulationMsg)

protected:
    plKey fWorldKey;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
