#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../DynLib/PageID.h"
#include <map>
#include <vector>

DllClass plKeyCollector {
private:
    std::map<PageID, std::vector<plKey*>, PageComparator> keys;

public:
    ~plKeyCollector();

    plKey* findKey(plKey* match);
    void add(plKey* key);

    unsigned int countTypes(PageID& pid);
    unsigned int countKeys(PageID& pid);
    std::vector<plKey*>& getKeys(PageID& pid, short type);
    std::vector<short>& getTypes(PageID& pid);
    std::vector<PageID>& getPages();
};

#endif
