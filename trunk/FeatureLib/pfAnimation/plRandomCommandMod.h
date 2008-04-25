#ifndef _PLRANDOMCOMMANDMOD_H
#define _PLRANDOMCOMMANDMOD_H

#include "NucleusLib/pnModifier/plModifier.h"
#include "CoreLib/hsBitVector.h"

DllClass plRandomCommandMod : public plSingleModifier {
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
    virtual ~plRandomCommandMod();

    DECLARE_CREATABLE(plRandomCommandMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
