#ifndef _PLWIN32STATICSOUND_H
#define _PLWIN32STATICSOUND_H

#include "plWin32Sound.h"

DllClass plWin32StaticSound : public plWin32Sound {
protected:
    bool fRegisteredOnThread;

public:
    DECLARE_CREATABLE(plWin32StaticSound)
};

DllClass plWin32GroupedSound : public plWin32StaticSound {
protected:
    unsigned short fCurrentSound;
    unsigned int fCurrentSoundLength;
    hsTArray<unsigned int> fStartPositions;
    hsTArray<float> fVolumes;
    unsigned char fNumDestChannels, fNumDestBytesPerSample;

public:
    DECLARE_CREATABLE(plWin32GroupedSound)

    virtual void IPrcWrite(pfPrcHelper* prc);

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
};

DllClass plWin32LinkSound : public plWin32StaticSound {
public:
    DECLARE_CREATABLE(plWin32LinkSound)

    virtual void read(hsStream* S, plResManager* mgr);
};

#endif
