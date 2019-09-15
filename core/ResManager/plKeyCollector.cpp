/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plKeyCollector.h"
#include "pdUnifiedTypeMap.h"
#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Debug/plDebug.h"
#include <list>

plKeyCollector::~plKeyCollector()
{
    unsigned keysLeft = 0;

    // This is now the "ultimate owner" of KeyedObjects, so we must delete
    // all the KOs that we own...
    for (keymap_t::iterator it = keys.begin(); it != keys.end(); it++) {
        for (std::map<short, std::vector<plKey> >::iterator i2 = it->second.begin(); i2 != it->second.end(); i2++) {
            for (std::vector<plKey>::iterator i3 = i2->second.begin(); i3 != i2->second.end(); i3++) {
                if ((*i3).Exists() && (*i3).isLoaded()) {
                    ++keysLeft;
                    delete (*i3)->getObj();
                }
            }
        }
    }

    if (keysLeft)
        plDebug::Warning("Warning: {} keys were still loaded when the ResManager was destroyed.\n", keysLeft);
}

plKey plKeyCollector::findKey(const plKey& match)
{
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

void plKeyCollector::add(const plKey& key)
{
    keys[key->getLocation()][key->getType()].push_back(key);
    if (key->getID() == 0)
        key->setID(keys[key->getLocation()][key->getType()].size());
}

void plKeyCollector::del(const plKey& key)
{
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
    if (keyList.empty())
        keys[key->getLocation()].erase(key->getType());
    if (keys[key->getLocation()].empty())
        keys.erase(key->getLocation());
    if (key.Exists() && key.isLoaded()) {
        key->deleteObj();
    }
}

void plKeyCollector::delAll(const plLocation& loc)
{
    std::map<short, std::vector<plKey> >& locList = keys[loc];
    auto loc_iter = locList.begin();
    while (loc_iter != locList.end()) {
        auto key_iter = loc_iter->second.begin();
        while (key_iter != loc_iter->second.end()) {
            if (key_iter->Exists() && key_iter->isLoaded()) {
                (*key_iter)->deleteObj();
                key_iter = loc_iter->second.erase(key_iter);
            } else {
                ++key_iter;
            }
        }
        ++loc_iter;
    }
    cleanupKeys();
}

void plKeyCollector::cleanupKeys()
{
    auto loc_iter = keys.begin();
    while (loc_iter != keys.end()) {
        auto tp_iter = loc_iter->second.begin();
        while (tp_iter != loc_iter->second.end()) {
            auto key_iter = tp_iter->second.begin();
            while (key_iter != tp_iter->second.end()) {
                const plKey &key = *key_iter;
                if (!key.Exists()) {
                    plDebug::Warning("WARNING: Got NULL key in the ResManager!\n");
                    key_iter = tp_iter->second.erase(key_iter);
                    continue;
                }

                if ((key.isLoaded() && key->CountRefs() == 2)
                        || (!key.isLoaded() && key->CountRefs() == 1)) {
                    // We are the only remaining owner of this key.  Nuke it.
                    key->deleteObj();
                    key_iter = tp_iter->second.erase(key_iter);
                } else {
                    ++key_iter;
                }
            }
            if (tp_iter->second.empty())
                tp_iter = loc_iter->second.erase(tp_iter);
            else
                ++tp_iter;
        }
        if (keys.empty())
            loc_iter = keys.erase(loc_iter);
        else
            ++loc_iter;
    }
}

void plKeyCollector::reserveKeySpace(const plLocation& loc, short type, int num)
{
    keys[loc][type].reserve(num);
}

void plKeyCollector::sortKeys(const plLocation& loc)
{
    std::vector<short> types = getTypes(loc);
    std::list<plKey> sortKeys;
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
        keys[loc][types[i]] = std::vector<plKey>(sortKeys.begin(), sortKeys.end());
    }
}

unsigned int plKeyCollector::countTypes(const plLocation& loc, bool checkKeys)
{
    return getTypes(loc, checkKeys).size();
}

unsigned int plKeyCollector::countKeys(const plLocation& loc, bool checkKeys)
{
    unsigned int kCount = 0;
    for (unsigned int i=0; i<TYPESPACE_MAX; i++)
        kCount += getKeys(loc, i, checkKeys).size();
    return kCount;
}

std::vector<plKey> plKeyCollector::getKeys(const plLocation& loc, short type,
                                           bool checkKeys)
{
    if (checkKeys) {
        std::list<plKey> kList;
        std::vector<plKey>::iterator it;
        for (it = keys[loc][type].begin(); it != keys[loc][type].end(); it++) {
            if ((*it).Exists() && (*it).isLoaded())
                kList.push_back(*it);
            else
                plDebug::Debug("Got erroneous key: {}", it->toString());
        }
        return std::vector<plKey>(kList.begin(), kList.end());
    } else {
        return keys[loc][type];
    }
}

std::vector<short> plKeyCollector::getTypes(const plLocation& loc, bool checkKeys)
{
    std::list<short> types;
    for (unsigned short i=0; i<TYPESPACE_MAX; i++) {
        if (checkKeys) {
            bool hasValidKeys = false;
            std::vector<plKey>::iterator it;
            for (it = keys[loc][i].begin(); it != keys[loc][i].end(); it++) {
                if ((*it).Exists() && (*it).isLoaded()) {
                    hasValidKeys = true;
                    break;
                } else {
                    plDebug::Debug("Got erroneous key: {}", it->toString());
                }
            }
            if (hasValidKeys)
                types.push_back(i);
        } else {
            if (keys[loc][i].size() > 0)
                types.push_back(i);
        }
    }
    return std::vector<short>(types.begin(), types.end());
}

std::vector<plLocation> plKeyCollector::getPages()
{
    std::list<plLocation> pages;
    keymap_t::iterator i;
    for (i = keys.begin(); i != keys.end(); i++)
        pages.push_back(i->first);
    return std::vector<plLocation>(pages.begin(), pages.end());
}

void plKeyCollector::ChangeLocation(const plLocation& from, const plLocation& to)
{
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

void plKeyCollector::MoveKey(const plKey& key, const plLocation& to)
{
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
    if (keyList.empty())
        keys[key->getLocation()].erase(key->getType());
    if (keys[key->getLocation()].empty())
        keys.erase(key->getLocation());
    key->setLocation(to);
    add(key);
}
