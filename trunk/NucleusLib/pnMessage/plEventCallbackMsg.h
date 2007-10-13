#ifndef _PLEVENTCALLBACKMSG_H
#define _PLEVENTCALLBACKMSG_H

#include "plMessage.h"

DllClass plEventCallbackMsg : public plMessage {
protected:
    float fEventTime;
    CallbackEvent fEvent;
    short fIndex, fRepeats, fUser;

public:
    plEventCallbackMsg();
    virtual ~plEventCallbackMsg();

    DECLARE_CREATABLE(plEventCallbackMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
