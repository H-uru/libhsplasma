#ifndef _PLARMATUREEFFECTMSG_H
#define _PLARMATUREEFFECTMSG_H

#include "NucleusLib/pnMessage/plMessage.h"

DllClass plArmatureEffectStateMsg : public plMessage {
protected:
    hsByte fSurface;
    bool fAddSurface;

public:
    plArmatureEffectStateMsg();
    virtual ~plArmatureEffectStateMsg();

    DECLARE_CREATABLE(plArmatureEffectStateMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
