#include "plMsgForwarder.h"

plMsgForwarder::plMsgForwarder() { }
plMsgForwarder::~plMsgForwarder() { }

IMPLEMENT_CREATABLE(plMsgForwarder, kMsgForwarder, hsKeyedObject)

void plMsgForwarder::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fForwardKeys.clear();
    fForwardKeys.setSize(S->readInt());
    for (size_t i=0; i<fForwardKeys.getSize(); i++)
        fForwardKeys[i] = mgr->readKey(S);
}

void plMsgForwarder::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fForwardKeys.getSize());
    for (size_t i=0; i<fForwardKeys.getSize(); i++)
        mgr->writeKey(S, fForwardKeys[i]);
}

void plMsgForwarder::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("ForwardKeys");
    for (size_t i=0; i<fForwardKeys.getSize(); i++)
        fForwardKeys[i]->prcWrite(prc);
    prc->closeTag();
}
