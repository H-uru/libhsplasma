#ifndef _PLSPAWNMODIFIER_H
#define _PLSPAWNMODIFIER_H

#include "plModifier.h"

// Yeah, I dunno either...

DllClass plSpawnModifier : public plMultiModifier {
    CREATABLE(plSpawnModifier, kSpawnModifier, plMultiModifier)
};


DllClass plSpawnMod : public plModifier {
    CREATABLE(plSpawnMod, kSpawnMod, plModifier)

protected:
    bool fBool1, fDisableDraw;
    plString fAge, fPage, fObjName;

public:
    plSpawnMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
