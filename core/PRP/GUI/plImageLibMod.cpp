#include "plImageLibMod.h"

plImageLibMod::plImageLibMod() { }
plImageLibMod::~plImageLibMod() { }

IMPLEMENT_CREATABLE(plImageLibMod, kImageLibMod, plSingleModifier)

void plImageLibMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fImages.setSize(S->readInt());
    for (size_t i=0; i<fImages.getSize(); i++)
        fImages[i] = mgr->readKey(S);
}

void plImageLibMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fImages.getSize());
    for (size_t i=0; i<fImages.getSize(); i++)
        mgr->writeKey(S, fImages[i]);
}

void plImageLibMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Images");
    for (size_t i=0; i<fImages.getSize(); i++)
        fImages[i]->prcWrite(prc);
    prc->closeTag();
}

void plImageLibMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Images") {
        fImages.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fImages.getSize(); i++) {
            fImages[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
