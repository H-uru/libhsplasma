#include "plKeyCollector.h"
#include "DynLib/pdUnifiedTypeMap.h"
#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"

plKeyCollector::plKeyCollector() { }
plKeyCollector::~plKeyCollector() { }

plKey plKeyCollector::findKey(plKey match) {
    plKey key;
    std::vector<plKey> kList = getKeys(match->getPageID(), match->getType());
    for (unsigned int i=0; i < kList.size(); i++)
        if (*kList[i] == *match)
            key = kList[i];
    return key;
}

void plKeyCollector::add(plKey key) {
    keys[key->getPageID()][key->getType()].push_back(key);
    if (key->getID() == 0)
        key->setID(keys[key->getPageID()][key->getType()].size());
}

void plKeyCollector::reserveKeySpace(const PageID& pid, short type, int num) {
    keys[pid][type].reserve(num);
}

void plKeyCollector::sortKeys(const PageID& pid) {
    std::vector<short> types = getTypes(pid);
    std::vector<plKey> sortKeys;
    for (unsigned int i=0; i<types.size(); i++) {
        sortKeys.clear();
        unsigned int id = 1;
        unsigned int nKeys = keys[pid][types[i]].size();
        for (unsigned int j=0; j<nKeys; j++) {
            for (unsigned int k=0; k<nKeys; k++) {
                if (keys[pid][types[i]][k]->getID() == id) {
                    sortKeys.push_back(keys[pid][types[i]][k]);
                    id++;
                }
            }
        }
        keys[pid][types[i]] = sortKeys;
    }
}

unsigned int plKeyCollector::countTypes(const PageID& pid) {
    return getTypes(pid).size();
}

unsigned int plKeyCollector::countKeys(const PageID& pid) {
    unsigned int kCount = 0;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++)
        kCount += keys[pid][i].size();
    return kCount;
}

const std::vector<plKey>& plKeyCollector::getKeys(const PageID& pid, short type) {
    return keys[pid][type];
}

std::vector<short> plKeyCollector::getTypes(const PageID& pid) {
    std::vector<short> types;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++) {
        if (keys[pid][i].size() > 0)
            types.push_back(i);
    }
    return types;
}

std::vector<PageID> plKeyCollector::getPages() {
    std::vector<PageID> pages;
    keymap_t::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages.push_back(i->first);
    return pages;
}

