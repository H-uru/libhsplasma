#include "plSceneNode.h"

void plSceneNode::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fSceneObjects.setSize(S->readInt());
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        fSceneObjects[i] = mgr->readKey(S);
    fPoolObjects.setSize(S->readInt());
    for (size_t i=0; i<fPoolObjects.getSize(); i++)
        fPoolObjects[i] = mgr->readKey(S);
}

void plSceneNode::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSceneObjects.getSize());
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        mgr->writeKey(S, fSceneObjects[i]);
    S->writeInt(fPoolObjects.getSize());
    for (size_t i=0; i<fPoolObjects.getSize(); i++)
        mgr->writeKey(S, fPoolObjects[i]);
}

void plSceneNode::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("SceneObjects");
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        fSceneObjects[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PoolObjects");
    for (size_t i=0; i<fPoolObjects.getSize(); i++)
        fPoolObjects[i]->prcWrite(prc);
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
        fPoolObjects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPoolObjects.getSize(); i++) {
            fPoolObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
