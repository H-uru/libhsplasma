#include "plSceneNode.h"
#include "../plResMgr/plResManager.h"

plSceneNode::plSceneNode(PlasmaVer pv) { }
plSceneNode::~plSceneNode() { }

void plSceneNode::read(hsStream *S) {
    hsKeyedObject::read(S);

    SceneObjects.setSize(S->readInt());
    for (int i=0; i<SceneObjects.getSize(); i++) {
        SceneObjects[i] = plResManager::inst->readKey(S);
        SceneObjects[i]->Ref();
    }
    OtherObjects.setSize(S->readInt());
    for (int i=0; i<OtherObjects.getSize(); i++) {
        OtherObjects[i] = plResManager::inst->readKey(S);
        OtherObjects[i]->Ref();
    }
}

void plSceneNode::write(hsStream *S) {
    hsKeyedObject::write(S);

    S->writeInt(SceneObjects.getSize());
    for (int i=0; i<SceneObjects.getSize(); i++)
        plResManager::inst->writeKey(S, SceneObjects[i]);
    S->writeInt(OtherObjects.getSize());
    for (int i=0; i<OtherObjects.getSize(); i++)
        plResManager::inst->writeKey(S, OtherObjects[i]);
}

