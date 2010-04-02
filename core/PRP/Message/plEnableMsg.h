#ifndef _PLENABLEMSG_H
#define _PLENABLEMSG_H

#include "plMessage.h"
#include "Util/hsBitVector.h"

DllClass plEnableMsg : public plMessage {
    CREATABLE(plEnableMsg, kEnableMsg, plMessage)

public:
    enum { kDisable, kEnable, kDrawable, kPhysical, kAudible, kAll, kByType };

protected:
    hsBitVector fCmd, fTypes;

public:
    plEnableMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
