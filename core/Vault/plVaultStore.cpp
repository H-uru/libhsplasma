#include "plVaultStore.h"
#include "../Stream/plEncryptedStream.h"
#include "../Util/hsBitVector.h"

plVaultStore::plVaultStore(unsigned int firstNode)
            : fNextNodeID(firstNode) { }

void plVaultStore::ImportFile(const char* filename) {
    hsStream* S;
    if (plEncryptedStream::IsFileEncrypted(filename)) {
        S = new plEncryptedStream();
        ((plEncryptedStream*)S)->open(filename, fmRead, plEncryptedStream::kEncAuto);
    } else {
        S = new hsFileStream();
        ((hsFileStream*)S)->open(filename, fmRead);
    }

    if (S->readByte() != 1) {
        delete S;
        throw hsBadParamException(__FILE__, __LINE__, "Incorrect Vault File Version");
    }

    hsBitVector fileFields;
    fileFields.read(S);
    if (fileFields[0]) {
        if (S->readByte() != 3) {
            delete S;
            throw hsBadParamException(__FILE__, __LINE__, "Incorrect Vault Version");
        }

        hsBitVector vaultFields;
        vaultFields.read(S);
        if (vaultFields[0]) {
            fNextNodeID = S->readInt() + 1;
        }
        if (vaultFields[2]) {
            size_t numNodes = S->readInt();
            for (size_t i=0; i<numNodes; i++) {
                plVaultNode node;
                node.read(S);
                fNodes[node.getNodeID()] = node;
            }
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

    delete S;
}

void plVaultStore::ExportFile(const char* filename, bool encrypt) {
    hsStream* S;
    if (encrypt) {
        S = new plEncryptedStream();
        ((plEncryptedStream*)S)->open(filename, fmCreate, plEncryptedStream::kEncXtea);
    } else {
        S = new hsFileStream();
        ((hsFileStream*)S)->open(filename, fmCreate);
    }

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

    S->writeInt(fNextNodeID - 1);

    S->writeInt(fNodes.size());
    for (std::map<unsigned int, plVaultNode>::iterator it=fNodes.begin(); it!=fNodes.end(); it++)
        it->second.write(S);

    S->writeInt(fNodeRefs.size());
    for (std::list<plVaultNodeRef>::iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++)
        (*it).write(S);

    delete S;
}

plVaultNode plVaultStore::getNode(unsigned int idx) const {
    std::map<unsigned int, plVaultNode>::const_iterator it = fNodes.find(idx);
    if (it != fNodes.end())
        return it->second;
    else
        return plVaultNode();
}

std::vector<plVaultNode> plVaultStore::getChildren(unsigned int parent) const {
    std::list<unsigned int> childIDs;
    for (std::list<plVaultNodeRef>::const_iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++) {
        if ((*it).getParent() == parent)
            childIDs.push_back((*it).getChild());
    }
    std::vector<plVaultNode> nodes;
    nodes.resize(childIDs.size());
    size_t i=0;
    for (std::list<unsigned int>::iterator it=childIDs.begin(); it!=childIDs.end(); it++)
        nodes[i++] = getNode(*it);
    return nodes;
}

std::vector<plVaultNode> plVaultStore::findParents(unsigned int child) const {
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

void plVaultStore::addNode(const plVaultNode& node) {
    if (node.getNodeID() == 0) {
        fNodes[fNextNodeID] = node;
        fNodes[fNextNodeID].setNodeID(fNextNodeID);
        fNextNodeID++;
    } else {
        fNodes[node.getNodeID()] = node;
    }
}

void plVaultStore::delNode(unsigned int idx) {
    fNodes.erase(idx);
}

void plVaultStore::addRef(unsigned int parent, unsigned int child, unsigned int saver) {
    plVaultNodeRef ref;
    ref.setParent(parent);
    ref.setChild(child);
    ref.setSaver(saver);
    fNodeRefs.push_back(ref);
}

void plVaultStore::delRef(unsigned int parent, unsigned int child) {
    for (std::list<plVaultNodeRef>::iterator it=fNodeRefs.begin(); it!=fNodeRefs.end(); it++) {
        if ((*it).getParent() == parent && (*it).getChild() == child)
            it = fNodeRefs.erase(it);
    }
}
