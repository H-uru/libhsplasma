#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "NucleusLib/pnKeyedObject/plKey.h"
#include "DynLib/PageID.h"
#include <map>
#include <vector>

typedef std::map<PageID, std::map<short, std::vector<plKey> > > keymap_t;

DllClass plKeyCollector {
private:
    keymap_t keys;

public:
    plKeyCollector();
    ~plKeyCollector();

    plKey findKey(plKey match);
    void add(plKey key);
    void reserveKeySpace(const PageID& pid, short type, int num);
    void sortKeys(const PageID& pid);

    unsigned int countTypes(const PageID& pid);
    unsigned int countKeys(const PageID& pid);
    const std::vector<plKey>& getKeys(const PageID& pid, short type);
    std::vector<short> getTypes(const PageID& pid);
    std::vector<PageID> getPages();
};

#endif
