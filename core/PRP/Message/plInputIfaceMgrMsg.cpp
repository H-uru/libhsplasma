#include "plInputIfaceMgrMsg.h"

plInputIfaceMgrMsg::plInputIfaceMgrMsg() : fCommand(0), fPageID(0) {
    fBCastFlags |= kBCastByExactType;
}

void plInputIfaceMgrMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCommand = S->readByte();
    fPageID = S->readInt();
    fAgeName = S->readSafeStr();
    fAgeFilename = S->readSafeStr();
    fSpawnPoint = S->readSafeStr();
    fAvKey = mgr->readKey(S);
}

void plInputIfaceMgrMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeByte(fCommand);
    S->writeInt(fPageID);
    S->writeSafeStr(fAgeName);
    S->writeSafeStr(fAgeFilename);
    S->writeSafeStr(fSpawnPoint);
    mgr->writeKey(S, fAvKey);
}

void plInputIfaceMgrMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("InputIfaceMgrParams");
    prc->writeParam("Command", fCommand);
    prc->writeParam("PageID", fPageID);
    prc->writeParam("AgeName", fAgeName);
    prc->writeParam("AgeFilename", fAgeFilename);
    prc->writeParam("SpawnPoint", fSpawnPoint);
    prc->endTag(true);

    prc->writeSimpleTag("AvatarKey");
    fAvKey->prcWrite(prc);
    prc->closeTag();
}

void plInputIfaceMgrMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "InputIfaceMgrParams") {
        fCommand = tag->getParam("Command", "0").toUint();
        fPageID = tag->getParam("PageID", "0").toUint();
        fAgeName = tag->getParam("AgeName", "");
        fAgeFilename = tag->getParam("AgeFilename", "");
        fSpawnPoint = tag->getParam("SpawnPoint", "");
    } else if (tag->getName() == "AvKey") {
        if (tag->hasChildren())
            fAvKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
