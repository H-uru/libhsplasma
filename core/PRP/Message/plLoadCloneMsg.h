#ifndef _PLLOADCLONEMSG_H
#define _PLLOADCLONEMSG_H

#include "plMessage.h"

DllClass plLoadCloneMsg : public plMessage {
protected:
    plKey fCloneKey, fRequestorKey;
    unsigned char fValidMsg, fIsLoading;
    unsigned int fUserData, fOriginatingPlayerID;
    plMessage* fTriggerMsg;

public:
    plLoadCloneMsg();
    virtual ~plLoadCloneMsg();

    DECLARE_CREATABLE(plLoadCloneMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plMessage* getTriggerMsg() const;
    void setTriggerMsg(plMessage* msg);
};

#endif
