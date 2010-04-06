#include "plAnimEventModifier.h"

plAnimEventModifier::plAnimEventModifier() : fCallback(NULL), fDisabled(false) { }

plAnimEventModifier::~plAnimEventModifier() {
    delete fCallback;
}

void plAnimEventModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    setCallback(plMessage::Convert(mgr->ReadCreatable(S)));
}

void plAnimEventModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    mgr->WriteCreatable(S, fCallback);
}

void plAnimEventModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Callback");
    fCallback->prcWrite(prc);
    prc->closeTag();
}

void plAnimEventModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Callback") {
        if (tag->hasChildren())
            setCallback(plMessage::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plAnimEventModifier::setCallback(plMessage* callback) {
    delete fCallback;
    fCallback = callback;
}
