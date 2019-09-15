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

#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "PRP/KeyedObject/plKey.h"
#include <map>
#include <vector>

typedef std::map<plLocation, std::map<short, std::vector<plKey>>> keymap_t;

/**
 * \brief This class is used internally by the plResManager as a storage
 *        backend for plKeys.
 *
 * It also "owns" the hsKeyedObjects referenced by its stored keys, in
 * the manner that deleting keys from here will cause the associated
 * hsKeyedObject to also be deleted.
 */
class PLASMA_DLL plKeyCollector
{
private:
    keymap_t keys;

public:
    plKeyCollector() { }
    ~plKeyCollector();

    plKey findKey(const plKey& match);
    void add(const plKey& key);
    void del(const plKey& key);
    void delAll(const plLocation& loc);
    void cleanupKeys();
    void reserveKeySpace(const plLocation& loc, short type, int num);
    void sortKeys(const plLocation& loc);

    unsigned int countTypes(const plLocation& loc, bool checkKeys = false);
    unsigned int countKeys(const plLocation& loc, bool checkKeys = false);
    std::vector<plKey> getKeys(const plLocation& loc, short type,
                               bool checkKeys = false);
    std::vector<short> getTypes(const plLocation& loc, bool checkKeys = false);
    std::vector<plLocation> getPages();

    void ChangeLocation(const plLocation& from, const plLocation& to);
    void MoveKey(const plKey& key, const plLocation& to);
};

#endif
