#ifndef _PLPHYSICALSNDGROUP_H
#define _PLPHYSICALSNDGROUP_H

#include "PRP/KeyedObject/hsKeyedObject.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
