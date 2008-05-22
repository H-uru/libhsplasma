#ifndef _PLTRANSITIONMSG_H
#define _PLTRANSITIONMSG_H

#include "plMessageWithCallbacks.h"

DllClass plTransitionMsg : public plMessageWithCallbacks {
public:
    enum { kFadeIn, kFadeOut, kFadeInNoSound, kFadeOutNoSound };

protected:
    unsigned int fEffect;
    float fLengthInSecs;
    int fHoldUntilNext;

public:
    plTransitionMsg();
    virtual ~plTransitionMsg();

    DECLARE_CREATABLE(plTransitionMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
