#include "plSceneObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plSceneObject::plSceneObject() { }
plSceneObject::~plSceneObject() { }

IMPLEMENT_CREATABLE(plSceneObject, kSceneObject, plSynchedObject)

void plSceneObject::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    DrawIntf = mgr->readKey(S);
    SimIntf = mgr->readKey(S);
    CoordIntf = mgr->readKey(S);
    AudioIntf = mgr->readKey(S);

    Interfaces.setSizeNull(S->readInt());
	size_t i;
    for (i=0; i<Interfaces.getSize(); i++)
        Interfaces[i] = mgr->readKey(S);
    Modifiers.setSizeNull(S->readInt());
    for (i=0; i<Modifiers.getSize(); i++)
        Modifiers[i] = mgr->readKey(S);

    SceneNode = mgr->readKey(S);
}

void plSceneObject::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, DrawIntf);
    mgr->writeKey(S, SimIntf);
    mgr->writeKey(S, CoordIntf);
    mgr->writeKey(S, AudioIntf);

    S->writeInt(Interfaces.getSize());
    size_t i;
    for (i=0; i<Interfaces.getSize(); i++)
        mgr->writeKey(S, Interfaces[i]);
    S->writeInt(Modifiers.getSize());
    for (i=0; i<Modifiers.getSize(); i++)
        mgr->writeKey(S, Modifiers[i]);
    mgr->writeKey(S, SceneNode);
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
