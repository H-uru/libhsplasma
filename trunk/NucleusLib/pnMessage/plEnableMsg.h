#ifndef _PLENABLEMSG_H
#define _PLENABLEMSG_H

#include "plMessage.h"
#include "CoreLib/hsBitVector.h"

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
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
