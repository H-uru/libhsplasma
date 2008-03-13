#ifndef _PLBLOWER_H
#define _PLBLOWER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plBlower : public plSingleModifier {
public:
    DllStruct Oscillator {
        float fFrequency, fPhase, fPower;
    };

protected:
    float fMasterPower, fDirectRate, fImpulseRate, fSpringKonst;

public:
    plBlower();
    virtual ~plBlower();

    DECLARE_CREATABLE(plBlower)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
