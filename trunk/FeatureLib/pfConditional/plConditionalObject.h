#ifndef _PLCONDITIONALOBJECT_H
#define _PLCONDITIONALOBJECT_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "CoreLib/hsBitVector.h"

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
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
