#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "PRP/KeyedObject/plKey.h"
#include <map>
#include <vector>

typedef std::map<plLocation, std::map<short, std::vector<plKey> > > keymap_t;

DllClass plKeyCollector {
private:
    keymap_t keys;

public:
    plKeyCollector();
    ~plKeyCollector();

    plKey findKey(plKey match);
    void add(plKey key);
    void del(plKey key);
    void delAll(const plLocation& loc);
    void reserveKeySpace(const plLocation& loc, short type, int num);
    void sortKeys(const plLocation& loc);

    unsigned int countTypes(const plLocation& loc);
    unsigned int countKeys(const plLocation& loc);
    const std::vector<plKey>& getKeys(const plLocation& loc, short type);
    std::vector<short> getTypes(const plLocation& loc);
    std::vector<plLocation> getPages();

    void ChangeLocation(const plLocation& from, const plLocation& to);
    void MoveKey(plKey key, const plLocation& to);
};

#endif
