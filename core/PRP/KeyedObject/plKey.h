#ifndef _PLKEY_H
#define _PLKEY_H

#include "plUoid.h"

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
DllClass plKeyData {
private:
    plUoid fUoid;
    class hsKeyedObject* fObjPtr;

    hsUint32 fFileOff, fObjSize;
    hsUint32 fRefCnt;

public:
    /**
     * Construct key data for an empty object.  The key will need to be
     * filled in with meaningful data before it is useful.
     */
    plKeyData();

    /**
     * Don't ever use this directly (i.e., don't ever allocate plKeyData
     * objects on the stack).  The key will be automatically deleted
     * once its ref count is zero (meaning there are no more keys that
     * own references to this KeyData).
     */
    ~plKeyData() { }

private:
    hsUint32 Ref() { return ++fRefCnt; }
    void UnRef();
    friend class plKey;

public:
    /**
     * Compares the contents of this key to another to see if they are
     * equivalent.  This basically just calls the == operator on the
     * plUoid (so storage information is not compared).
     */
    bool operator==(plKeyData& other) const;

    /**
     * Converts the key to a string.  If the key is empty, returns "NULL",
     * otherwise, returns the plUoid's string representation.
     * \sa plUoid::toString()
     */
    plString toString() const;

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
    void readUoid(hsStream* S);

    /**
     * Write a key without the index information or exists bool directly
     * to a stream.  You generally shouldn't use this directly, but
     * rather use the plResManager to write keys.
     * \sa readUoid(), write(), plResManager::WriteUoid()
     */
    void writeUoid(hsStream* S);

    /**
     * Write a plKey tag describing this key into the PRC document.
     * Unlike the other reading and writing functions, you can use
     * this directly to write keys to PRC output.
     * \sa PrcParse()
     */
    void prcWrite(pfPrcHelper* prc);

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

    /** Returns a pointer to the object referenced by this key */
    class hsKeyedObject* getObj() { return fObjPtr; }

    /** Sets the object referenced by this key. */
    void setObj(class hsKeyedObject* obj) { fObjPtr = obj; }

    /** Returns the Class Index of the object referenced by this key */
    short getType() const { return fUoid.getType(); }

    /** Returns the name of the object referenced by this key */
    const plString& getName() const { return fUoid.getName(); }

    /** Returns the location where this key and its object are stored */
    const plLocation& getLocation() const { return fUoid.getLocation(); }

    /** Returns the load mask of the object referenced by this key */
    const plLoadMask& getLoadMask() const { return fUoid.getLoadMask(); }

    /** Returns the numeric ID of the key; only meaningful for EoA, Hex Isle and MOUL */
    hsUint32 getID() const { return fUoid.getID(); }

    /** Returns the Clone ID of this key (usually 0) */
    hsUint32 getCloneID() const { return fUoid.getCloneID(); }

    /** Returns the Clone Player ID of this key (usually 0) */
    hsUint32 getClonePlayerID() const { return fUoid.getClonePlayerID(); }

    /**
     * Returns the location in the PRP file where this key's data starts.
     * This is not updated until the PRP file's key index is either read
     * or written.
     */
    hsUint32 getFileOff() const { return fFileOff; }

    /**
     * Returns the total size of the object referenced by this key.
     * This is not updated until the PRP file's key index is either read
     * or written.
     */
    hsUint32 getObjSize() const { return fObjSize; }

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
    void setName(const plString& name) { fUoid.setName(name); }

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
    void setID(hsUint32 id) { fUoid.setID(id); }

    /** Sets the Clone IDs of the key.  Basically useless. */
    void setCloneIDs(hsUint32 clone, hsUint32 player) { fUoid.setCloneIDs(clone, player); }

    /**
     * Set the file offset for the object pointed to by the key.  This
     * is done automatically by the plResManager when writing pages.
     */
    void setFileOff(hsUint32 off) { fFileOff = off; }

    /**
     * Set the object size for the object pointed to by the key.  This
     * is done automatically by the plResManager when writing pages.
     */
    void setObjSize(hsUint32 size) { fObjSize = size; }
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
DllClass plKey {
private:
    plKeyData* fKeyData;

public:
    /** Constructs a NULL plKey.  This will return false for Exists() */
    plKey();

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
    bool operator==(const plKey& other) const;

    /** Returns true if this key's plKeyData is 'other' */
    bool operator==(const plKeyData* other) const;

    /** Returns true if the keys point to different plKeyData structures */
    bool operator!=(const plKey& other) const;

    /** Returns true if this key's plKeyData is NOT 'other' */
    bool operator!=(const plKeyData* other) const;

    /** Provides sorting functionality for STL containers */
    bool operator<(const plKey& other) const;

    /**
     * Tests to see if the key refers to an object (not NULL key).
     * This will return false for empty keys, so it should be checked
     * any place where an empty key can be specified.
     */
    bool Exists() const;

    /**
     * Returns whether the object referenced by the key is currently
     * loaded by the plResManager.
     *
     * NOTE: For empty keys (Exists() == false), this will always
     * return true!
     */
    bool isLoaded() const;
};

#endif
