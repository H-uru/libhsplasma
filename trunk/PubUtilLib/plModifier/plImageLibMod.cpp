#include "plImageLibMod.h"
#include "../plResMgr/plResManager.h"

plImageLibMod::plImageLibMod(PlasmaVer pv) { }
plImageLibMod::~plImageLibMod() { }

short plImageLibMod::ClassIndex() {
    return (ver == pvEoa ? 0x00F1 : 0x0122);
}
const char* plImageLibMod::ClassName() { return "plImageLibMod"; }

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

void plImageLibMod::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSingleModifier::prcWrite(S, prc);

    prc->writeSimpleTag("Images");
    for (int i=0; i<fImages.getSize(); i++)
        fImages[i]->prcWrite(S, prc);
    prc->closeTag();
}
