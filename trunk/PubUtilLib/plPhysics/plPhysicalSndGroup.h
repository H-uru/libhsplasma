#ifndef _PLPHYSICALSNDGROUP_H
#define _PLPHYSICALSNDGROUP_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"

DllClass plPhysicalSndGroup : public hsKeyedObject {
public:
    enum SoundGroup { kNone, kMetal, kGrass, kWood, kStone };

protected:
    unsigned int fGroup;
    int fCurrSlideSnd;
    hsTArray<plKey> fImpactSounds, fSlideSounds;

public:
    plPhysicalSndGroup();
    virtual ~plPhysicalSndGroup();

    DECLARE_CREATABLE(plPhysicalSndGroup)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
