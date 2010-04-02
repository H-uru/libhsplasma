#ifndef _PLACTIVATORCONDITIONALOBJECT_H
#define _PLACTIVATORCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plActivatorConditionalObject : public plConditionalObject {
    CREATABLE(plActivatorConditionalObject, kActivatorConditionalObject,
              plConditionalObject)

protected:
    hsTArray<plKey> fActivators;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plActivatorActivatorConditionalObject : public plActivatorConditionalObject {
    CREATABLE(plActivatorActivatorConditionalObject,
              kActivatorActivatorConditionalObject,
              plActivatorConditionalObject)
};


DllClass plVolActivatorConditionalObject : public plActivatorConditionalObject {
    CREATABLE(plVolActivatorConditionalObject,
              kVolActivatorConditionalObject,
              plActivatorConditionalObject)
};

#endif
