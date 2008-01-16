#ifndef _PLTIMERCALLBACKMSG_H
#define _PLTIMERCALLBACKMSG_H

#include "../../NucleusLib/pnMessage/plMessage.h"

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
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
