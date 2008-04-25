#include "plEventCallbackMsg.h"

plEventCallbackMsg::plEventCallbackMsg() { }
plEventCallbackMsg::~plEventCallbackMsg() { }

IMPLEMENT_CREATABLE(plEventCallbackMsg, kEventCallbackMsg, plMessage)

void plEventCallbackMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fEventTime = S->readFloat();
    fEvent = (CallbackEvent)S->readShort();
    fIndex = S->readShort();
    fRepeats = S->readShort();
    fUser = S->readShort();
}

void plEventCallbackMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeFloat(fEventTime);
    S->writeShort(fEvent);
    S->writeShort(fIndex);
    S->writeShort(fRepeats);
    S->writeShort(fUser);
}

void plEventCallbackMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("EventCallback");
    prc->writeParam("EventTime", fEventTime);
    prc->writeParam("Event", fEvent);
    prc->writeParam("Index", fIndex);
    prc->writeParam("Repeats", fRepeats);
    prc->writeParam("User", fUser);
    prc->endTag(true);
}
