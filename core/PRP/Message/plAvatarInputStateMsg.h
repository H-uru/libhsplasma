#ifndef _PLAVATARINPUTSTATEMSG_H
#define _PLAVATARINPUTSTATEMSG_H

#include "plMessage.h"

DllClass plAvatarInputStateMsg : public plMessage {
protected:
    hsUint16 fState;

public:
    plAvatarInputStateMsg();
    virtual ~plAvatarInputStateMsg();

    DECLARE_CREATABLE(plAvatarInputStateMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
