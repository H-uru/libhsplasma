#include "pfKIMsg.h"

pfKIMsg::pfKIMsg()
       : fCommand(kNoCommand), fFlags(0), fPlayerID(0), fDelay(0.0f), fValue(0) {
    fBCastFlags |= kBCastByExactType;
}

pfKIMsg::~pfKIMsg() { }

IMPLEMENT_CREATABLE(pfKIMsg, kKIMsg, plMessage)

void pfKIMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCommand = S->readByte();
    fUser = S->readSafeStr();
    fPlayerID = S->readInt();
    fString = S->readSafeWStr();
    fFlags = S->readInt();
    fDelay = S->readFloat();
    fValue = S->readInt();
}

void pfKIMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeByte(fCommand);
    S->writeSafeStr(fUser);
    S->writeInt(fPlayerID);
    S->writeSafeWStr(fString);
    S->writeInt(fFlags);
    S->writeFloat(fDelay);
    S->writeInt(fValue);
}

void pfKIMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("Parameters");
    prc->writeParam("Command", fCommand);
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Delay", fDelay);
    prc->writeParam("Value", fValue);
    prc->endTag(true);

    prc->startTag("Player");
    prc->writeParam("ID", fPlayerID);
    prc->writeParam("User", fUser);
    prc->endTag(true);

    prc->startTag("Message");
    prc->writeParam("value", hsWStringToString(fString));
    prc->endTag(true);
}

void pfKIMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if(tag->getName() == "Parameters") {
        fCommand = (hsUbyte)tag->getParam("Command", "0").toInt();
        fFlags = tag->getParam("Flags", "0").toInt();
        fDelay = tag->getParam("Delay", "0.0").toFloat();
        fValue = tag->getParam("Value", "0").toInt();
    } else if (tag->getName() == "Player") {
        fUser = tag->getParam("User", "");
        fPlayerID = tag->getParam("ID", "0").toInt();
    } else if (tag->getName() == "Message") {
        fString = hsStringToWString(tag->getParam("value", ""));
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
