#ifndef _PLNETMSGGROUPOWNER_H
#define _PLNETMSGGROUPOWNER_H

#include "plNetMessage.h"
#include "plNetGroupId.h"

DllClass plNetMsgGroupOwner : public plNetMsgServerToClient {
public:
    DllStruct GroupInfo {
        plNetGroupId fGroupID;
        bool fOwnIt;

        GroupInfo();
    };

private:
    hsTArray<GroupInfo> fGroups;

public:
    plNetMsgGroupOwner();
    ~plNetMsgGroupOwner();

    DECLARE_CREATABLE(plNetMsgGroupOwner);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
