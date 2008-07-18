#ifndef _PLALIASMODIFIER_H
#define _PLALIASMODIFIER_H

#include "plModifier.h"

DllClass plAliasModifier : public plSingleModifier {
protected:
    plString fAlias;

public:
    plAliasModifier();
    virtual ~plAliasModifier();

    DECLARE_CREATABLE(plAliasModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
