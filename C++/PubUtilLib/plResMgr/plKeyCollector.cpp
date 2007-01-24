#include "plKeyCollector.h"

plKeyCollector::~plKeyCollector() {
    std::vector<PageID> pages = getPages();
    for (unsigned int i=0; i<pages.size(); i++) {
        std::vector<short> types = getTypes(pages[i]);
        for (unsigned int j=0; j<types.size(); j++)
            for (unsigned int k=0; k<keys[pages[i]][types[j]].size(); k++)
                keys[pages[i]][types[j]][k]->UnRef();
    }
}

plKey* plKeyCollector::findKey(plKey* match) {
    std::vector<plKey*> kv = keys[match->pageID][match->objType];
    plKey* key = NULL;
    for (unsigned int i=0; i < kv.size(); i++)
        if (*(kv[i]) == *match) key = kv[i];
    return key;
}

void plKeyCollector::add(plKey* key) {
    keys[key->pageID][key->objType].push_back(key);
    key->Ref();
}

unsigned int plKeyCollector::countTypes(PageID& pid) {
    return keys[pid].size();
}

unsigned int plKeyCollector::countKeys(PageID& pid) {
    std::vector<short> types = getTypes(pid);
    unsigned int ct = 0;
    for (unsigned int i=0; i<types.size(); i++)
        ct += keys[pid][types[i]].size();
    return ct;
}

std::vector<plKey*>& plKeyCollector::getKeys(PageID& pid, short type) {
    return keys[pid][type];
}

std::vector<short> plKeyCollector::getTypes(PageID& pid) {
    std::vector<short>* types = new std::vector<short>;
    std::map<short, std::vector<plKey*> >::iterator i;
    for (i = keys[pid].begin(); i != keys[pid].end(); i++)
        types->push_back(i->first);
    return *types;
}

std::vector<PageID> plKeyCollector::getPages() {
    std::vector<PageID>* pages = new std::vector<PageID>;
    std::map<PageID, std::map<short, std::vector<plKey*> >, PageComparator>::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages->push_back(i->first);
    return *pages;
}

