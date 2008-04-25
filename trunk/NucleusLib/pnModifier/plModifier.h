#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "NucleusLib/pnSceneObject/plSceneObject.h"
#include "CoreLib/hsBitVector.h"

DllClass plModifier : public plSynchedObject {
public:
    plModifier();
    virtual ~plModifier();

    DECLARE_CREATABLE(plModifier)
};


DllClass plSingleModifier : public plModifier {
protected:
    hsBitVector fFlags;

public:
    plSingleModifier();
    virtual ~plSingleModifier();

    DECLARE_CREATABLE(plSingleModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};


DllClass plMultiModifier : public plModifier {
protected:
    hsBitVector fFlags;

public:
    plMultiModifier();
    virtual ~plMultiModifier();

    DECLARE_CREATABLE(plMultiModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
