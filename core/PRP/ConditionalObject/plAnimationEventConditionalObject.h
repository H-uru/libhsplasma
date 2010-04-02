#ifndef _PLANIMATIONEVENTCONDITIONALOBJECT_H
#define _PLANIMATIONEVENTCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plAnimationEventConditionalObject : public plConditionalObject {
    CREATABLE(plAnimationEventConditionalObject,
              kAnimationEventConditionalObject,
              plConditionalObject)

protected:
    CallbackEvent fAction;
    plKey fTarget;

public:
    plAnimationEventConditionalObject();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
