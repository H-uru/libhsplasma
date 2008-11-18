#include "plExcludeRegionMsg.h"

plExcludeRegionMsg::plExcludeRegionMsg() : fCmd(0), fSynchFlags(0) { }
plExcludeRegionMsg::~plExcludeRegionMsg() { }

IMPLEMENT_CREATABLE(plExcludeRegionMsg, kExcludeRegionMsg, plMessage)

void plExcludeRegionMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fCmd = S->readByte();
    fSynchFlags = (S->getVer() < pvEoa) ? S->readInt() : 0;
}

void plExcludeRegionMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeByte(fCmd);
    if (S->getVer() < pvEoa)
        S->writeInt(fSynchFlags);
}

void plExcludeRegionMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("ExcludeParams");
    prc->writeParam("Command", fCmd);
    prc->writeParamHex("SynchFlags", fSynchFlags);
    prc->endTag(true);
}

void plExcludeRegionMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ExcludeParams") {
        fCmd = tag->getParam("Command", "0").toUint();
        fSynchFlags = tag->getParam("SynchFlags", "0").toUint();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
