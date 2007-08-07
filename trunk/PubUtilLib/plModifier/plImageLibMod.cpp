#include "plImageLibMod.h"
#include "../plResMgr/plResManager.h"

plImageLibMod::plImageLibMod() { }
plImageLibMod::~plImageLibMod() { }

IMPLEMENT_CREATABLE(plImageLibMod, kImageLibMod, plSingleModifier)

void plImageLibMod::read(hsStream* S) {
    plSingleModifier::read(S);

    int count = S->readInt();
    fImages.setSizeNull(count);
    for (int i=0; i<count; i++)
        fImages[i] = plResManager::inst->readKey(S);
}

void plImageLibMod::write(hsStream* S) {
    plSingleModifier::write(S);

    S->writeInt(fImages.getSize());
    for (int i=0; i<fImages.getSize(); i++)
        plResManager::inst->writeKey(S, fImages[i]);
}

void plImageLibMod::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->writeSimpleTag("Images");
    for (int i=0; i<fImages.getSize(); i++)
        fImages[i]->prcWrite(prc);
    prc->closeTag();
}
