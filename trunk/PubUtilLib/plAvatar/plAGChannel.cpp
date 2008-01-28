#include "plAGChannel.h"

plAGChannel::plAGChannel() { }
plAGChannel::~plAGChannel() { }

IMPLEMENT_CREATABLE(plAGChannel, kAGChannel, plCreatable)

void plAGChannel::read(hsStream* S, plResManager* mgr) {
    fName = S->readSafeStr();
}

void plAGChannel::write(hsStream* S, plResManager* mgr) {
    S->writeSafeStr(fName);
}

void plAGChannel::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->startTag("AGChannelParams");
    prc->writeParam("Name", fName);
    prc->endTag(true);
}
