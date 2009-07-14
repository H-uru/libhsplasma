#ifndef _PLKEYCOLLECTOR_H
#define _PLKEYCOLLECTOR_H

#include "PRP/KeyedObject/plKey.h"
#include <map>
#include <vector>

typedef std::map<plLocation, std::map<short, std::vector<plKey> > > keymap_t;

/**
 * \brief This class is used internally by the plResManager as a storage
 *        backend for plKeys.
 * 
 * It also "owns" the hsKeyedObjects referenced by its stored keys, in
 * the manner that deleting keys from here will cause the associated
 * hsKeyedObject to also be deleted.
 */
DllClass plKeyCollector {
private:
    keymap_t keys;

public:
    plKeyCollector();
    ~plKeyCollector();

    plKey findKey(plKey match);
    void add(plKey key);
    void del(plKey key);
    void delAll(const plLocation& loc);
    void reserveKeySpace(const plLocation& loc, short type, int num);
    void sortKeys(const plLocation& loc);

    unsigned int countTypes(const plLocation& loc, bool checkKeys = false);
    unsigned int countKeys(const plLocation& loc, bool checkKeys = false);
    std::vector<plKey> getKeys(const plLocation& loc, short type,
                               bool checkKeys = false);
    std::vector<short> getTypes(const plLocation& loc, bool checkKeys = false);
    std::vector<plLocation> getPages();

    void ChangeLocation(const plLocation& from, const plLocation& to);
    void MoveKey(plKey key, const plLocation& to);
};

#endif
