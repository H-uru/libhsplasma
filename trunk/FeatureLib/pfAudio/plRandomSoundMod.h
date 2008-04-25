#ifndef _PLRANDOMSOUNDMOD_H
#define _PLRANDOMSOUNDMOD_H

#include "FeatureLib/pfAnimation/plRandomCommandMod.h"

DllClass plRandomSoundModGroup {
protected:
    unsigned short fNumSounds;
    hsTArray<unsigned short> fIndices;
    short fGroupedIdx;

public:
    plRandomSoundModGroup();
    ~plRandomSoundModGroup();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllClass plRandomSoundMod : public plRandomCommandMod {
protected:
    unsigned short fNumGroups;
    hsTArray<plRandomSoundModGroup> fGroups;

public:
    plRandomSoundMod();
    virtual ~plRandomSoundMod();

    DECLARE_CREATABLE(plRandomSoundMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
