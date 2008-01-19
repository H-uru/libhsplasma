#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "NucleusLib/pnSceneObject/plSceneObject.h"
#include "CoreLib/hsBitVector.h"

DllClass plModifier : public plSynchedObject {
public:
    plModifier();

    DECLARE_CREATABLE(plModifier)
};


DllClass plSingleModifier : public plModifier {
protected:
    plSceneObject* fTarget;
    hsBitVector fFlags;

public:
    plSingleModifier();

    DECLARE_CREATABLE(plSingleModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};


DllClass plMultiModifier : public plModifier {
protected:
    hsTArray<plSceneObject*> fTargets;
    hsBitVector fFlags;

public:
    plMultiModifier();

    DECLARE_CREATABLE(plMultiModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
