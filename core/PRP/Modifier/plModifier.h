#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "PRP/Object/plSynchedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsBitVector.h"

DllClass plModifier : public plSynchedObject {
    CREATABLE(plModifier, kModifier, plSynchedObject)
};


DllClass plSingleModifier : public plModifier {
    CREATABLE(plSingleModifier, kSingleModifier, plModifier)

protected:
    hsBitVector fFlags;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const { return fFlags.get(flag); }
    void setFlag(size_t flag, bool value) { fFlags.set(flag, value); }
};


DllClass plMultiModifier : public plModifier {
    CREATABLE(plMultiModifier, kMultiModifier, plModifier)

protected:
    hsBitVector fFlags;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const { return fFlags.get(flag); }
    void setFlag(size_t flag, bool value) { fFlags.set(flag, value); }
};


/* Misc empty modifiers that don't make sense to put elsewhere */
DllClass plElevatorModifier : public plSingleModifier {
    CREATABLE(plElevatorModifier, kElevatorModifier, plSingleModifier)
};

#endif
