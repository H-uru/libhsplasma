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

#ifndef _PLVAULTSTORE_H
#define _PLVAULTSTORE_H

#include "plVaultNode.h"
#include "plVaultNodeRef.h"
#include <map>
#include <list>

class PLASMA_DLL plVaultStore
{
protected:
    std::map<unsigned int, plVaultNode> fNodes;
    std::list<plVaultNodeRef> fNodeRefs;
    unsigned int fFirstNodeID, fLastNodeID;

public:
    plVaultStore(unsigned int firstNode = 20001)
        : fFirstNodeID(firstNode), fLastNodeID(firstNode - 1) { }

    void ImportFile(const ST::string& filename);
    void Import(hsStream* S);
    void ExportFile(const ST::string& filename, bool encrypt = true);
    void Export(hsStream* S);

    plVaultNode getNode(unsigned int idx) const;
    std::vector<plVaultNode> getChildren(unsigned int parent) const;
    std::vector<plVaultNode> findParents(unsigned int child) const;
    unsigned int getFirstNodeID() const { return fFirstNodeID; }
    unsigned int getLastNodeID() const { return fLastNodeID; }

    plVaultNode& addNode(const plVaultNode& node);
    void delNode(unsigned int idx) { fNodes.erase(idx); }
    void addRef(unsigned int parent, unsigned int child, unsigned int saver=0);
    void delRef(unsigned int parent, unsigned int child);
};

#endif
