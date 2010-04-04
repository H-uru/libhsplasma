#ifndef _PLNETMSGGROUPOWNER_H
#define _PLNETMSGGROUPOWNER_H

#include "plNetMessage.h"
#include "plNetGroupId.h"

DllClass plNetMsgGroupOwner : public plNetMsgServerToClient {
    CREATABLE(plNetMsgGroupOwner, kNetMsgGroupOwner, plNetMsgServerToClient)

public:
    DllStruct GroupInfo {
        plNetGroupId fGroupID;
        bool fOwnIt;

        GroupInfo();
    };

private:
    hsTArray<GroupInfo> fGroups;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<GroupInfo>& getGroups() const { return fGroups; }
    hsTArray<GroupInfo>& getGroups() { return fGroups; }
    void addGroup(const GroupInfo& grp) { fGroups.append(grp); }
    void delGroup(size_t idx) { fGroups.remove(idx); }
    void clearGroups() { fGroups.clear(); }
};

#endif
