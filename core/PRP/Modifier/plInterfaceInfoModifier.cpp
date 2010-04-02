#include "plInterfaceInfoModifier.h"

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

void plInterfaceInfoModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeyList.getSize(); i++)
        fKeyList[i]->prcWrite(prc);
    prc->closeTag();
}

void plInterfaceInfoModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Keys") {
        fKeyList.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fKeyList.getSize(); i++) {
            fKeyList[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
