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

#ifndef _PLSPACETREE_H
#define _PLSPACETREE_H

#include "PRP/plCreatable.h"
#include "Util/hsTArray.hpp"
#include "Math/hsGeometry3.h"
#include "PRP/Region/hsBounds.h"
#include "Util/hsBitVector.h"

DllStruct plSpaceBuilderNode {
    hsBounds3Ext fBounds;
    plSpaceBuilderNode* fChildren[2];

    plSpaceBuilderNode();
    ~plSpaceBuilderNode();
    size_t size() const;
};


DllClass plSpaceTreeNode {
public:
    enum {
        kNone = 0,
        kIsLeaf = 0x1,
        kDirty = 0x2,
        kDisabled = 0x4,
        kEmpty = 0x8,
        kEnabledTemp = 0x10
    };

protected:
    hsBounds3Ext fWorldBounds;
    unsigned short fFlags;
    short fParent;

    union {
        short fChildren[2];
        short fLeafIndex;
    };

public:
    plSpaceTreeNode();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    const hsBounds3Ext& getBounds() const { return fWorldBounds; }
    unsigned short getFlags() const { return fFlags; }
    short getParent() const { return fParent; }
    short getLChild() const { return fChildren[0]; }
    short getRChild() const { return fChildren[1]; }
    short getLeafIndex() const { return fLeafIndex; }

    void setBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }
    void setFlags(unsigned short flags) { fFlags = flags; }
    void setParent(short parent) { fParent = parent; }
    void setChildren(short left, short right);
    void setLeafIndex(short idx);
};

DllClass plSpaceTree : public plCreatable {
    CREATABLE(plSpaceTree, kSpaceTree, plCreatable)

protected:
    hsTArray<plSpaceTreeNode> fTree;
    short fRoot, fNumLeaves;

public:
    plSpaceTree();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    short IBuildTree(plSpaceBuilderNode* node, short idx);

public:
    void clear();
    void buildTree(plSpaceBuilderNode* root);

    const plSpaceTreeNode& getNode(short idx) const { return fTree[idx]; }
    const plSpaceTreeNode& getRoot() const { return fTree[fRoot]; }
    short addLeaf(const hsBounds3Ext& bounds);
    short addParent(const hsBounds3Ext& bounds, short left, short right);
};

#endif
