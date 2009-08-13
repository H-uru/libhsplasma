#ifndef _PLNETMSGINITIALAGESTATESENT_H
#define _PLNETMSGINITIALAGESTATESENT_H

#include "plNetMessage.h"

DllClass plNetMsgInitialAgeStateSent : public plNetMsgServerToClient {
private:
    unsigned int fNumInitialStates;

public:
    plNetMsgInitialAgeStateSent();
    ~plNetMsgInitialAgeStateSent();

    DECLARE_CREATABLE(plNetMsgInitialAgeStateSent)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
