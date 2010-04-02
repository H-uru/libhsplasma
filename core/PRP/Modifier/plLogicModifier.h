#ifndef _PLLOGICMODIFIER_H
#define _PLLOGICMODIFIER_H

#include "plLogicModBase.h"

DllClass plLogicModifier : public plLogicModBase {
    CREATABLE(plLogicModifier, kLogicModifier, plLogicModBase)

protected:
    hsTArray<plKey> fConditionList;
    unsigned int fMyCursor;
    plKey fParent;

public:
    plLogicModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getConditions() const { return fConditionList; }
    hsTArray<plKey>& getConditions() { return fConditionList; }
    void addCondition(plKey cond) { fConditionList.append(cond); }
    void delCondition(size_t idx) { fConditionList.remove(idx); }
    void clearConditions() { fConditionList.clear(); }

    unsigned int getCursor() const { return fMyCursor; }
    plKey getParent() const { return fParent; }

    void setCursor(unsigned int cursor) { fMyCursor = cursor; }
    void setParent(plKey parent) { fParent = parent; }
};

#endif
