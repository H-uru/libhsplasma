#include "plSpaceTree.h"

/* plSpaceBuilderNode */
plSpaceBuilderNode::plSpaceBuilderNode() {
    fChildren[0] = NULL;
    fChildren[1] = NULL;
}

plSpaceBuilderNode::~plSpaceBuilderNode() {
    if (fChildren[0] != NULL)
        delete fChildren[0];
    if (fChildren[1] != NULL)
        delete fChildren[1];
}

size_t plSpaceBuilderNode::size() const {
    return 1 + ((fChildren[0] != NULL) ? fChildren[0]->size() : 0)
             + ((fChildren[1] != NULL) ? fChildren[1]->size() : 0);
}


/* plSpaceTreeNode */
plSpaceTreeNode::plSpaceTreeNode() : fFlags(0), fParent(-1) {
    fChildren[0] = 0;
    fChildren[1] = 0;
}

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

void plSpaceTreeNode::setChildren(short left, short right) {
    fFlags &= ~kIsLeaf;
    fChildren[0] = left;
    fChildren[1] = right;
}

void plSpaceTreeNode::setLeafIndex(short idx) {
    fFlags |= kIsLeaf;
    fLeafIndex = idx;
}


/* plSpaceTree */
plSpaceTree::plSpaceTree() : fRoot(-1), fNumLeaves(0) { }

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

void plSpaceTree::clear() {
    fTree.clear();
    fRoot = -1;
    fNumLeaves = 0;
}

short plSpaceTree::IBuildTree(plSpaceBuilderNode* node, short idx) {
    if (node->fChildren[0] != NULL) {
        short left = IBuildTree(node->fChildren[0], idx);
        idx = left + 1;
        short right = IBuildTree(node->fChildren[1], idx);
        idx = right + 1;
        fTree[idx].setChildren(left, right);
        fTree[left].setParent(idx);
        fTree[right].setParent(idx);
    } else {
        fTree[idx].setLeafIndex(idx);
        fNumLeaves++;
    }
    fTree[idx].setBounds(node->fBounds);
    return idx;
}

void plSpaceTree::buildTree(plSpaceBuilderNode* root) {
    clear();
    fTree.setSize(root->size());
    fRoot = IBuildTree(root, 0);
}

short plSpaceTree::addLeaf(const hsBounds3Ext& bounds) {
    plSpaceTreeNode node;
    node.setLeafIndex(fNumLeaves);
    node.setBounds(bounds);
    fTree.append(node);
    fNumLeaves++;
    return fTree.getSize() - 1;
}

short plSpaceTree::addParent(const hsBounds3Ext& bounds, short left, short right) {
    plSpaceTreeNode node;
    node.setChildren(left, right);
    node.setBounds(bounds);
    fTree.append(node);
    short id = fTree.getSize() - 1;
    fTree[left].setParent(id);
    fTree[right].setParent(id);
    fRoot = id;
    return id;
}
