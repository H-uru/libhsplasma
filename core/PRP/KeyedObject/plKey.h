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

#ifndef _PLKEY_H
#define _PLKEY_H

#include "plUoid.h"
#include <functional>
#include <list>

#define GET_KEY_OBJECT(key, classname) \
    ((key.Exists() && key.isLoaded()) \
     ? classname::Convert(key->getObj()) \
     : NULL)

#define GET_OBJECT_KEY(obj) \
    (obj == NULL ? plKey() : obj->getKey())

/**
 * \brief Contains plKey data.
 *
 * This class contains the actual description and pointers for hsKeyedObjects,
 * and is used by plKey.  You generally shouldn't use this class directly,
 * but rather keep it contained in a plKey object, and use plKeyData's members
 * through the plKey's overloaded pointer operators.
 */
class PLASMA_DLL plKeyData {
private:
    plUoid fUoid;
    class hsKeyedObject* fObjPtr;

    uint32_t fFileOff, fObjSize;
    uint32_t fRefCnt;

public:
    /**
     * Construct key data for an empty object.  The key will need to be
     * filled in with meaningful data before it is useful.
     */
    plKeyData() : fUoid(), fObjPtr(NULL), fFileOff(0), fObjSize(0),
                  fRefCnt(0) { }

    /**
     * Don't ever use this directly (i.e., don't ever allocate plKeyData
     * objects on the stack).  The key will be automatically deleted
     * once its ref count is zero (meaning there are no more keys that
     * own references to this KeyData).
     */
    ~plKeyData() { }

    /** Return the number of active "owners" of this key. */
    uint32_t CountRefs() const { return fRefCnt; }

    typedef std::function<void (hsKeyedObject*)> AfterLoadCallback;

private:
    std::list<AfterLoadCallback> fCallbacks;

    void Ref() { ++fRefCnt; }
    void UnRef();
    friend class plKey;

public:
    /**
     * Compares the contents of this key to another to see if they are
     * equivalent.  This basically just calls the == operator on the
     * plUoid (so storage information is not compared).
     */
    bool operator==(plKeyData& other) const { return (fUoid == other.fUoid); }

    /**
     * Read a key directly from the key index of a PRP file.  This will
     * include the file offset and size where the hsKeyedObject is stored.
     * You generally shouldn't use this directly, but rather use the
     * plResManager to read keys.
     * \sa write(), readUoid(), plResManager::ReadKey()
     */
    void read(hsStream* S);

    /**
     * Write a key directly to the key index of a PRP file.  This includes
     * the file offset and size information for the hsKeyedObject.
     * You generally shouldn't use this directly, but rather use the
     * plResManager to write keys.
     * \sa read(), writeUoid(), plResManager::WriteKey()
     */
    void write(hsStream* S);

    /**
     * Read a key without the index information or exists bool directly
     * from a stream.  You generally shouldn't use this directly, but
     * rather use the plResManager to read keys.
     * \sa writeUoid(), read(), plResManager::ReadUoid()
     */
    void readUoid(hsStream* S) { fUoid.read(S); }

    /**
     * Write a key without the index information or exists bool directly
     * to a stream.  You generally shouldn't use this directly, but
     * rather use the plResManager to write keys.
     * \sa readUoid(), write(), plResManager::WriteUoid()
     */
    void writeUoid(hsStream* S) { fUoid.write(S); }

    /**
     * Write a plKey tag describing this key into the PRC document.
     * \sa PrcParse()
     */
    void prcWriteUoid(pfPrcHelper* prc);

    /**
     * Parse a plKey tag from the PRC document into this structure.
     * You generally shouldn't use this directly, but rather use the
     * plResManager to parse keys.
     * \sa prcWrite(), plResManager::prcParseKey()
     */
    static plKeyData* PrcParse(const pfPrcTag* tag);

public:
    /** Returns the plUoid that describes the object */
    plUoid& getUoid() { return fUoid; }

    /** Returns the plUoid that describes the object */
    const plUoid& getUoid() const { return fUoid; }

    /** Returns a pointer to the object referenced by this key */
    class hsKeyedObject* getObj() { return fObjPtr; }

    /** Returns a const pointer to the object referenced by this key */
    const class hsKeyedObject* getObj() const { return fObjPtr; }

    /** Sets the object referenced by this key. */
    void setObj(class hsKeyedObject* obj);

    /** Delete object referenced by this key. */
    void deleteObj();

    /** Returns the Class Index of the object referenced by this key */
    short getType() const { return fUoid.getType(); }

    /** Returns the name of the object referenced by this key */
    const ST::string& getName() const { return fUoid.getName(); }

    /** Returns the location where this key and its object are stored */
    const plLocation& getLocation() const { return fUoid.getLocation(); }

    /** Returns the load mask of the object referenced by this key */
    const plLoadMask& getLoadMask() const { return fUoid.getLoadMask(); }

    /** Returns the numeric ID of the key; only meaningful for EoA, Hex Isle and MOUL */
    uint32_t getID() const { return fUoid.getID(); }

    /** Returns the Clone ID of this key (usually 0) */
    uint32_t getCloneID() const { return fUoid.getCloneID(); }

    /** Returns the Clone Player ID of this key (usually 0) */
    uint32_t getClonePlayerID() const { return fUoid.getClonePlayerID(); }

    /**
     * Returns the location in the PRP file where this key's data starts.
     * This is not updated until the PRP file's key index is either read
     * or written.
     */
    uint32_t getFileOff() const { return fFileOff; }

    /**
     * Returns the total size of the object referenced by this key.
     * This is not updated until the PRP file's key index is either read
     * or written.
     */
    uint32_t getObjSize() const { return fObjSize; }

    /**
     * Sets the Class Index of the object referenced by this key.
     * You should not use this directly, but rather call hsKeyedObject::init()
     * to set up the key for an object.
     * \sa hsKeyedObject::init()
     */
    void setType(short type) { fUoid.setType(type); }

    /**
     * Sets the name of an object/key.  This can be done at any time.
     * \sa hsKeyedObject::init()
     */
    void setName(const ST::string& name) { fUoid.setName(name); }

    /**
     * Sets the location of this key and its object.  Generally, you should
     * not use this directly, but rather use the plResManager to manage
     * a key's location.
     * \sa plResManager::MoveKey(), plResManager::ChangeLocation()
     */
    void setLocation(const plLocation& loc) { fUoid.setLocation(loc); }

    /**
     * Sets the load mask of this object and key.  This can be done at
     * any time.
     */
    void setLoadMask(const plLoadMask& mask) { fUoid.setLoadMask(mask); }

    /**
     * Sets the numeric ID of this key.  This is handled automatically
     * by the plResManager while managing keys, so you should never
     * call this directly unless you are not using a ResManager.
     */
    void setID(uint32_t id) { fUoid.setID(id); }

    /** Sets the Clone IDs of the key. */
    void setCloneIDs(uint32_t clone, uint32_t player) { fUoid.setCloneIDs(clone, player); }

    /**
     * Set the file offset for the object pointed to by the key.  This
     * is done automatically by the plResManager when writing pages.
     */
    void setFileOff(uint32_t off) { fFileOff = off; }

    /**
     * Set the object size for the object pointed to by the key.  This
     * is done automatically by the plResManager when writing pages.
     */
    void setObjSize(uint32_t size) { fObjSize = size; }

    /**
     * Add callback to be called after referenced object is loaded. 
     * Callbacks added after object load will be executed immediately.
     */
    void addCallback(AfterLoadCallback callback);

    /** Remove all callbacks, without executing */
    void clearCallbacks() { fCallbacks.clear(); }
};

/**
 * \brief Describes and points to an hsKeyedObject.
 *
 * This is actually just a ref-counted wrapper for plKeyData.  However,
 * you should never use plKeyData directly, but rather use plKey to
 * hold references to plKeyData objects.  The overloaded operators in
 * plKey allow you to use it as though it were the plKeyData object, so
 * you should generally just think of plKeyData's members as being
 * plKey's members, with the addition of Exists() and isLoaded(), which
 * are direct members of the plKey container.
 */
class PLASMA_DLL plKey {
private:
    plKeyData* fKeyData;

public:
    /** Constructs a NULL plKey.  This will return false for Exists() */
    plKey() : fKeyData(NULL) { }

    /** Copy constructor */
    plKey(const plKey& init);

    /**
     * Copy constructor for plKeyData pointers.  Usually you won't ever
     * need to use this directly; it's mostly here for internal use by
     * the plResManager.
     */
    plKey(plKeyData* init);

    /**
     * Removes a reference to the key.  When there are no more references
     * to the key data, the plKeyData pointer will be deleted.  The object
     * it references, however, will NOT be automatically deleted.  Unless
     * the object is stored in the plResManager, you will need to delete
     * the object yourself.  However, if the object is registered with the
     * plResManager, you should not delete the object.
     */
    virtual ~plKey();

    /** Allows for *(plKey) usage as a pointer. */
    plKeyData& operator*() const { return *fKeyData; }

    /** Allows for (plKey)->member usage as a pointer. */
    plKeyData* operator->() const { return fKeyData; }

    /** Allows for typecasts to plKeyData* pointers. */
    operator plKeyData*() const { return fKeyData; }

    /** Copies and refs the key data in other */
    virtual plKey& operator=(const plKey& other);

    /** Refs the key data and stores it in this key */
    virtual plKey& operator=(plKeyData* other);

    /** Returns true if the keys point to the same plKeyData */
    bool operator==(const plKey& other) const { return fKeyData == other.fKeyData; }

    /** Returns true if this key's plKeyData is 'other' */
    bool operator==(const plKeyData* other) const { return fKeyData == other; }

    /** Returns true if the keys point to different plKeyData structures */
    bool operator!=(const plKey& other) const { return fKeyData != other.fKeyData; }

    /** Returns true if this key's plKeyData is NOT 'other' */
    bool operator!=(const plKeyData* other) const { return fKeyData != other; }

    /** Provides sorting functionality for STL containers */
    bool operator<(const plKey& other) const
    { return fKeyData->getUoid() < other->getUoid(); }

    /**
     * Tests to see if the key refers to an object (not NULL key).
     * This will return false for empty keys, so it should be checked
     * any place where an empty key can be specified.
     */
    bool Exists() const { return (fKeyData != NULL); }

    /**
     * Returns whether the object referenced by the key is currently
     * loaded by the plResManager.
     *
     * NOTE: For empty keys (Exists() == false), this will always
     * return true!
     */
    bool isLoaded() const;

    /**
     * Converts the key to a string.  If the key is empty, returns "NULL",
     * otherwise, returns the plUoid's string representation.
     * \sa plUoid::toString()
     */
    ST::string toString() const;

    /**
     * Determine if this key should be ordered after the specified key.
     * Important Note:  This only works if both keys' referenced objects
     * are loaded.  Also, this is not a strict ordering -- that is, if
     * key A is not ordered after key B, it does not necessarily imply that
     * key B should be ordered after key A.
     */
    bool orderAfter(const plKey& other) const;
};

/** Order a vector of keys for writing in the correct load order. */
std::vector<plKey> hsOrderKeys(const std::vector<plKey>& keys);

#endif
