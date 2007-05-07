#include "plKeyCollector.h"
#include "../../DynLib/pdUnifiedTypeMap.h"

plKeyCollector::plKeyCollector() { }

plKeyCollector::~plKeyCollector() {
    std::vector<PageID> pages = getPages();
    for (unsigned int i=0; i<pages.size(); i++) {
        for (unsigned int j=0; j<TYPESPACE_MAX; j++) {
            for (unsigned int k=0; k<keys[pages[i]][j].size(); k++)
                keys[pages[i]][j][k]->UnRef();
        }
    }
}

plKey* plKeyCollector::findKey(plKey* match) {
    plKey* key = NULL;
    for (unsigned int i=0; i < keys[match->getPageID()][match->getType()].size(); i++)
        if (*(keys[match->getPageID()][match->getType()][i]) == *match)
            key = keys[match->getPageID()][match->getType()][i];
    return key;
}

void plKeyCollector::add(plKey* key) {
    keys[key->getPageID()][key->getType()].push_back(key);
    key->Ref();
}

void plKeyCollector::reserveKeySpace(PageID& pid, short type, int num) {
    keys[pid][type].reserve(num);
}

unsigned int plKeyCollector::countTypes(PageID& pid) {
    return getTypes(pid).size();
}

unsigned int plKeyCollector::countKeys(PageID& pid) {
    unsigned int kCount = 0;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++)
        kCount += keys[pid][i].size();
    return kCount;
}

std::vector<plKey*>& plKeyCollector::getKeys(PageID& pid, short type) {
    return keys[pid][type];
}

std::vector<short>& plKeyCollector::getTypes(PageID& pid) {
    std::vector<short>* types = new std::vector<short>;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++) {
        if (keys[pid][i].size() > 0)
            types->push_back(i);
    }
    return *types;
}

std::vector<PageID>& plKeyCollector::getPages() {
    std::vector<PageID>* pages = new std::vector<PageID>;
    keymap_t::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages->push_back(i->first);
    return *pages;
}

