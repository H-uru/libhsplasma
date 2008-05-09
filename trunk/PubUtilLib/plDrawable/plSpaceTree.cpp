#include "plSpaceTree.h"

/* plSpaceTreeNode */
plSpaceTreeNode::plSpaceTreeNode() { }
plSpaceTreeNode::~plSpaceTreeNode() { }

void plSpaceTreeNode::read(hsStream* S) {
    fWorldBounds.read(S);
    fFlags = S->readShort();
    fParent = S->readShort();
    fChildren[0] = S->readShort();
    fChildren[1] = S->readShort();
}

void plSpaceTreeNode::write(hsStream* S) {
    fWorldBounds.write(S);
    S->writeShort(fFlags);
    S->writeShort(fParent);
    S->writeShort(fChildren[0]);
    S->writeShort(fChildren[1]);
}

void plSpaceTreeNode::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plSpaceTreeNode");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Parent", fParent);
    if (fFlags & kIsLeaf) {
        prc->writeParam("LeafIndex", fLeafIndex);
    } else {
        prc->writeParam("LeftChild", fChildren[0]);
        prc->writeParam("RightChild", fChildren[1]);
    }
    prc->endTag();
    fWorldBounds.prcWrite(prc);
    prc->closeTag();
}

void plSpaceTreeNode::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plSpaceTreeNode")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFlags = tag->getParam("Flags", "0").toUint();
    fParent = tag->getParam("Parent", "-1").toInt();
    if (tag->hasParam("LeafIndex")) {
        fLeafIndex = tag->getParam("LeafIndex", "0").toInt();;
    } else {
        fChildren[0] = tag->getParam("LeftChild", "0").toInt();
        fChildren[1] = tag->getParam("RightChild", "0").toInt();
    }

    if (tag->hasChildren())
        fWorldBounds.prcParse(tag->getFirstChild());
}


/* plSpaceTree */
plSpaceTree::plSpaceTree() { }
plSpaceTree::~plSpaceTree() { }

IMPLEMENT_CREATABLE(plSpaceTree, kSpaceTree, plCreatable)

void plSpaceTree::read(hsStream* S, plResManager* mgr) {
    fRoot = S->readShort();
    fNumLeaves = S->readInt();

    fTree.setSize(S->readInt());
    for (size_t i=0; i<fTree.getSize(); i++)
        fTree[i].read(S);
}

void plSpaceTree::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fRoot);
    S->writeInt(fNumLeaves);

    S->writeInt(fTree.getSize());
    for (size_t i=0; i<fTree.getSize(); i++)
        fTree[i].write(S);
}

void plSpaceTree::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("SpaceTreeParams");
    prc->writeParam("Root", fRoot);
    prc->writeParam("NumLeaves", fNumLeaves);
    prc->endTag(true);

    prc->writeSimpleTag("Tree");
    for (size_t i=0; i<fTree.getSize(); i++)
        fTree[i].prcWrite(prc);
    prc->closeTag();
}

void plSpaceTree::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SpaceTreeParams") {
        fRoot = tag->getParam("Root", "0").toInt();
        fNumLeaves = tag->getParam("NumLeaves", "0").toInt();
    } else if (tag->getName() == "Tree") {
        const pfPrcTag* child = tag->getFirstChild();
        fTree.setSize(tag->countChildren());
        for (size_t i=0; i<fTree.getSize(); i++) {
            fTree[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
