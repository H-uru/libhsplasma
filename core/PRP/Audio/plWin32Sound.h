#ifndef _PLWIN32SOUND_H
#define _PLWIN32SOUND_H

#include "plSound.h"

DllClass plWin32Sound : public plSound {
public:
    enum ChannelSelect { kLeftChannel, kRightChannel };

protected:
    unsigned char fChannelSelect;

public:
    plWin32Sound();
    virtual ~plWin32Sound();

    DECLARE_CREATABLE(plWin32Sound)

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);

public:
    unsigned char getChannel() const;
    void setChannel(unsigned char channel);
};

DllClass plWin32StreamingSound : public plWin32Sound {
public:
    DECLARE_CREATABLE(plWin32StreamingSound)
};

#endif
