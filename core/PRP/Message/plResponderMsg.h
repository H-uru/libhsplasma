#ifndef _PLONESHOTMSG_H
#define _PLONESHOTMSG_H

#include "plMessage.h"
#include "plOneShotCallbacks.h"

DllClass plResponderMsg : public plMessage {
    CREATABLE(plResponderMsg, kResponderMsg, plMessage)
};


DllClass plOneShotMsg : public plResponderMsg {
    CREATABLE(plOneShotMsg, kOneShotMsg, plResponderMsg)

protected:
    plOneShotCallbacks fCallbacks;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
