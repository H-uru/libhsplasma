#ifndef _PLNETMSGMEMBERSLIST_H
#define _PLNETMSGMEMBERSLIST_H

#include "plClientGuid.h"
#include "PRP/KeyedObject/plUoid.h"
#include "plNetMessage.h"

DllClass plNetMsgMemberInfoHelper : public plCreatable {
    CREATABLE(plNetMsgMemberInfoHelper, kNetMsgMemberInfoHelper, plCreatable)

private:
    unsigned int fFlags;
    plUoid fAvatarUoid;
    plClientGuid fClientGuid;

public:
    plNetMsgMemberInfoHelper();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getFlags() const { return fFlags; }
    const plUoid& getAvatarUoid() const { return fAvatarUoid; }
    const plClientGuid& getClientGuid() const { return fClientGuid; }
};


DllClass plNetMsgMemberListHelper : public plCreatable {
    CREATABLE(plNetMsgMemberListHelper, kNetMsgMemberListHelper, plCreatable)

private:
    hsTArray<plNetMsgMemberInfoHelper> fMembers;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plNetMsgMemberInfoHelper>& getMemberList() { return fMembers; }
};


DllClass plNetMsgMembersList : public plNetMsgServerToClient {
    CREATABLE(plNetMsgMembersList, kNetMsgMembersList, plNetMsgServerToClient)

private:
    plNetMsgMemberListHelper fHelper;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsUint32 getNumMembers() { return fHelper.getMemberList().getSize(); }
    const plNetMsgMemberInfoHelper& getMember(hsUint32 index) { return fHelper.getMemberList().get(index); }
};


DllClass plNetMsgMembersListReq : public plNetMessage {
    CREATABLE(plNetMsgMembersListReq, kNetMsgMembersListReq, plNetMessage)
};

#endif
