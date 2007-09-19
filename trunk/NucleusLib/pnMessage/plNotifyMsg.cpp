#include "plNotifyMsg.h"

plNotifyMsg::plNotifyMsg() : fType(0), fState(0.0f), fID(0) { }

plNotifyMsg::~plNotifyMsg() {
    for (size_t i=0; i<fEvents.getSize(); i++)
        delete fEvents[i];
}

IMPLEMENT_CREATABLE(plNotifyMsg, kNotifyMsg, plMessage)

void plNotifyMsg::read(hsStream* S, plResManager* mgr) {
    IMsgRead(S, mgr);
    fType = S->readInt();
    fState = S->readFloat();
    fID = S->readInt();

    fEvents.setSize(S->readInt());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i] = proEventData::read(S, mgr);
}

void plNotifyMsg::write(hsStream* S, plResManager* mgr) {
    IMsgWrite(S, mgr);
    S->writeInt(fType);
    S->writeFloat(fState);
    S->writeInt(fID);

    S->writeInt(fEvents.getSize());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i]->write(S, mgr);
}

void plNotifyMsg::prcWrite(pfPrcHelper* prc) {
    // Later
}
