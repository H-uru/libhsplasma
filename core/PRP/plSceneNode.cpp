#include "plSceneNode.h"

plSceneNode::plSceneNode() { }
plSceneNode::~plSceneNode() { }

IMPLEMENT_CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

void plSceneNode::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fSceneObjects.setSize(S->readInt());
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        fSceneObjects[i] = mgr->readKey(S);
    fOtherObjects.setSize(S->readInt());
    for (size_t i=0; i<fOtherObjects.getSize(); i++)
        fOtherObjects[i] = mgr->readKey(S);
}

void plSceneNode::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSceneObjects.getSize());
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        mgr->writeKey(S, fSceneObjects[i]);
    S->writeInt(fOtherObjects.getSize());
    for (size_t i=0; i<fOtherObjects.getSize(); i++)
        mgr->writeKey(S, fOtherObjects[i]);
}

void plSceneNode::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("SceneObjects");
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        fSceneObjects[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PoolObjects");
    for (size_t i=0; i<fOtherObjects.getSize(); i++)
        fOtherObjects[i]->prcWrite(prc);
    prc->closeTag();
}

void plSceneNode::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SceneObjects") {
        fSceneObjects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSceneObjects.getSize(); i++) {
            fSceneObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PoolObjects") {
        fOtherObjects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fOtherObjects.getSize(); i++) {
            fOtherObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

size_t plSceneNode::getNumSceneObjects() const { return fSceneObjects.getSize(); }
plKey plSceneNode::getSceneObject(size_t idx) const { return fSceneObjects[idx]; }
void plSceneNode::addSceneObject(plKey obj) { fSceneObjects.append(obj); }
void plSceneNode::delSceneObject(size_t idx) { fSceneObjects.remove(idx); }
void plSceneNode::clearSceneObjects() { fSceneObjects.clear(); }

size_t plSceneNode::getNumPoolObjects() const { return fOtherObjects.getSize(); }
plKey plSceneNode::getPoolObject(size_t idx) const { return fOtherObjects[idx]; }
void plSceneNode::addPoolObject(plKey obj) { fOtherObjects.append(obj); }
void plSceneNode::delPoolObject(size_t idx) { fOtherObjects.remove(idx); }
void plSceneNode::clearPoolObjects() { fOtherObjects.clear(); }

hsTArray<plKey>& plSceneNode::getSceneObjects() { return fSceneObjects; }
hsTArray<plKey>& plSceneNode::getPoolObjects() { return fOtherObjects; }
