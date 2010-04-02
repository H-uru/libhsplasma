#ifndef _PLBOOLEANCONDITIONALOBJECT_H
#define _PLBOOLEANCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plANDConditionalObject : public plConditionalObject {
    CREATABLE(plANDConditionalObject, kANDConditionalObject,
              plConditionalObject)

protected:
    hsTArray<plKey> fChildren;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plORConditionalObject : public plConditionalObject {
    CREATABLE(plORConditionalObject, kORConditionalObject,
              plConditionalObject)

protected:
    hsTArray<plKey> fChildren;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
