#include "plLinkToAgeMsg.h"

plLinkToAgeMsg::plLinkToAgeMsg() : fStreamVersion(0) { }
plLinkToAgeMsg::~plLinkToAgeMsg() { }

IMPLEMENT_CREATABLE(plLinkToAgeMsg, kLinkToAgeMsg, plMessage)

void plLinkToAgeMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fStreamVersion = S->readByte();
    fAgeLink.read(S, mgr);
    fLinkInAnimName = S->readSafeStr();
}

void plLinkToAgeMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeByte(fStreamVersion);
    fAgeLink.write(S, mgr);
    S->writeSafeStr(fLinkInAnimName);
}

void plLinkToAgeMsg::prcWrite(pfPrcHelper* prc) {
    plMessage::prcWrite(prc);

    prc->startTag("LinkParams");
    prc->writeParam("LinkInAnimName", fLinkInAnimName);
    prc->writeParam("StreamVersion", fStreamVersion);
    prc->endTag(true);
    fAgeLink.prcWrite(prc);
}
