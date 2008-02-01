#ifndef _PLWAVESET7_H
#define _PLWAVESET7_H

#include "plWaveSetBase.h"
#include "plFixedWaterState7.h"

/* Yes, this is greatly simplified...  And it'll probably stay that way
 * unless I implement the actual rendering of plWaveSets
 */

DllClass plWaveSet7 : public plWaveSetBase {
public:
    enum { kHasRefObject = 0x10 };

protected:
    plFixedWaterState7 fState;
    float fMaxLen;
    hsTArray<plKey> fShores, fDecals;
    plKey fEnvMap, fRefObj;

public:
    plWaveSet7();
    virtual ~plWaveSet7();

    DECLARE_CREATABLE(plWaveSet7)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
