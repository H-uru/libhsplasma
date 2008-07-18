#ifndef _PLLOGICMODIFIER_H
#define _PLLOGICMODIFIER_H

#include "plLogicModBase.h"

DllClass plLogicModifier : public plLogicModBase {
protected:
    hsTArray<plKey> fConditionList;
    unsigned int fMyCursor;
    plWeakKey fParent;

public:
    plLogicModifier();
    virtual ~plLogicModifier();

    DECLARE_CREATABLE(plLogicModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
