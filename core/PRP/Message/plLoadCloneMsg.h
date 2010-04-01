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
    plKey getCloneKey() const;
    plKey getRequestorKey() const;
    unsigned char getValidMsg() const;
    unsigned char getIsLoading() const;
    unsigned int getUserData() const;
    unsigned int getOriginatingPlayerID() const;
    plMessage* getTriggerMsg() const;

    void setCloneKey(plKey CloneKey);
    void setRequestorKey(plKey RequestorKey);
    void setValidMsg(unsigned char ValidMsg);
    void setIsLoading(unsigned char IsLoading);
    void setUserData(unsigned int UserData);
    void setOriginatingPlayerID(unsigned int OriginatingPlayerID);
    void setTriggerMsg(plMessage* TriggerMsg);
};

#endif
