#ifndef _PLWAVESETBASE_H
#define _PLWAVESETBASE_H

#include "PRP/Modifier/plModifier.h"

DllClass plWaveSetBase : public plMultiModifier {
public:
    plWaveSetBase();
    virtual ~plWaveSetBase();

    DECLARE_CREATABLE(plWaveSetBase)
};

#endif
