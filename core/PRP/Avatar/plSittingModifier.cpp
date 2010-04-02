#include "plSittingModifier.h"

plSittingModifier::plSittingModifier() : fMiscFlags(0) { }

void plSittingModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fMiscFlags = S->readByte();
    fNotifyKeys.setSize(S->readInt());
    for (size_t i=0; i<fNotifyKeys.getSize(); i++)
        fNotifyKeys[i] = mgr->readKey(S);
}

void plSittingModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeByte(fMiscFlags);
    S->writeInt(fNotifyKeys.getSize());
    for (size_t i=0; i<fNotifyKeys.getSize(); i++)
        mgr->writeKey(S, fNotifyKeys[i]);
}

void plSittingModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("SittingModParams");
    prc->writeParamHex("MiscFlags", fMiscFlags);
    prc->endTag(true);

    prc->writeSimpleTag("NotifyKeys");
    for (size_t i=0; i<fNotifyKeys.getSize(); i++)
        fNotifyKeys[i]->prcWrite(prc);
    prc->closeTag();
}

void plSittingModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SittingModParams") {
        fMiscFlags = tag->getParam("MiscFlags", "0").toUint();
    } else if (tag->getName() == "NotifyKeys") {
        fNotifyKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNotifyKeys.getSize(); i++) {
            fNotifyKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
