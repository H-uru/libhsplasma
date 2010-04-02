#ifndef _PLRANDOMSOUNDMOD_H
#define _PLRANDOMSOUNDMOD_H

#include "plRandomCommandMod.h"

DllClass plRandomSoundModGroup {
protected:
    hsTArray<unsigned short> fIndices;
    short fGroupedIdx;

public:
    plRandomSoundModGroup();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


DllClass plRandomSoundMod : public plRandomCommandMod {
    CREATABLE(plRandomSoundMod, kRandomSoundMod, plRandomCommandMod)

protected:
    hsTArray<plRandomSoundModGroup> fGroups;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
