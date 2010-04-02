#ifndef _PLWIN32SOUND_H
#define _PLWIN32SOUND_H

#include "plSound.h"

DllClass plWin32Sound : public plSound {
    CREATABLE(plWin32Sound, kWin32Sound, plSound)

public:
    enum ChannelSelect { kLeftChannel, kRightChannel };

protected:
    unsigned char fChannelSelect;

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);

public:
    unsigned char getChannel() const { return fChannelSelect; }
    void setChannel(unsigned char channel) { fChannelSelect = channel; }
};

DllClass plWin32StreamingSound : public plWin32Sound {
    CREATABLE(plWin32StreamingSound, kWin32StreamingSound, plWin32Sound)
};

#endif
