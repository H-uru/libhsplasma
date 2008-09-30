#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "PRP/Object/plSynchedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsBitVector.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const;
    void setFlag(size_t flag);
    void clearFlag(size_t flag);
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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const;
    void setFlag(size_t flag);
    void clearFlag(size_t flag);
};

#endif
