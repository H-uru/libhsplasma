#include "plKeyCollector.h"

plKeyCollector::~plKeyCollector() {
    std::vector<PageID> pages = getPages();
    for (unsigned int i=0; i<pages.size(); i++) {
        std::vector<short> types = getTypes(pages[i]);
        for (unsigned int j=0; j<keys[pages[i]].size(); j++)
            keys[pages[i]][j]->UnRef();
    }
}

plKey* plKeyCollector::findKey(plKey* match) {
    plKey* key = NULL;
    for (unsigned int i=0; i < keys[match->getPageID()].size(); i++)
        if (*(keys[match->getPageID()][i]) == *match)
            key = keys[match->getPageID()][i];
    return key;
}

void plKeyCollector::add(plKey* key) {
    keys[key->getPageID()].push_back(key);
    key->Ref();
}

void plKeyCollector::reserveKeySpace(PageID& pid, int num) {
    keys[pid].reserve(num);
}

unsigned int plKeyCollector::countTypes(PageID& pid) {
    return getTypes(pid).size();
}

unsigned int plKeyCollector::countKeys(PageID& pid) {
    return keys[pid].size();
}

std::vector<plKey*>& plKeyCollector::getKeys(PageID& pid, short type) {
    std::vector<plKey*>* kList = new std::vector<plKey*>;
    kList->reserve(keys[pid].size());
    for (unsigned int i=0; i<keys[pid].size(); i++) {
        if (keys[pid][i]->getType() == type)
            kList->push_back(keys[pid][i]);
    }
    return *kList;
}

std::vector<short>& plKeyCollector::getTypes(PageID& pid) {
    std::vector<short>* types = new std::vector<short>;
    bool gotIt;
    short curType;
    std::vector<short>::iterator iter;
    for (unsigned int i=0; i<keys[pid].size(); i++) {
        gotIt = false;
        iter = types->begin();
        curType = keys[pid][i]->getType();
        while (iter != types->end() && *iter <= curType) {
            if (*iter == curType) gotIt = true;
            iter++;
        }
        if (!gotIt) types->insert(iter, curType);
    }

    return *types;
}

std::vector<PageID>& plKeyCollector::getPages() {
    std::vector<PageID>* pages = new std::vector<PageID>;
    std::map<PageID, std::vector<plKey*>, PageComparator>::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages->push_back(i->first);
    return *pages;
}

