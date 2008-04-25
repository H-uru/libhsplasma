#ifndef _PLCONTROLEVENTCONDITIONALOBJECT_H
#define _PLCONTROLEVENTCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plControlEventConditionalObject : public plConditionalObject {
protected:
    ControlEventCode fControlEvent;

public:
    plControlEventConditionalObject();
    virtual ~plControlEventConditionalObject();

    DECLARE_CREATABLE(plControlEventConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
