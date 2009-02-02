#ifndef _PLLOGICMODBASE_H
#define _PLLOGICMODBASE_H

#include "plModifier.h"
#include "PRP/Message/plNotifyMsg.h"

DllClass plLogicModBase : public plSingleModifier {
public:
    enum Flags {
        kLocalElement, kReset, kTriggered, kOneShot, kRequestingTrigger,
        kTypeActivator, kMultiTrigger
    };

protected:
    hsTArray<plMessage*> fCommandList;
    hsBitVector fLogicFlags;
    plNotifyMsg* fNotify;
    bool fDisabled;

public:
    plLogicModBase();
    virtual ~plLogicModBase();

    DECLARE_CREATABLE(plLogicModBase)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumCommands() const;
    plMessage* getCommand(size_t idx) const;
    void addCommand(plMessage* cmd);
    void delCommand(size_t idx);
    void clearCommands();

    plNotifyMsg* getNotify() const;
    bool isDisabled() const;

    void setNotify(plNotifyMsg* notify);
    void setDisabled(bool disabled);

    hsBitVector& getLogicFlags();
};

#endif
