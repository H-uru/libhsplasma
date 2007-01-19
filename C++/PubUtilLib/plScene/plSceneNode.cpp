#include "plSceneNode.h"

plSceneNode::plSceneNode(PlasmaVer pv) { }
plSceneNode::~plSceneNode() { }

void plSceneNode::read(hsStream *S) {
    hsKeyedObject::read(S);

    SceneObjects.setSize(S->readInt());
    for (int i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i].readRef(S);
    OtherObjects.setSize(S->readInt());
    for (int i=0; i<OtherObjects.getSize(); i++)
        OtherObjects[i].readRef(S);
}

void plSceneNode::write(hsStream *S) {
    hsKeyedObject::write(S);

    S->writeInt(SceneObjects.getSize());
    for (int i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i].writeRef(S);
    S->writeInt(OtherObjects.getSize());
    for (int i=0; i<OtherObjects.getSize(); i++)
        OtherObjects[i].writeRef(S);
}

