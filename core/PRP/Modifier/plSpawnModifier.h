#ifndef _PLSPAWNMODIFIER_H
#define _PLSPAWNMODIFIER_H

#include "plModifier.h"

// Yeah, I dunno either...

DllClass plSpawnModifier : public plMultiModifier {
public:
    plSpawnModifier();
    virtual ~plSpawnModifier();

    DECLARE_CREATABLE(plSpawnModifier)
};

DllClass plSpawnMod : public plModifier {
protected:
    bool fBool1, fDisableDraw;
    plString fAge, fPage, fObjName;

public:
    plSpawnMod();
    virtual ~plSpawnMod();

    DECLARE_CREATABLE(plSpawnMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
