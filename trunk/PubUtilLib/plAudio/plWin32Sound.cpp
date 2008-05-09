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

void plWin32Sound::IPrcWrite(pfPrcHelper* prc) {
    plSound::IPrcWrite(prc);
    prc->startTag("ChannelSelect");
    prc->writeParam("channel", fChannelSelect);
    prc->endTag(true);
}

void plWin32Sound::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ChannelSelect") {
        fChannelSelect = tag->getParam("channel", "0").toUint();
    } else {
        plSound::IPrcParse(tag, mgr);
    }
}


/* plWin32StreamingSound */
IMPLEMENT_CREATABLE(plWin32StreamingSound, kWin32StreamingSound, plWin32Sound)
