/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plSpaceTree.h"

/* plSpaceBuilderNode */
plSpaceBuilderNode::plSpaceBuilderNode() : fDataIndex(-1), fIndex(-1) {
    fChildren[0] = NULL;
    fChildren[1] = NULL;
}

plSpaceBuilderNode::~plSpaceBuilderNode() {
    delete fChildren[0];
    delete fChildren[1];
}

size_t plSpaceBuilderNode::size() const {
    return 1 + ((fChildren[0] != NULL) ? fChildren[0]->size() : 0)
             + ((fChildren[1] != NULL) ? fChildren[1]->size() : 0);
}

size_t plSpaceBuilderNode::depth() const {
    int dep0 = (fChildren[0] != NULL) ? fChildren[0]->depth() : 0;
    int dep1 = (fChildren[1] != NULL) ? fChildren[1]->depth() : 0;

    return 1 + (dep0 | dep1);
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

void plSpaceTree::read(hsStream* S, plResManager* ) {
    fRoot = S->readShort();
    fNumLeaves = S->readInt();

    fTree.setSize(S->readInt());
    for (size_t i=0; i<fTree.getSize(); i++)
        fTree[i].read(S);
}

void plSpaceTree::write(hsStream* S, plResManager* ) {
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

void plSpaceTree::IGatherLeaves(plSpaceBuilderNode* node) {
    if (node->fChildren[0] == NULL) {
        plSpaceTreeNode& leaf = fTree[node->fDataIndex];
        short nodeIdx = node->fDataIndex;
        leaf.setBounds(node->fBounds);
        node->fIndex = nodeIdx;
        leaf.setLeafIndex(nodeIdx);

        return;
    }

    IGatherLeaves(node->fChildren[0]);
    IGatherLeaves(node->fChildren[1]);
}

void plSpaceTree::IMakeTree(plSpaceBuilderNode* node, int target, int curr) {
    if (node->fChildren[0] == NULL) {
        /* Don't include leaves */
        return;
    }

    if (curr == target) {
        short idx = fTree.getSize();
        fTree.incSize();

        fTree[idx].setBounds(node->fBounds);
        node->fIndex = idx;

        short left = node->fChildren[0]->fIndex;
        short right = node->fChildren[1]->fIndex;

        fTree[idx].setChildren(left, right);
        fTree[left].setParent(idx);
        fTree[right].setParent(idx);

        return;
    }

    IMakeTree(node->fChildren[0], target, curr+1);
    IMakeTree(node->fChildren[1], target, curr+1);
}

void plSpaceTree::buildTree(plSpaceBuilderNode* root, int numLeaves) {
    clear();
    fTree.setSize(numLeaves);
    fNumLeaves = numLeaves;

    IGatherLeaves(root);

    int depth = root->depth();
    while (depth > 0) {
        IMakeTree(root, --depth, 0);
    }

    fRoot = fTree.getSize() - 1;
    fTree[fRoot].setParent(-1);
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
