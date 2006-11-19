#include "plSceneNode.h"

plSceneNode::plSceneNode() { }
plSceneNode::~plSceneNode() { }

void plSceneNode::read(hsStream *S) {
    hsKeyedObject::read(S);
    SceneObjects.read(S);
    OtherObjects.read(S);
}

void plSceneNode::write(hsStream *S) {
    hsKeyedObject::write(S);
    SceneObjects.write(S);
    OtherObjects.write(S);
}

