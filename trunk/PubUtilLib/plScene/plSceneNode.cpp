#include "plSceneNode.h"
#include "../plResMgr/plResManager.h"

plSceneNode::plSceneNode() { }
plSceneNode::~plSceneNode() { }

IMPLEMENT_CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

void plSceneNode::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    SceneObjects.setSizeNull(S->readInt());
	size_t i;
    for (i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i] = mgr->readKey(S);
    OtherObjects.setSize(S->readInt());
    for (i=0; i<OtherObjects.getSize(); i++)
        OtherObjects[i] = mgr->readKey(S);
}

void plSceneNode::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(SceneObjects.getSize());
	size_t i;
    for (i=0; i<SceneObjects.getSize(); i++)
        mgr->writeKey(S, SceneObjects[i]);
    S->writeInt(OtherObjects.getSize());
    for (i=0; i<OtherObjects.getSize(); i++)
        mgr->writeKey(S, OtherObjects[i]);
}

void plSceneNode::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    size_t i;
    prc->writeSimpleTag("SceneObjects");
    for (i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PoolObjects");
    for (i=0; i<OtherObjects.getSize(); i++)
        OtherObjects[i]->prcWrite(prc);
    prc->closeTag();
}
