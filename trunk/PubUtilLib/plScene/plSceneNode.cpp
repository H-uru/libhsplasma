#include "plSceneNode.h"

plSceneNode::plSceneNode() { }
plSceneNode::~plSceneNode() { }

IMPLEMENT_CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

void plSceneNode::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fSceneObjects.setSize(S->readInt());
	size_t i;
    for (i=0; i<fSceneObjects.getSize(); i++)
        fSceneObjects[i] = mgr->readKey(S);
    fOtherObjects.setSize(S->readInt());
    for (i=0; i<fOtherObjects.getSize(); i++)
        fOtherObjects[i] = mgr->readKey(S);
}

void plSceneNode::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSceneObjects.getSize());
	size_t i;
    for (i=0; i<fSceneObjects.getSize(); i++)
        mgr->writeKey(S, fSceneObjects[i]);
    S->writeInt(fOtherObjects.getSize());
    for (i=0; i<fOtherObjects.getSize(); i++)
        mgr->writeKey(S, fOtherObjects[i]);
}

void plSceneNode::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    size_t i;
    prc->writeSimpleTag("SceneObjects");
    for (i=0; i<fSceneObjects.getSize(); i++)
        fSceneObjects[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PoolObjects");
    for (i=0; i<fOtherObjects.getSize(); i++)
        fOtherObjects[i]->prcWrite(prc);
    prc->closeTag();
}
