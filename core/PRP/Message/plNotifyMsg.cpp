#include "plNotifyMsg.h"

plNotifyMsg::plNotifyMsg() : fType(0), fID(0), fState(0.0f) { }

plNotifyMsg::~plNotifyMsg() {
    for (size_t i=0; i<fEvents.getSize(); i++) {
        if (fEvents[i] != NULL)
            delete fEvents[i];
    }
}

IMPLEMENT_CREATABLE(plNotifyMsg, kNotifyMsg, plMessage)

void plNotifyMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fType = S->readInt();
    fState = S->readFloat();
    fID = (S->getVer() >= pvEoa) ? S->readByte() : S->readInt();

    fEvents.setSizeNull(S->readInt());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i] = proEventData::Read(S, mgr);
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

void plNotifyMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "NotifyParams") {
        fType = tag->getParam("Type", "0").toInt();
        fState = tag->getParam("State", "0").toFloat();
        fID = tag->getParam("ID", "0").toInt();
    } else if (tag->getName() == "Events") {
        fEvents.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEvents.getSize(); i++) {
            fEvents[i] = proEventData::PrcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

int plNotifyMsg::getType() const { return fType; }
float plNotifyMsg::getState() const { return fState; }
int plNotifyMsg::getID() const { return fID; }

void plNotifyMsg::setType(int type) { fType = type; }
void plNotifyMsg::setState(float state) { fState = state; }
void plNotifyMsg::setID(int id) { fID = id; }

size_t plNotifyMsg::getNumEvents() const { return fEvents.getSize(); }
proEventData* plNotifyMsg::getEvent(size_t idx) const { return fEvents[idx]; }
void plNotifyMsg::addEvent(proEventData* evt) { fEvents.append(evt); }

void plNotifyMsg::delEvent(size_t idx) {
    if (fEvents[idx] != NULL)
        delete fEvents[idx];
    fEvents.remove(idx);
}

void plNotifyMsg::clearEvents() {
    for (size_t i=0; i<fEvents.getSize(); i++) {
        if (fEvents[i] != NULL)
            delete fEvents[i];
    }
    fEvents.clear();
}
