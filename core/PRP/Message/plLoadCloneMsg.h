#ifndef _PLLOADCLONEMSG_H
#define _PLLOADCLONEMSG_H

#include "plMessage.h"

DllClass plLoadCloneMsg : public plMessage {
    CREATABLE(plLoadCloneMsg, kLoadCloneMsg, plMessage)

protected:
    plKey fCloneKey, fRequestorKey;
    unsigned char fValidMsg, fIsLoading;
    unsigned int fUserData, fOriginatingPlayerID;
    plMessage* fTriggerMsg;

public:
    plLoadCloneMsg();
    virtual ~plLoadCloneMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getCloneKey() const { return fCloneKey; }
    plKey getRequestor() const { return fRequestorKey; }
    unsigned char getValidMsg() const { return fValidMsg; }
    unsigned char getIsLoading() const { return fIsLoading; }
    unsigned int getUserData() const { return fUserData; }
    unsigned int getOriginatingPlayerID() const { return fOriginatingPlayerID; }
    plMessage* getTriggerMsg() const { return fTriggerMsg; }

    void setCloneKey(plKey key) { fCloneKey = key; }
    void setRequestor(plKey key) { fRequestorKey = key; }
    void setValidMsg(unsigned char validMsg) { fValidMsg = validMsg; }
    void setIsLoading(unsigned char isLoading) { fIsLoading = isLoading; }
    void setUserData(unsigned int userData) { fUserData = userData; }
    void setOriginatingPlayerID(unsigned int playerID) { fOriginatingPlayerID = playerID; }

    void setTriggerMsg(plMessage* TriggerMsg);
};

#endif
