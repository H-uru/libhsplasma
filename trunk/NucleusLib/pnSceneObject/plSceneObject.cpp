#include "plSceneObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plSceneObject::plSceneObject() { }
plSceneObject::~plSceneObject() { }

IMPLEMENT_CREATABLE(plSceneObject, kSceneObject, plSynchedObject)

void plSceneObject::read(hsStream* S) {
    plSynchedObject::read(S);

    DrawIntf = plResManager::inst->readKey(S);
    SimIntf = plResManager::inst->readKey(S);
    CoordIntf = plResManager::inst->readKey(S);
    AudioIntf = plResManager::inst->readKey(S);

    Interfaces.setSizeNull(S->readInt());
	size_t i;
    for (i=0; i<Interfaces.getSize(); i++)
        Interfaces[i] = plResManager::inst->readKey(S);
    Modifiers.setSizeNull(S->readInt());
    for (i=0; i<Modifiers.getSize(); i++)
        Modifiers[i] = plResManager::inst->readKey(S);

    SceneNode = plResManager::inst->readKey(S);
}

void plSceneObject::write(hsStream* S) {
    plSynchedObject::write(S);

    plResManager::inst->writeKey(S, DrawIntf);
    plResManager::inst->writeKey(S, SimIntf);
    plResManager::inst->writeKey(S, CoordIntf);
    plResManager::inst->writeKey(S, AudioIntf);

    S->writeInt(Interfaces.getSize());
    size_t i;
    for (i=0; i<Interfaces.getSize(); i++)
        plResManager::inst->writeKey(S, Interfaces[i]);
    S->writeInt(Modifiers.getSize());
    for (i=0; i<Modifiers.getSize(); i++)
        plResManager::inst->writeKey(S, Modifiers[i]);
    plResManager::inst->writeKey(S, SceneNode);
}

void plSceneObject::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);
    
    prc->writeSimpleTag("DrawInterface");
      DrawIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SimulationInterface");
      SimIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("CoordinateInterface");
      CoordIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("AudioInterface");
      AudioIntf->prcWrite(prc);
    prc->closeTag();

    size_t i;
    prc->writeSimpleTag("Interfaces");
    for (i=0; i<Interfaces.getSize(); i++)
        Interfaces[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Modifiers");
    for (i=0; i<Modifiers.getSize(); i++)
        Modifiers[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("SceneNode");
      SceneNode->prcWrite(prc);
    prc->closeTag();
}
