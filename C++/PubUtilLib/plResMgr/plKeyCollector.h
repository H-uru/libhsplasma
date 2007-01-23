#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../DynLib/PageID.h"
#include <map>
#include <vector>

class plKeyCollector {
private:
    std::map<PageID, std::map<short, std::vector<plKey> >, PageComparator> keys;

public:
    plKey* findKey(plKey* match);
    void add(plKey* key);
};

#endif

