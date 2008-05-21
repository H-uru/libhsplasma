#include "plOneShotCallbacks.h"

plOneShotCallbacks::plOneShotCallbacks() { }
plOneShotCallbacks::~plOneShotCallbacks() { }

void plOneShotCallbacks::read(hsStream* S, plResManager* mgr) {
    fCallbacks.setSize(S->readInt());
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        fCallbacks[i].fMarker = S->readSafeStr();
        fCallbacks[i].fReceiver = mgr->readKey(S);
        fCallbacks[i].fUser = S->readShort();
    }
}

void plOneShotCallbacks::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fCallbacks.getSize());
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        S->writeSafeStr(fCallbacks[i].fMarker);
        mgr->writeKey(S, fCallbacks[i].fReceiver);
        S->writeShort(fCallbacks[i].fUser);
    }
}

void plOneShotCallbacks::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plOneShotCallbacks");
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        prc->startTag("Callback");
        prc->writeParam("Marker", fCallbacks[i].fMarker);
        prc->writeParam("User", fCallbacks[i].fUser);
        prc->endTag();
        fCallbacks[i].fReceiver->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}

void plOneShotCallbacks::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "plOneShotCallbacks")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fCallbacks.setSize(tag->countChildren());
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        if (child->getName() != "Callback")
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        fCallbacks[i].fMarker = tag->getParam("Marker", "");
        fCallbacks[i].fUser = tag->getParam("User", "0").toInt();
        if (child->hasChildren())
            fCallbacks[i].fReceiver = mgr->prcParseKey(child->getFirstChild());
        child = child->getNextSibling();
    }
}
