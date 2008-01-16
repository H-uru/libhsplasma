#ifndef _PLTRANSITIONMSG_H
#define _PLTRANSITIONMSG_H

#include "../../NucleusLib/pnMessage/plMessageWithCallbacks.h"

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
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
