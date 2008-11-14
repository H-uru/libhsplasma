#ifndef _PLSWIMMSG_H
#define _PLSWIMMSG_H

#include "plMessage.h"

DllClass plSwimMsg : public plMessage {
protected:
    bool fIsEntering;
    plKey fSwimRegion;

public:
    plSwimMsg();

    DECLARE_CREATABLE(plSwimMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
