#include "plDrawInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plDrawInterface::plDrawInterface(PlasmaVer pv) { }
plDrawInterface::~plDrawInterface() { }

short plDrawInterface::ClassIndex() { return 0x0016; }

void plDrawInterface::read(hsStream *S) {
    plObjInterface::read(S);
    int count = S->readInt();
    Drawables.clear();
    Drawables.setSize(count);
    DrawableKeys.clear();
    DrawableKeys.setSize(count);
	int i;
    for (i=0; i<count; i++) {
        DrawableKeys[i] = S->readInt();
        Drawables[i] = plResManager::inst->readKey(S);
        Drawables[i]->Ref();
    }
    count = S->readInt();
    Objects.clear();
    Objects.setSize(count);
    for (i=0; i<count; i++) {
        Objects[i] = plResManager::inst->readKey(S);
        Objects[i]->Ref();
    }
}

void plDrawInterface::write(hsStream *S) {
    plObjInterface::write(S);
    S->writeInt(Drawables.getSize());
	int i;
    for (i=0; i<Drawables.getSize(); i++) {
        S->writeInt(DrawableKeys[i]);
        plResManager::inst->writeKey(S, Drawables[i]);
    }
    S->writeInt(Objects.getSize());
    for (i=0; i<Objects.getSize(); i++)
        plResManager::inst->writeKey(S, Objects[i]);
}

