#ifndef _PLRANDOMCOMMANDMOD_H
#define _PLRANDOMCOMMANDMOD_H

#include "plModifier.h"
#include "Util/hsBitVector.h"

DllClass plRandomCommandMod : public plSingleModifier {
    CREATABLE(plRandomCommandMod, kRandomCommandMod, plSingleModifier)

public:
    enum {
        kNormal = 0,
        kNoRepeats = 0x1,
        kCoverall = 0x2,
        kOneCycle = 0x4,
        kOneCmd = 0x8,
        kDelayFromEnd = 0x10,
        kSequential = 0x20
    };

    enum { kStopped = 0x1 };

protected:
    unsigned char fState, fMode;
    float fMinDelay, fMaxDelay;

public:
    plRandomCommandMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
