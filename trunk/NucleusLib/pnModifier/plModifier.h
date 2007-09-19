#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "../pnNetCommon/plSynchedObject.h"
#include "../pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsBitVector.h"

DllClass plModifier : public plSynchedObject {
public:
    plModifier();

    DECLARE_CREATABLE(plModifier)
};


DllClass plSingleModifier : public plModifier {
protected:
    plSceneObject* target;
    hsBitVector flags;

public:
    plSingleModifier();

    DECLARE_CREATABLE(plSingleModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};


DllClass plMultiModifier : public plModifier {
protected:
    hsTArray<plSceneObject*> targets;
    hsBitVector flags;

public:
    plMultiModifier();

    DECLARE_CREATABLE(plMultiModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
