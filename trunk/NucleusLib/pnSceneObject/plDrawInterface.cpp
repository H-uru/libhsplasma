#include "plDrawInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plDrawInterface::plDrawInterface() { }
plDrawInterface::~plDrawInterface() { }

IMPLEMENT_CREATABLE(plDrawInterface, kDrawInterface, plObjInterface)

void plDrawInterface::read(hsStream* S) {
    plObjInterface::read(S);
    size_t count = S->readInt();
    Drawables.clear();
    Drawables.setSize(count);
    DrawableKeys.clear();
    DrawableKeys.setSize(count);
	size_t i;
    for (i=0; i<count; i++) {
        DrawableKeys[i] = S->readInt();
        Drawables[i] = plResManager::inst->readKey(S);
    }
    count = S->readInt();
    Objects.clear();
    Objects.setSize(count);
    for (i=0; i<count; i++)
        Objects[i] = plResManager::inst->readKey(S);
}

void plDrawInterface::write(hsStream* S) {
    plObjInterface::write(S);
    S->writeInt(Drawables.getSize());
	size_t i;
    for (i=0; i<Drawables.getSize(); i++) {
        S->writeInt(DrawableKeys[i]);
        plResManager::inst->writeKey(S, Drawables[i]);
    }
    S->writeInt(Objects.getSize());
    for (i=0; i<Objects.getSize(); i++)
        plResManager::inst->writeKey(S, Objects[i]);
}

void plDrawInterface::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    size_t i;
    prc->writeSimpleTag("Drawables");
    for (i=0; i<Drawables.getSize(); i++) {
        prc->startTag("DrawableKey");
        prc->writeParam("value", DrawableKeys[i]);
        prc->endTag(true);
        Drawables[i]->prcWrite(prc);
    }
    prc->closeTag();
    prc->writeSimpleTag("Objects");
    for (i=0; i<Objects.getSize(); i++)
        Objects[i]->prcWrite(prc);
    prc->closeTag();
}
