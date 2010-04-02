#ifndef _PLWAVESET_H
#define _PLWAVESET_H

#include "PRP/Modifier/plModifier.h"
#include "plFixedWaterState6.h"
#include "plFixedWaterState7.h"

DllClass plWaveSetBase : public plMultiModifier {
    CREATABLE(plWaveSetBase, kWaveSetBase, plMultiModifier)
};


DllClass plWaveSet6 : public plWaveSetBase {
    CREATABLE(plWaveSet6, kWaveSet6, plWaveSetBase)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plWaveSet7 : public plWaveSetBase {
    CREATABLE(plWaveSet7, kWaveSet7, plWaveSetBase)

public:
    enum { kHasRefObject = 0x10 };

protected:
    plFixedWaterState7 fState;
    float fMaxLen;
    hsTArray<plKey> fShores, fDecals;
    plKey fEnvMap, fRefObj;

public:
    plWaveSet7();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
