#ifndef _PLALIASMODIFIER_H
#define _PLALIASMODIFIER_H

#include "plModifier.h"

DllClass plAliasModifier : public plSingleModifier {
    CREATABLE(plAliasModifier, kAliasModifier, plSingleModifier)

protected:
    plString fAlias;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
