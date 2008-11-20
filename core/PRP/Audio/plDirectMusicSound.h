#ifndef _PLDIRECTMUSICSOUND_H
#define _PLDIRECTMUSICSOUND_H

#include "plSound.h"

DllClass plDirectMusicSound : public plSound {
protected:
    unsigned int fUnknown1;
    plString fFileName;

public:
    plDirectMusicSound();
    virtual ~plDirectMusicSound();

    DECLARE_CREATABLE(plDirectMusicSound)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
