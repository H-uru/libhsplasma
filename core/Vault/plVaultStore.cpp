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

#include "plVaultStore.h"
#include "Stream/plEncryptedStream.h"
#include "Util/hsBitVector.h"

void plVaultStore::ImportFile(const ST::string& filename)
{
    if (plEncryptedStream::IsFileEncrypted(filename)) {
        plEncryptedStream S;
        S.open(filename, fmRead, plEncryptedStream::kEncAuto);
        Import(&S);
    } else {
        hsFileStream S;
        S.open(filename, fmRead);
        Import(&S);
    }
}

void plVaultStore::Import(hsStream* S)
{
    if (S->readByte() != 1)
        throw hsBadParamException(__FILE__, __LINE__, "Incorrect Vault File Version");

    hsBitVector fileFields;
    fileFields.read(S);
    if (fileFields[0]) {
        if (S->readByte() != 3)
            throw hsBadParamException(__FILE__, __LINE__, "Incorrect Vault Version");

        hsBitVector vaultFields;
        vaultFields.read(S);
        if (vaultFields[0]) {
            fLastNodeID = S->readInt();
        }
        if (vaultFields[2]) {
            size_t numNodes = S->readInt();
            for (size_t i=0; i<numNodes; i++) {
                plVaultNode node;
                node.read(S);
                fNodes[node.getNodeID()] = node;
            }
            if (numNodes > 0)
                fFirstNodeID = fNodes.begin()->first;
        }
        if (vaultFields[1]) {
            size_t numRefs = S->readInt();
            for (size_t i=0; i<numRefs; i++) {
                plVaultNodeRef ref;
                ref.read(S);
                fNodeRefs.push_back(ref);
            }
        }
    }
}

void plVaultStore::ExportFile(const ST::string& filename, bool encrypt)
{
    if (encrypt) {
        plEncryptedStream S;
        S.open(filename, fmCreate, plEncryptedStream::kEncXtea);
        Export(&S);
    } else {
        hsFileStream S;
        S.open(filename, fmCreate);
        Export(&S);
    }
}

void plVaultStore::Export(hsStream* S)
{
    // Vault File
    S->writeByte(1);

    hsBitVector fileFields;
    fileFields[0] = true;
    fileFields.write(S);

    // Vault
    S->writeByte(3);

    hsBitVector vaultFields;
    vaultFields[0] = true;
    vaultFields[1] = true;
    vaultFields[2] = true;
    vaultFields.write(S);

    S->writeInt(fLastNodeID);

    S->writeInt(fNodes.size());
    for (std::map<unsigned int, plVaultNode>::iterator it=fNodes.begin(); it!=fNodes.end(); it++)
        it->second.write(S);

    S->writeInt(fNodeRefs.size());
    for (std::list<plVaultNodeRef>::iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++)
        (*it).write(S);
}

plVaultNode plVaultStore::getNode(unsigned int idx) const
{
    std::map<unsigned int, plVaultNode>::const_iterator it = fNodes.find(idx);
    if (it != fNodes.end())
        return it->second;
    else
        return plVaultNode();
}

std::vector<plVaultNode> plVaultStore::getChildren(unsigned int parent) const
{
    std::list<unsigned int> childIDs;
    for (std::list<plVaultNodeRef>::const_iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++) {
        if ((*it).getParent() == parent)
            childIDs.push_back((*it).getChild());
    }
    std::vector<plVaultNode> nodes(childIDs.size());
    size_t i=0;
    for (auto it=childIDs.begin(); it!=childIDs.end(); it++)
        nodes[i++] = getNode(*it);
    return nodes;
}

std::vector<plVaultNode> plVaultStore::findParents(unsigned int child) const
{
    std::list<unsigned int> parentIDs;
    for (std::list<plVaultNodeRef>::const_iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++) {
        if ((*it).getChild() == child)
            parentIDs.push_back((*it).getParent());
    }
    std::vector<plVaultNode> nodes;
    nodes.resize(parentIDs.size());
    size_t i=0;
    for (std::list<unsigned int>::iterator it=parentIDs.begin(); it!=parentIDs.end(); it++)
        nodes[i++] = getNode(*it);
    return nodes;
}

plVaultNode& plVaultStore::addNode(const plVaultNode& node)
{
    if (node.getNodeID() == 0) {
        fLastNodeID++;
        fNodes[fLastNodeID] = node;
        fNodes[fLastNodeID].setNodeID(fLastNodeID);
        return fNodes[fLastNodeID];
    } else {
        if (node.getNodeID() < fFirstNodeID)
            fFirstNodeID = node.getNodeID();
        if (node.getNodeID() > fLastNodeID)
            fLastNodeID = node.getNodeID();
        fNodes[node.getNodeID()] = node;
        return fNodes[node.getNodeID()];
    }
}

void plVaultStore::addRef(unsigned int parent, unsigned int child, unsigned int saver)
{
    plVaultNodeRef ref;
    ref.setParent(parent);
    ref.setChild(child);
    ref.setSaver(saver);
    fNodeRefs.push_back(ref);
}

void plVaultStore::delRef(unsigned int parent, unsigned int child)
{
    for (std::list<plVaultNodeRef>::iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++) {
        if ((*it).getParent() == parent && (*it).getChild() == child) {
            it = fNodeRefs.erase(it);
            return;
        }
    }
}
