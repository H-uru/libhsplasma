#include "plInterfaceInfoModifier.h"

plInterfaceInfoModifier::plInterfaceInfoModifier() { }
plInterfaceInfoModifier::~plInterfaceInfoModifier() { }

IMPLEMENT_CREATABLE(plInterfaceInfoModifier, kInterfaceInfoModifier, plSingleModifier)

void plInterfaceInfoModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fKeyList.setSize(S->readInt());
    for (size_t i=0; i<fKeyList.getSize(); i++)
        fKeyList[i] = mgr->readKey(S);
}

void plInterfaceInfoModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fKeyList.getSize());
    for (size_t i=0; i<fKeyList.getSize(); i++)
        mgr->writeKey(S, fKeyList[i]);
}

void plInterfaceInfoModifier::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeyList.getSize(); i++)
        fKeyList[i]->prcWrite(prc);
    prc->closeTag();
}
