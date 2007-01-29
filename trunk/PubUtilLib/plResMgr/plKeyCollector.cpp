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
    for (unsigned int i=0; i < keys[match->pageID].size(); i++)
        if (*(keys[match->pageID][i]) == *match)
            key = keys[match->pageID][i];
    return key;
}

void plKeyCollector::add(plKey* key) {
    keys[key->pageID].push_back(key);
    key->Ref();
}

unsigned int plKeyCollector::countTypes(PageID& pid) {
    unsigned int nTypes = 0;
    short lastType = -1;
    for (unsigned int i=0; i<keys[pid].size(); i++) {
        if (keys[pid][i]->objType != lastType) {
            nTypes++;
            lastType = keys[pid][i]->objType;
        }
    }
    return nTypes;
}

unsigned int plKeyCollector::countKeys(PageID& pid) {
    return keys[pid].size();
}

std::vector<plKey*>& plKeyCollector::getKeys(PageID& pid, short type) {
    std::vector<plKey*>* kList = new std::vector<plKey*>;
    for (unsigned int i=0; i<keys[pid].size(); i++) {
        if (keys[pid][i]->objType == type)
            kList->push_back(keys[pid][i]);
    }
    return *kList;
}

std::vector<short> plKeyCollector::getTypes(PageID& pid) {
    std::vector<short>* types = new std::vector<short>;
    short lastType = -1;
    for (unsigned int i=0; i<keys[pid].size(); i++) {
        if (keys[pid][i]->objType != lastType) {
            lastType = keys[pid][i]->objType;
            types->push_back(lastType);
        }
    }
    return *types;
}

std::vector<PageID> plKeyCollector::getPages() {
    std::vector<PageID>* pages = new std::vector<PageID>;
    std::map<PageID, std::vector<plKey*>, PageComparator>::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages->push_back(i->first);
    return *pages;
}
