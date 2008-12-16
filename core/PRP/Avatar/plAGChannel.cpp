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

void plAGChannel::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Channel");
    prc->writeParam("Name", fName);
    prc->endTag(true);
}

void plAGChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Channel") {
        fName = tag->getParam("Name", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plString plAGChannel::getName() const { return fName; }
void plAGChannel::setName(const plString& name) { fName = name; }
