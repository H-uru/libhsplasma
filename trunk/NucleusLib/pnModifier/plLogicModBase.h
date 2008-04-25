#ifndef _PLLOGICMODBASE_H
#define _PLLOGICMODBASE_H

#include "plModifier.h"
#include "NucleusLib/pnMessage/plNotifyMsg.h"

DllClass plLogicModBase : public plSingleModifier {
public:
    enum Flags {
        kLocalElement, kReset, kTriggered, kOneShot, kRequestingTrigger,
        kTypeActivator, kMultiTrigger
    };

protected:
    hsTArray<plMessage*> fCommandList;
    hsTArray<plKey> fReceiverList;
    hsBitVector fLogicFlags;
    plNotifyMsg* fNotify;
    bool fDisabled;

public:
    plLogicModBase();
    virtual ~plLogicModBase();

    DECLARE_CREATABLE(plLogicModBase)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
