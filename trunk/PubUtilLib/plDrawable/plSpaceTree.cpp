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
    prc->writeParam("Flags", fFlags);
    prc->writeParam("Parent", fParent);
    prc->writeParam("LeftChild", fChildren[0]);
    prc->writeParam("RightChild", fChildren[1]);
    prc->endTag();
    fWorldBounds.prcWrite(prc);
    prc->closeTag();
    prc->closeTag();
}


/* plSpaceTree */
plSpaceTree::plSpaceTree() : fCache(NULL) /*, fCullFunc(NULL)*/ { }
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
    prc->startTag("Params");
    prc->writeParam("Root", fRoot);
    prc->writeParam("NumLeaves", fNumLeaves);
    prc->endTag(true);
    
    for (size_t i=0; i<fTree.getSize(); i++)
        fTree[i].prcWrite(prc);
}
