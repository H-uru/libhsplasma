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

class plKeyVector
{
    std::vector<plKey> fKeys;
    uint32_t fFlags;

public:
    plKeyVector() : fFlags() { }

    uint32_t getFlags() const { return fFlags; }

    bool checkFlag(uint32_t flag) const
    {
        return (fFlags & flag);
    }

    void setFlag(uint32_t flag, bool on = true)
    {
        if (on)
            fFlags |= flag;
        else
            fFlags &= ~flag;
    }

    void setFlags(uint32_t flags) { fFlags = flags; }

    std::vector<plKey>::iterator begin() HS_NOEXCEPT { return fKeys.begin(); }
    bool empty() const HS_NOEXCEPT { return fKeys.empty(); }
    std::vector<plKey>::iterator end() HS_NOEXCEPT { return fKeys.end(); }
    std::vector<plKey>::iterator erase(std::vector<plKey>::iterator pos) { return fKeys.erase(pos); }
    void push_back(const plKey& value) { fKeys.push_back(value); }
    void reserve(size_t count) { fKeys.reserve(count); }
    void resize(size_t count) { fKeys.resize(count); }
    size_t size() const HS_NOEXCEPT { return fKeys.size(); }

    std::vector<plKey>& operator *() { return fKeys; }
    const std::vector<plKey>& operator *() const { return fKeys; }

    plKey& operator[](size_t idx) { return fKeys[idx]; }
    const plKey& operator[](size_t idx) const { return fKeys[idx]; }
};

typedef std::map<plLocation, std::map<short, plKeyVector>> keymap_t;

/**
 * \brief This class is used internally by the plResManager as a storage
 *        backend for plKeys.
 *
 * It also "owns" the hsKeyedObjects referenced by its stored keys, in
 * the manner that deleting keys from here will cause the associated
 * hsKeyedObject to also be deleted.
 */
class HSPLASMA_EXPORT plKeyCollector
{
private:
    keymap_t keys;

public:
    enum
    {
        /**
         * Indicates the keys are NOT sorted by name.
         */
        kNotOptimized = 0x01,
    };

public:
    plKeyCollector() { }
    ~plKeyCollector();

    plKey findKey(const plKey& match);
    void add(const plKey& key);
    void del(const plKey& key);
    void delAll(const plLocation& loc);
    void cleanupKeys();
    void reserveKeySpace(const plLocation& loc, short type, int num);

    uint32_t getFlags(const plLocation& loc, short type);
    void setFlags(const plLocation& loc, short type, uint32_t flags);

    /**
     * Sorts the keys by index.
     * This sorts the keys by their existing IDs, renumbering any keys that have duplicated IDs
     * and ensuring that all key IDs are contiguous.
     */
    void sortKeys(const plLocation& loc);

    /**
     * Sorts the keys by name.
     * This is used by Myst V, Hex Isle, and some variants of MOUL to perform
     * "optimized" name-based key lookups.
     */
    void optimizeKeys(const plLocation& loc);

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
