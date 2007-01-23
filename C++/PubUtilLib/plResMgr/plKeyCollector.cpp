#include "plKeyCollector.h"

plKey* plKeyCollector::findKey(plKey* match) {
    std::vector<plKey>* kv = &(keys[match->pageID][match->objType]);
    plKey* key = NULL;
    for (unsigned int i=0; i < kv->size(); i++)
        if (kv->at(i) == *match) *key = &(kv->at(i));
    return key;
}

void plKeyCollector::add(plKey* key) {
    keys[key->pageID][key->objType].push_back(*key);
    key->Ref();
}

