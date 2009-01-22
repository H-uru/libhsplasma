#include "plKeyCollector.h"
#include "pdUnifiedTypeMap.h"
#include "PRP/KeyedObject/hsKeyedObject.h"

plKeyCollector::plKeyCollector() { }

plKeyCollector::~plKeyCollector() {
    // This is now the "ultimate owner" of KeyedObjects, so we must delete
    // all the KOs that we own...
    for (keymap_t::iterator it = keys.begin(); it != keys.end(); it++) {
        for (std::map<short, std::vector<plKey> >::iterator i2 = it->second.begin(); i2 != it->second.end(); i2++) {
            for (std::vector<plKey>::iterator i3 = i2->second.begin(); i3 != i2->second.end(); i3++) {
                if ((*i3).Exists() && (*i3).isLoaded())
                    delete (*i3)->getObj();
            }
        }
    }
}

plKey plKeyCollector::findKey(plKey match) {
    plKey key;
    std::vector<plKey> kList = getKeys(match->getLocation(), match->getType());
    for (unsigned int i=0; i < kList.size(); i++) {
        if (*kList[i] == *match) {
            key = kList[i];
            break;
        }
    }
    return key;
}

void plKeyCollector::add(plKey key) {
    keys[key->getLocation()][key->getType()].push_back(key);
    if (key->getID() == 0)
        key->setID(keys[key->getLocation()][key->getType()].size());
}

void plKeyCollector::del(plKey key) {
    std::vector<plKey>& keyList = keys[key->getLocation()][key->getType()];
    std::vector<plKey>::iterator it = keyList.begin();
    size_t sub = 0;
    while (it != keyList.end()) {
        if ((*it) == key) {
            it = keyList.erase(it);
            sub++;
        } else {
            (*it)->setID((*it)->getID() - sub);
            it++;
        }
    }
    if (key.Exists() && key.isLoaded())
        delete key->getObj();
}

void plKeyCollector::delAll(const plLocation& loc) {
    std::map<short, std::vector<plKey> >& locList = keys[loc];
    std::map<short, std::vector<plKey> >::iterator it = locList.begin();
    while (it != locList.end()) {
        for (std::vector<plKey>::iterator i2 = it->second.begin(); i2 != it->second.end(); i2++) {
            if ((*i2).Exists() && (*i2).isLoaded())
                delete (*i2)->getObj();
        }
        it++;
    }
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

void plKeyCollector::ChangeLocation(const plLocation& from, const plLocation& to) {
    for (unsigned int i=0; i<TYPESPACE_MAX; i++) {
        if (from == to) {
            // Only flags are different
            for (size_t j=0; j<keys[from][i].size(); j++)
                keys[from][i][j]->setLocation(to);
        } else {
            size_t begin = keys[to][i].size();
            keys[to][i].resize(begin + keys[from][i].size());
            for (size_t j=0; j<keys[from][i].size(); j++) {
                keys[to][i][begin+j] = keys[from][i][j];
                keys[to][i][begin+j]->setLocation(to);
            }
        }
    }
    keys.erase(keys.find(from));
}

void plKeyCollector::MoveKey(plKey key, const plLocation& to) {
    std::vector<plKey>& keyList = keys[key->getLocation()][key->getType()];
    std::vector<plKey>::iterator it = keyList.begin();
    size_t sub = 0;
    while (it != keyList.end()) {
        if ((*it) == key) {
            it = keyList.erase(it);
            sub++;
        } else {
            (*it)->setID((*it)->getID() - sub);
            it++;
        }
    }
    key->setLocation(to);
    add(key);
}
