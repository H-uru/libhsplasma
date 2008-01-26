#ifndef _PLRANDOMSOUNDMOD_H
#define _PLRANDOMSOUNDMOD_H

#include "FeatureLib/pfAnimation/plRandomCommandMod.h"

DllClass plRandomSoundModGroup {
protected:
    hsBitVector fExcluded;
    signed char fCurrent;
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
    unsigned short fCurrentGroup, fNumGroups;
    hsTArray<plRandomSoundModGroup> fGroups;
    hsTArray<unsigned short> fActiveList;
    int fOldPriority;
    bool fFirstTimePlay;

public:
    plRandomSoundMod();
    virtual ~plRandomSoundMod();

    DECLARE_CREATABLE(plRandomSoundMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
