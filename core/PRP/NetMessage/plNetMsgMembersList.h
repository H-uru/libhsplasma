/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLNETMSGMEMBERSLIST_H
#define _PLNETMSGMEMBERSLIST_H

#include "plClientGuid.h"
#include "PRP/KeyedObject/plUoid.h"
#include "plNetMessage.h"

class PLASMA_DLL plNetMsgMemberInfoHelper : public plCreatable {
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


class PLASMA_DLL plNetMsgMembersList : public plNetMsgServerToClient {
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


class PLASMA_DLL plNetMsgMemberUpdate : public plNetMsgServerToClient {
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
    plNetMsgMemberInfoHelper& getMember() { return fMemberInfo; }

    bool getAddMember() { return fAddMember; }
    void setAddMember(bool add) { fAddMember = add; }
};


class PLASMA_DLL plNetMsgMembersListReq : public plNetMessage {
    CREATABLE(plNetMsgMembersListReq, kNetMsgMembersListReq, plNetMessage)
};

#endif
