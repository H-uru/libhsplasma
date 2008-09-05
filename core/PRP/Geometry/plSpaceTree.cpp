#include "plSpaceTree.h"

/* plSpaceTreeNode */
plSpaceTreeNode::plSpaceTreeNode() : fFlags(0), fParent(-1) {
    fChildren[0] = -1;
    fChildren[1] = -1;
}

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

const hsBounds3Ext& plSpaceTreeNode::getBounds() { return fWorldBounds; }
unsigned short plSpaceTreeNode::getFlags() const { return fFlags; }
short plSpaceTreeNode::getParent() const { return fParent; }
short plSpaceTreeNode::getLChild() const { return fChildren[0]; }
short plSpaceTreeNode::getRChild() const { return fChildren[1]; }
short plSpaceTreeNode::getLeafIndex() const { return fLeafIndex; }

void plSpaceTreeNode::setBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }
void plSpaceTreeNode::setFlags(unsigned short flags) { fFlags = flags; }
void plSpaceTreeNode::setParent(short parent) { fParent = parent; }

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

void plSpaceTree::clear() {
    fTree.clear();
    fRoot = -1;
    fNumLeaves = 0;
}

const plSpaceTreeNode& plSpaceTree::getNode(short idx) const { return fTree[idx]; }
const plSpaceTreeNode& plSpaceTree::getRoot() const { return fTree[fRoot]; }

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
