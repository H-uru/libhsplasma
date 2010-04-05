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

    void setFlags(unsigned int flags) { fFlags = flags; }
    void setAvatarUoid(const plUoid& uoid) { fAvatarUoid = uoid; }
    void setClientGuid(const plClientGuid& guid) { fClientGuid = guid; }
};


DllClass plNetMsgMembersList : public plNetMsgServerToClient {
    CREATABLE(plNetMsgMembersList, kNetMsgMembersList, plNetMsgServerToClient)

private:
    hsTArray<plNetMsgMemberInfoHelper> fMembers;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plNetMsgMemberInfoHelper>& getMembers() const { return fMembers; }
    hsTArray<plNetMsgMemberInfoHelper>& getMembers() { return fMembers; }
    void addMember(const plNetMsgMemberInfoHelper& memb) { fMembers.append(memb); }
    void delMember(size_t idx) { fMembers.remove(idx); }
    void clearMembers() { fMembers.clear(); }
};

DllClass plNetMsgMemberUpdate : public plNetMsgServerToClient {
    CREATABLE(plNetMsgMemberUpdate, kNetMsgMemberUpdate, plNetMsgServerToClient)

private:
    plNetMsgMemberInfoHelper fMemberInfo;
    bool fAddMember;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plNetMsgMemberInfoHelper& getMember() const { return fMemberInfo; }
    bool getAddMember() { return fAddMember; }
};

DllClass plNetMsgMembersListReq : public plNetMessage {
    CREATABLE(plNetMsgMembersListReq, kNetMsgMembersListReq, plNetMessage)
};

#endif
