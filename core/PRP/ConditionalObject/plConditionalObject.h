#ifndef _PLCONDITIONALOBJECT_H
#define _PLCONDITIONALOBJECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Util/hsBitVector.h"

DllClass plConditionalObject : public hsKeyedObject {
    CREATABLE(plConditionalObject, kConditionalObject, hsKeyedObject)

protected:
    bool fSatisfied, fToggle;

public:
    plConditionalObject();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plPickedConditionalObject : public plConditionalObject {
    CREATABLE(plPickedConditionalObject, kPickedConditionalObject,
              plConditionalObject)
};


DllClass plPythonFileModConditionalObject : public plConditionalObject {
    CREATABLE(plPythonFileModConditionalObject,
              kPythonFileModConditionalObject,
              plConditionalObject)
};

#endif
