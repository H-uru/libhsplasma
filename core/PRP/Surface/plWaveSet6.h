#ifndef _PLWAVESET6_H
#define _PLWAVESET6_H

#include "plWaveSetBase.h"

DllClass plWaveSet6 : public plWaveSetBase {
public:
    plWaveSet6();
    virtual ~plWaveSet6();

    DECLARE_CREATABLE(plWaveSet6)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
