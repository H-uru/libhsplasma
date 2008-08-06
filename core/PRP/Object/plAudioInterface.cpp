#include "plAudioInterface.h"

plAudioInterface::plAudioInterface() { }
plAudioInterface::~plAudioInterface() { }

IMPLEMENT_CREATABLE(plAudioInterface, kAudioInterface, plObjInterface)

void plAudioInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fAudible = mgr->readKey(S);
}

void plAudioInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, fAudible);
}

void plAudioInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Audible");
    fAudible->prcWrite(prc);
    prc->closeTag();
}

void plAudioInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Audible") {
        if (tag->hasChildren())
            fAudible = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

plKey plAudioInterface::getAudible() const { return fAudible; }
void plAudioInterface::setAudible(plKey audible) { fAudible = audible; }
