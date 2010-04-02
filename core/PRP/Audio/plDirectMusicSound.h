#ifndef _PLDIRECTMUSICSOUND_H
#define _PLDIRECTMUSICSOUND_H

#include "plSound.h"

DllClass plDirectMusicSound : public plSound {
    CREATABLE(plDirectMusicSound, kDirectMusicSound, plSound)

protected:
    unsigned int fUnknown1;
    plString fFileName;

public:
    plDirectMusicSound();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
