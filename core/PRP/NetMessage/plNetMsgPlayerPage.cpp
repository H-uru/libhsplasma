#include "plNetMsgPlayerPage.h"

plNetMsgPlayerPage::plNetMsgPlayerPage() : fUnload(0) { }
plNetMsgPlayerPage::~plNetMsgPlayerPage() { }

IMPLEMENT_CREATABLE(plNetMsgPlayerPage, kNetMsgPlayerPage, plNetMessage)

void plNetMsgPlayerPage::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);

    fUnload = S->readByte();
    fUoid.read(S);
}

void plNetMsgPlayerPage::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    S->writeByte(fUnload);
    fUoid.write(S);
}

void plNetMsgPlayerPage::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->startTag("PlayerPageParams");
    prc->writeParam("Unload", fUnload);
    prc->endTag();
    fUoid.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgPlayerPage::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PlayerPageParams") {
        fUnload = tag->getParam("Unload", "0").toUint();
        if (tag->hasChildren())
            fUoid.prcParse(tag->getFirstChild());
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
