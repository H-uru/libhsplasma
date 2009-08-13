#ifndef _PLNETMSGMEMBERSLIST_H
#define _PLNETMSGMEMBERSLIST_H

#include "plClientGuid.h"
#include "PRP/KeyedObject/plUoid.h"
#include "plNetMessage.h"

DllClass plNetMsgMemberInfoHelper : public plCreatable {
private:
    unsigned int fFlags;
    plUoid fAvatarUoid;
    plClientGuid fClientGuid;

public:
    plNetMsgMemberInfoHelper();
    ~plNetMsgMemberInfoHelper();

    DECLARE_CREATABLE(plNetMsgMemberInfoHelper)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgMemberListHelper : public plCreatable {
private:
    hsTArray<plNetMsgMemberInfoHelper> fMembers;

public:
    plNetMsgMemberListHelper();
    ~plNetMsgMemberListHelper();

    DECLARE_CREATABLE(plNetMsgMemberListHelper)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgMembersList : public plNetMsgServerToClient {
private:
    plNetMsgMemberListHelper fHelper;

public:
    plNetMsgMembersList();
    ~plNetMsgMembersList();

    DECLARE_CREATABLE(plNetMsgMembersList)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgMembersListReq : public plNetMessage {
public:
    DECLARE_CREATABLE(plNetMsgMembersListReq)
};

#endif
