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

void plLinkToAgeMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("LinkParams");
    prc->writeParam("LinkInAnimName", fLinkInAnimName);
    prc->writeParam("StreamVersion", fStreamVersion);
    prc->endTag(true);
    fAgeLink.prcWrite(prc);
}

void plLinkToAgeMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LinkParams") {
        fLinkInAnimName = tag->getParam("LinkInAnimName", "");
        fStreamVersion = tag->getParam("StreamVersion", "0").toInt();
    } else if (tag->getName() == "plAgeLinkStruct") {
        fAgeLink.prcParse(tag, mgr);
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
