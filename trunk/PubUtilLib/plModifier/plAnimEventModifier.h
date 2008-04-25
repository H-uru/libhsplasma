#ifndef _PLANIMEVENTMODIFIER_H
#define _PLANIMEVENTMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plAnimEventModifier : public plSingleModifier {
protected:
    hsTArray<plKey> fReceivers;
    plMessage* fCallback;
    bool fDisabled;

public:
    plAnimEventModifier();
    virtual ~plAnimEventModifier();

    DECLARE_CREATABLE(plAnimEventModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
