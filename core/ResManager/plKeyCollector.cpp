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
    for (auto it = keys.begin(); it != keys.end(); it++) {
        for (auto i2 = it->second.begin(); i2 != it->second.end(); i2++) {
            for (auto i3 = i2->second.begin(); i3 != i2->second.end(); i3++) {
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
    const auto& kList = keys[match->getLocation()][match->getType()];
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
    keys[key->getLocation()][key->getType()].setFlag(kNotOptimized);
}

void plKeyCollector::del(const plKey& key)
{
    auto& keyList = keys[key->getLocation()][key->getType()];
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
    auto& locList = keys[loc];
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

uint32_t plKeyCollector::getFlags(const plLocation& loc, short type)
{
    return keys[loc][type].getFlags();
}

void plKeyCollector::setFlags(const plLocation& loc, short type, uint32_t flags)
{
    keys[loc][type].setFlags(flags);
}

void plKeyCollector::sortKeys(const plLocation& loc)
{
    std::vector<short> types = getTypes(loc);
    for (short type : types) {
        std::sort(keys[loc][type].begin(), keys[loc][type].end(),
            [](const plKey& a, const plKey& b) { return a->getID() < b->getID(); });
        for (size_t i = 0; i < keys[loc][type].size(); ++i) {
            keys[loc][type][i]->setID(i + 1);

            // Side effect: verify that pages are telling the truth about
            // whether or not they are optimized. Fixes incorrect pages
            // exported by previous revisions of HSPlasma.
            if (!keys[loc][type].checkFlag(kNotOptimized) && i + 1 < keys[loc][type].size()) {
                const plKey& a = keys[loc][type][i];
                const plKey& b = keys[loc][type][i + 1];
                if (!(a->getName().compare_i(b->getName()) < 0)) {
                    plDebug::Warning("Keyring for page {} type {:04X} erroneously thinks it's optimized ({} >= {})",
                        loc.toString(), type, a.toString(), b.toString());
                    keys[loc][type].setFlag(kNotOptimized);
                }
            }
        }
    }
}

void plKeyCollector::optimizeKeys(const plLocation& loc)
{
    std::vector<short> types = getTypes(loc);
    for (short type : types) {
        std::sort(keys[loc][type].begin(), keys[loc][type].end(),
            [](const plKey& a, const plKey& b) { return a->getName().compare_i(b->getName()) < 0; });
        for (size_t i = 0; i < keys[loc][type].size(); ++i)
            keys[loc][type][i]->setID(i + 1);
        keys[loc][type].setFlag(kNotOptimized, false);
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
        return keys[loc][type].toStdVector();
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
                keys[to][i][begin+j]->setID(begin+j+1);
            }
            keys[to][i].setFlag(kNotOptimized);
        }
    }
    keys.erase(keys.find(from));
}

void plKeyCollector::MoveKey(const plKey& key, const plLocation& to)
{
    auto& keyList = keys[key->getLocation()][key->getType()];
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
    keys[to][key->getType()].push_back(key);
    key->setID(keys[to][key->getType()].size());
    keys[to][key->getType()].setFlag(kNotOptimized);
}
