#include "plNotifyMsg.h"

plNotifyMsg::plNotifyMsg() : fType(0), fState(0.0f), fID(0) { }

plNotifyMsg::~plNotifyMsg() {
    for (size_t i=0; i<fEvents.getSize(); i++)
        delete fEvents[i];
}

IMPLEMENT_CREATABLE(plNotifyMsg, kNotifyMsg, plMessage)

void plNotifyMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fType = S->readInt();
    fState = S->readFloat();
    fID = (S->getVer() >= pvEoa) ? S->readByte() : S->readInt();

    fEvents.setSize(S->readInt());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i] = proEventData::read(S, mgr);
}

void plNotifyMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeInt(fType);
    S->writeFloat(fState);
    if (S->getVer() >= pvEoa)
        S->writeByte(fID);
    else
        S->writeInt(fID);

    S->writeInt(fEvents.getSize());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i]->write(S, mgr);
}

void plNotifyMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("NotifyParams");
    prc->writeParam("Type", fType);
    prc->writeParam("State", fState);
    prc->writeParam("ID", fID);
    prc->endTag(true);

    prc->writeSimpleTag("Events");
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i]->prcWrite(prc);
    prc->closeTag();
}
