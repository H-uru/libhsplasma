#ifndef _PLVAULTSTORE_H
#define _PLVAULTSTORE_H

#include "plVaultNode.h"
#include "plVaultNodeRef.h"
#include <map>
#include <list>

DllClass plVaultStore {
protected:
    std::map<unsigned int, plVaultNode> fNodes;
    std::list<plVaultNodeRef> fNodeRefs;
    unsigned int fNextNodeID;

public:
    plVaultStore(unsigned int firstNode = 20001);

    void ImportFile(const char* filename);
    void ExportFile(const char* filename, bool encrypt = true);

    plVaultNode getNode(unsigned int idx) const;
    std::vector<plVaultNode> getChildren(unsigned int parent) const;
    std::vector<plVaultNode> findParents(unsigned int child) const;

    void addNode(const plVaultNode& node);
    void delNode(unsigned int idx);
    void addRef(unsigned int parent, unsigned int child, unsigned int saver=0);
    void delRef(unsigned int parent, unsigned int child);
};

#endif
