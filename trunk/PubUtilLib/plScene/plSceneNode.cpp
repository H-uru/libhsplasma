#include "plSceneNode.h"
#include "../plResMgr/plResManager.h"

plSceneNode::plSceneNode() { }
plSceneNode::~plSceneNode() { }

IMPLEMENT_CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

void plSceneNode::read(hsStream* S) {
    hsKeyedObject::read(S);

    SceneObjects.setSizeNull(S->readInt());
	size_t i;
    for (i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i] = plResManager::inst->readKey(S);
    OtherObjects.setSize(S->readInt());
    for (i=0; i<OtherObjects.getSize(); i++)
        OtherObjects[i] = plResManager::inst->readKey(S);
}

void plSceneNode::write(hsStream* S) {
    hsKeyedObject::write(S);

    S->writeInt(SceneObjects.getSize());
	size_t i;
    for (i=0; i<SceneObjects.getSize(); i++)
        plResManager::inst->writeKey(S, SceneObjects[i]);
    S->writeInt(OtherObjects.getSize());
    for (i=0; i<OtherObjects.getSize(); i++)
        plResManager::inst->writeKey(S, OtherObjects[i]);
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
