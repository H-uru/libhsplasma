#include "plKeyCollector.h"
#include "pdUnifiedTypeMap.h"
#include "PRP/KeyedObject/hsKeyedObject.h"

plKeyCollector::plKeyCollector() { }
plKeyCollector::~plKeyCollector() { }

plKey plKeyCollector::findKey(plKey match) {
    plKey key;
    std::vector<plKey> kList = getKeys(match->getLocation(), match->getType());
    for (unsigned int i=0; i < kList.size(); i++)
        if (*kList[i] == *match)
            key = kList[i];
    return key;
}

void plKeyCollector::add(plKey key) {
    keys[key->getLocation()][key->getType()].push_back(key);
    if (key->getID() == 0)
        key->setID(keys[key->getLocation()][key->getType()].size());
}

void plKeyCollector::del(plKey key) {
    std::vector<plKey>::iterator it;
    std::vector<plKey>& keyList = keys[key->getLocation()][key->getType()];
    for (it = keyList.begin(); it != keyList.end(); it++) {
        if ((*it) == key)
            it = keyList.erase(it);
    }
}

void plKeyCollector::delAll(const plLocation& loc) {
    keys.erase(loc);
}

void plKeyCollector::reserveKeySpace(const plLocation& loc, short type, int num) {
    keys[loc][type].reserve(num);
}

void plKeyCollector::sortKeys(const plLocation& loc) {
    std::vector<short> types = getTypes(loc);
    std::vector<plKey> sortKeys;
    for (unsigned int i=0; i<types.size(); i++) {
        sortKeys.clear();
        unsigned int id = 1;
        unsigned int nKeys = keys[loc][types[i]].size();
        for (unsigned int j=0; j<nKeys; j++) {
            for (unsigned int k=0; k<nKeys; k++) {
                if (keys[loc][types[i]][k]->getID() == id) {
                    sortKeys.push_back(keys[loc][types[i]][k]);
                    id++;
                }
            }
        }
        keys[loc][types[i]] = sortKeys;
    }
}

unsigned int plKeyCollector::countTypes(const plLocation& loc) {
    return getTypes(loc).size();
}

unsigned int plKeyCollector::countKeys(const plLocation& loc) {
    unsigned int kCount = 0;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++)
        kCount += keys[loc][i].size();
    return kCount;
}

const std::vector<plKey>& plKeyCollector::getKeys(const plLocation& loc, short type) {
    return keys[loc][type];
}

std::vector<short> plKeyCollector::getTypes(const plLocation& loc) {
    std::vector<short> types;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++) {
        if (keys[loc][i].size() > 0)
            types.push_back(i);
    }
    return types;
}

std::vector<plLocation> plKeyCollector::getPages() {
    std::vector<plLocation> pages;
    keymap_t::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages.push_back(i->first);
    return pages;
}
