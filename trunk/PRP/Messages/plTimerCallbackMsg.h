#ifndef _PLTIMERCALLBACKMSG_H
#define _PLTIMERCALLBACKMSG_H

#include "plMessage.h"

DllClass plTimerCallbackMsg : public plMessage {
protected:
    unsigned int fID;
    float fTime;

public:
    plTimerCallbackMsg();
    virtual ~plTimerCallbackMsg();

    DECLARE_CREATABLE(plTimerCallbackMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
