#include "plExcludeRegionMsg.h"

plExcludeRegionMsg::plExcludeRegionMsg() : fCmd(0), fSynchFlags(0) { }
plExcludeRegionMsg::~plExcludeRegionMsg() { }

IMPLEMENT_CREATABLE(plExcludeRegionMsg, kExcludeRegionMsg, plMessage)

void plExcludeRegionMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fCmd = S->readByte();
    fSynchFlags = S->readInt();
}

void plExcludeRegionMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeByte(fCmd);
    S->writeInt(fSynchFlags);
}

void plExcludeRegionMsg::prcWrite(pfPrcHelper* prc) {
    plMessage::prcWrite(prc);

    prc->startTag("ExcludeParams");
    prc->writeParam("Command", fCmd);
    prc->writeParam("SynchFlags", fSynchFlags);
    prc->endTag(true);
}
