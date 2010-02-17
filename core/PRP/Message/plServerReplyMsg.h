#ifndef _PLSERVERREPLYMSG_H
#define _PLSERVERREPLYMSG_H

#include "plMessage.h"

DllClass plServerReplyMsg : public plMessage {
public:
    enum { kUnInit = -1, kDeny, kAffirm };

protected:
    int fType;

public:
    plServerReplyMsg();
    virtual ~plServerReplyMsg();

    DECLARE_CREATABLE(plServerReplyMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
