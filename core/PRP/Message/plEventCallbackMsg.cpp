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

void plEventCallbackMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "EventCallback") {
        fEventTime = tag->getParam("EventTime", "0").toFloat();
        fEvent = (CallbackEvent)tag->getParam("Event", "0").toInt();
        fIndex = tag->getParam("Index", "0").toInt();
        fRepeats = tag->getParam("Repeats", "0").toInt();
        fUser = tag->getParam("User", "0").toInt();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

float plEventCallbackMsg::getEventTime() const { return fEventTime; }
CallbackEvent plEventCallbackMsg::getEvent() const { return fEvent; }
short plEventCallbackMsg::getIndex() const { return fIndex; }
short plEventCallbackMsg::getRepeats() const { return fRepeats; }
short plEventCallbackMsg::getUser() const { return fUser; }

void plEventCallbackMsg::setEventTime(float time) { fEventTime = time; }
void plEventCallbackMsg::setEvent(CallbackEvent evt) { fEvent = evt; }
void plEventCallbackMsg::setIndex(short idx) { fIndex = idx; }
void plEventCallbackMsg::setRepeats(short repeats) { fRepeats = repeats; }
void plEventCallbackMsg::setUser(short user) { fUser = user; }
