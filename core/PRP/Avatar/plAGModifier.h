#ifndef _PLAGMODIFIER_H
#define _PLAGMODIFIER_H

#include "PRP/Modifier/plModifier.h"

DllClass plAGModifier : public plSingleModifier {
protected:
    plString fChannelName;
    bool fAutoApply, fEnabled;

public:
    plAGModifier();
    virtual ~plAGModifier();

    DECLARE_CREATABLE(plAGModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
