#include "plWin32Sound.h"

/* plWin32Sound */
plWin32Sound::plWin32Sound() { }
plWin32Sound::~plWin32Sound() { }

IMPLEMENT_CREATABLE(plWin32Sound, kWin32Sound, plSound)

void plWin32Sound::IRead(hsStream* S, plResManager* mgr) {
    plSound::IRead(S, mgr);
    fChannelSelect = S->readByte();
}

void plWin32Sound::IWrite(hsStream* S, plResManager* mgr) {
    plSound::IWrite(S, mgr);
    S->writeByte(fChannelSelect);
}

void plWin32Sound::prcWrite(pfPrcHelper* prc) {
    plSound::prcWrite(prc);
    prc->startTag("ChannelSelect");
    prc->writeParam("channel", fChannelSelect);
    prc->endTag(true);
}


/* plWin32StreamingSound */
IMPLEMENT_CREATABLE(plWin32StreamingSound, kWin32StreamingSound, plWin32Sound)
