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

short plSceneObject::ClassIndex() { return 0x0001; }
const char* plSceneObject::ClassName() { return "plSceneObject"; }

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

    Interfaces.setSizeNull(S->readInt());
	int i;
    for (i=0; i<Interfaces.getSize(); i++) {
        Interfaces[i] = plResManager::inst->readKey(S);
        Interfaces[i]->Ref();
    }
    Modifiers.setSizeNull(S->readInt());
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

void plSceneObject::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);
    
    prc->writeSimpleTag("DrawInterface");
      DrawIntf->prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("SimulationInterface");
      SimIntf->prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("CoordinateInterface");
      CoordIntf->prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("AudioInterface");
      AudioIntf->prcWrite(S, prc);
    prc->closeTag();

    int i;
    prc->writeSimpleTag("Interfaces");
    for (i=0; i<Interfaces.getSize(); i++)
        Interfaces[i]->prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("Modifiers");
    for (i=0; i<Modifiers.getSize(); i++)
        Modifiers[i]->prcWrite(S, prc);
    prc->closeTag();
    
    prc->writeSimpleTag("SceneNode");
      SceneNode->prcWrite(S, prc);
    prc->closeTag();
}
