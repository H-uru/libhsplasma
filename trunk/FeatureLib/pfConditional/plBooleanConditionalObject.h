#ifndef _PLBOOLEANCONDITIONALOBJECT_H
#define _PLBOOLEANCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plANDConditionalObject : public plConditionalObject {
protected:
    hsTArray<plKey> fChildren;

public:
    plANDConditionalObject();
    virtual ~plANDConditionalObject();

    DECLARE_CREATABLE(plANDConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plORConditionalObject : public plConditionalObject {
protected:
    hsTArray<plKey> fChildren;

public:
    plORConditionalObject();
    virtual ~plORConditionalObject();

    DECLARE_CREATABLE(plORConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
