#ifndef _PLENABLEMSG_H
#define _PLENABLEMSG_H

#include "../pnMessage/plMessage.h"
#include "../../CoreLib/hsBitVector.h"

DllClass plEnableMsg : public plMessage {
public:
    enum { kDisable, kEnable, kDrawable, kPhysical, kAudible, kAll, kByType };

protected:
    hsBitVector fCmd, fTypes;

public:
    plEnableMsg();
    virtual ~plEnableMsg();

    DECLARE_CREATABLE(plEnableMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
