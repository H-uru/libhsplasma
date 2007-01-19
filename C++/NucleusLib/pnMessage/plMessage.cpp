#include "plMessage.h"

plMessage::plMessage(PlasmaVer pv) { }
plMessage::~plMessage() { }

void plMessage::IMsgRead(hsStream* S) {
    fSender.readRef(S);
    fReceivers.setSize(S->readInt());
    for (int i=0; i<fReceivers.getSize(); i++)
        fReceivers[i].readRef(S);
    fTimeStamp = S->readDouble();
    fBCastFlags = S->readInt();
}

void plMessage::IMsgWrite(hsStream* S) {
    fSender.writeRef(S);
    S->writeInt(fReceivers.getSize());
    for (int i=0; i<fReceivers.getSize(); i++)
        fReceivers[i].writeRef(S);
    S->writeDouble(fTimeStamp);
    S->writeInt(fBCastFlags);
}

