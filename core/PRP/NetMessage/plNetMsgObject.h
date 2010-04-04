#ifndef _PLNETMSGOBJECT_H
#define _PLNETMSGOBJECT_H

#include "plNetMessage.h"
#include "PRP/KeyedObject/plUoid.h"

DllClass plNetMsgObject : public plNetMessage {
    CREATABLE(plNetMsgObject, kNetMsgObject, plNetMessage)

private:
    plUoid fUoid;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plUoid getUoid() const { return fUoid; }
    void setUoid(const plUoid& uoid) { fUoid = uoid; }
};

#endif
