#ifndef _PLANIMEVENTMODIFIER_H
#define _PLANIMEVENTMODIFIER_H

#include "plModifier.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setCallback(plMessage* callback);
};

#endif
