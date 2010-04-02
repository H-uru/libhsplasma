#include "plCoordinateInterface.h"

plCoordinateInterface::plCoordinateInterface() {
    fLocalToParent.Reset();
    fParentToLocal.Reset();
    fLocalToWorld.Reset();
    fWorldToLocal.Reset();

    fProps.setName(kDisable, "kDisable");
    fProps.setName(kCanEverDelayTransform, "kCanEverDelayTransform");
    fProps.setName(kDelayedTransformEval, "kDelayedTransformEval");
}

void plCoordinateInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    fLocalToParent.read(S);
    fParentToLocal.read(S);
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);

    fChildren.setSize(S->readInt());
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i] = mgr->readKey(S);
}

void plCoordinateInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    fLocalToParent.write(S);
    fParentToLocal.write(S);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);

    S->writeInt(fChildren.getSize());
    for (size_t i=0; i<fChildren.getSize(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plCoordinateInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("LocalToParent");
    fLocalToParent.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("ParentToLocal");
    fParentToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToWorld");
    fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
    fWorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i]->prcWrite(prc);
    prc->closeTag();
}

void plCoordinateInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LocalToParent") {
        if (tag->hasChildren())
            fLocalToParent.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "ParentToLocal") {
        if (tag->hasChildren())
            fParentToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Children") {
        fChildren.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fChildren.getSize(); i++) {
            fChildren[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
