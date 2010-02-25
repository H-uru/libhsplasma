#ifndef _PLLINKEFFECTSTRIGGERMSG_H
#define _PLLINKEFFECTSTRIGGERMSG_H

#include "plMessage.h"

DllClass plLinkEffectsTriggerMsg : public plMessage {
private:
    unsigned int fInvisLevel, fEffects;
    bool fLeavingAge;
    plKey fLinkKey, fLinkInAnimKey;

public:
    plLinkEffectsTriggerMsg();
    virtual ~plLinkEffectsTriggerMsg();

    DECLARE_CREATABLE(plLinkEffectsTriggerMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
