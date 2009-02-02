#ifndef _PLLOGICMODIFIER_H
#define _PLLOGICMODIFIER_H

#include "plLogicModBase.h"

DllClass plLogicModifier : public plLogicModBase {
protected:
    hsTArray<plKey> fConditionList;
    unsigned int fMyCursor;
    plKey fParent;

public:
    plLogicModifier();
    virtual ~plLogicModifier();

    DECLARE_CREATABLE(plLogicModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumConditions() const;
    plKey getCondition(size_t idx) const;
    void addCondition(plKey cond);
    void delCondition(size_t idx);
    void clearConditions();

    unsigned int getCursor() const;
    plKey getParent() const;

    void setCursor(unsigned int cursor);
    void setParent(plKey parent);
};

#endif
