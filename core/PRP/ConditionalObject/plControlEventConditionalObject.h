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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
