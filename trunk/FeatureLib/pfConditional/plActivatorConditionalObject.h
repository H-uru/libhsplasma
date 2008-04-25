#ifndef _PLACTIVATORCONDITIONALOBJECT_H
#define _PLACTIVATORCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plActivatorConditionalObject : public plConditionalObject {
protected:
    hsTArray<plKey> fActivators;

public:
    plActivatorConditionalObject();
    virtual ~plActivatorConditionalObject();

    DECLARE_CREATABLE(plActivatorConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plActivatorActivatorConditionalObject : public plActivatorConditionalObject {
public:
    DECLARE_CREATABLE(plActivatorActivatorConditionalObject)
};

DllClass plVolActivatorConditionalObject : public plActivatorConditionalObject {
public:
    DECLARE_CREATABLE(plVolActivatorConditionalObject)
};

#endif
