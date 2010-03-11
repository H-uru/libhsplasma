#ifndef _PLSIMULATIONMSG_H
#define _PLSIMULATIONMSG_H

#include "plMessage.h"

DllClass plSimulationMsg : public plMessage {
public:
    plSimulationMsg();
    virtual ~plSimulationMsg();

    DECLARE_CREATABLE(plSimulationMsg)
};

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSubWorldMsg : public plSimulationMsg {
protected:
    plKey fWorldKey;

public:
    plSubWorldMsg();
    virtual ~plSubWorldMsg();

    DECLARE_CREATABLE(plSubWorldMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
