#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../DynLib/PageID.h"
#include <map>
#include <vector>

typedef std::map<PageID, std::map<short, std::vector<plKey*> >, PageComparator> keymap_t;

DllClass plKeyCollector {
private:
    keymap_t keys;

public:
    plKeyCollector();
    ~plKeyCollector();

    plKey* findKey(plKey* match);
    void add(plKey* key);
    void reserveKeySpace(PageID& pid, short type, int num);
    void sortKeys(PageID& pid);

    unsigned int countTypes(PageID& pid);
    unsigned int countKeys(PageID& pid);
    const std::vector<plKey*>& getKeys(PageID& pid, short type);
    std::vector<short> getTypes(PageID& pid);
    std::vector<PageID> getPages();
};

#endif
