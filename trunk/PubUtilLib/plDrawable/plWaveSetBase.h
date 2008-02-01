#ifndef _PLWAVESETBASE_H
#define _PLWAVESETBASE_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plWaveSetBase : public plMultiModifier {
public:
    plWaveSetBase();
    virtual ~plWaveSetBase();

    DECLARE_CREATABLE(plWaveSetBase)
};

#endif
