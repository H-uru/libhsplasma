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
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
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
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
