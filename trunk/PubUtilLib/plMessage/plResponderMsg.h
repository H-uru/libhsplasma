#ifndef _PLONESHOTMSG_H
#define _PLONESHOTMSG_H

#include "NucleusLib/pnMessage/plMessage.h"
#include "plOneShotCallbacks.h"

DllClass plResponderMsg : public plMessage {
protected:
    plKey fPlayerKey;

public:
    plResponderMsg();
    virtual ~plResponderMsg();

    DECLARE_CREATABLE(plResponderMsg)
};

DllClass plOneShotMsg : public plResponderMsg {
protected:
    plOneShotCallbacks fCallbacks;

public:
    plOneShotMsg();
    virtual ~plOneShotMsg();

    DECLARE_CREATABLE(plOneShotMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
