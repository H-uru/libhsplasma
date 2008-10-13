#ifndef _PLCONDITIONALOBJECT_H
#define _PLCONDITIONALOBJECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Util/hsBitVector.h"

DllClass plConditionalObject : public hsKeyedObject {
protected:
    bool fSatisfied, fToggle;
    hsBitVector fFlags;

public:
    plConditionalObject();
    virtual ~plConditionalObject();

    DECLARE_CREATABLE(plConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plPickedConditionalObject : public plConditionalObject {
public:
    DECLARE_CREATABLE(plPickedConditionalObject)
};

DllClass plPythonFileModConditionalObject : public plConditionalObject {
public:
    DECLARE_CREATABLE(plPythonFileModConditionalObject)
};

#endif
