#ifndef _PLARMATUREEFFECTMSG_H
#define _PLARMATUREEFFECTMSG_H

#include "plMessage.h"

DllClass plArmatureEffectStateMsg : public plMessage {
    CREATABLE(plArmatureEffectStateMsg, kArmatureEffectStateMsg, plMessage)

protected:
    hsByte fSurface;
    bool fAddSurface;

public:
    plArmatureEffectStateMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
