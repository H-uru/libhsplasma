#ifndef _PLACTIVATORCONDITIONALOBJECT_H
#define _PLACTIVATORCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plActivatorConditionalObject : public plConditionalObject {
protected:
    hsTArray<plWeakKey> fActivators;

public:
    plActivatorConditionalObject();
    virtual ~plActivatorConditionalObject();

    DECLARE_CREATABLE(plActivatorConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
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
