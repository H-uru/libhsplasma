#include "plSceneObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plSceneObject::plSceneObject(PlasmaVer pv) {
    DrawIntf = new plKey();
    SimIntf = new plKey();
    CoordIntf = new plKey();
    AudioIntf = new plKey();
    SceneNode = new plKey();
}

plSceneObject::~plSceneObject() {
    DrawIntf->UnRef();
    SimIntf->UnRef();
    CoordIntf->UnRef();
    AudioIntf->UnRef();
    SceneNode->UnRef();
	int i;
    for (i=0; i<Interfaces.getSize(); i++)
        Interfaces[i]->UnRef();
    for (i=0; i<Modifiers.getSize(); i++)
        Modifiers[i]->UnRef();
}

void plSceneObject::read(hsStream *S) {
    plSynchedObject::read(S);

    DrawIntf = plResManager::inst->readKey(S);
    DrawIntf->Ref();
    SimIntf = plResManager::inst->readKey(S);
    SimIntf->Ref();
    CoordIntf = plResManager::inst->readKey(S);
    CoordIntf->Ref();
    AudioIntf = plResManager::inst->readKey(S);
    AudioIntf->Ref();

    Interfaces.setSize(S->readInt());
	int i;
    for (i=0; i<Interfaces.getSize(); i++) {
        Interfaces[i] = plResManager::inst->readKey(S);
        Interfaces[i]->Ref();
    }
    Modifiers.setSize(S->readInt());
    for (i=0; i<Modifiers.getSize(); i++) {
        Modifiers[i] = plResManager::inst->readKey(S);
        Modifiers[i]->Ref();
    }

    SceneNode = plResManager::inst->readKey(S);
    SceneNode->Ref();
}

void plSceneObject::write(hsStream *S) {
    plSynchedObject::write(S);

    plResManager::inst->writeKey(S, DrawIntf);
    plResManager::inst->writeKey(S, SimIntf);
    plResManager::inst->writeKey(S, CoordIntf);
    plResManager::inst->writeKey(S, AudioIntf);

    S->writeInt(Interfaces.getSize());
	int i;
    for (i=0; i<Interfaces.getSize(); i++)
        plResManager::inst->writeKey(S, Interfaces[i]);
    S->writeInt(Modifiers.getSize());
    for (i=0; i<Modifiers.getSize(); i++)
        plResManager::inst->writeKey(S, Modifiers[i]);
    plResManager::inst->writeKey(S, SceneNode);
}

