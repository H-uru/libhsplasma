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


/* plSpaceTree */
plSpaceTree::plSpaceTree(PlasmaVer pv) : fCache(NULL) /*, fCullFunc(NULL)*/ { }
plSpaceTree::~plSpaceTree() { }

short plSpaceTree::ClassIndex() {
    switch (ver) {
    case pvEoa:   return 0x0240;
    case pvLive:  return 0x025D;
    default:      return 0x0258;
    }
}

void plSpaceTree::read(hsStream* S) {
    fRoot = S->readShort();
    fNumLeaves = S->readInt();

    fTree.setSize(S->readInt());
    for (int i=0; i<fTree.getSize(); i++)
        fTree[i].read(S);
}

void plSpaceTree::write(hsStream* S) {
    S->writeShort(fRoot);
    S->writeInt(fNumLeaves);

    S->writeInt(fTree.getSize());
    for (int i=0; i<fTree.getSize(); i++)
        fTree[i].write(S);
}
