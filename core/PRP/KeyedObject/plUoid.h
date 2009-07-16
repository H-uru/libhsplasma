#ifndef _PLUOID_H
#define _PLUOID_H

#include "plLoadMask.h"
#include "plLocation.h"

/**
 * \brief Universal Object IDentifier.
 *
 * This class contains the identification components to uniquely identify
 * any KeyedObject within a game.  This includes information such as name,
 * type and location of the object, so it can be compared or looked up
 * to find the actual object.  Most notably, plUoid is used by plKey as
 * an identification for the object that hte plKey references.
 */
DllClass plUoid {
private:
    enum ContentsFlags {
        kHasCloneIDs = 0x1,
        kHasLoadMask = 0x2
    };

private:
    plLocation location;
    plLoadMask loadMask;
    short classType;
    plString objName;
    unsigned int objID, clonePlayerID, cloneID;
    unsigned char eoaExtra;

public:
    /** Constructs a new, empty Uoid */
    plUoid();

    /** Copy constructor, makes an identical Uoid to the source */
    plUoid(const plUoid& other);

    ~plUoid();

    /** Copies a uoid's data into this Uoid */ 
    plUoid& operator=(const plUoid& other);

    /**
     * Compares two Uoids by contents.  Only the location, type and name
     * are actually compared -- fields such as flags, object ID, and
     * clone IDs are ignored in the comparison
     */
    bool operator==(const plUoid& other) const;

    /** Compares two Uoids by contents, for use in STL containers */
    bool operator<(const plUoid& other) const;

    /** Read this Uoid directly from a stream. */
    void read(hsStream* S);

    /** Write this Uoid directly to a stream. */
    void write(hsStream* S);

    /** Read this Uoid as a plKey tag in a PRC document */
    void prcWrite(pfPrcHelper* prc);

    /** Write this Uoid as a plKey tag in a PRC document */
    void prcParse(const pfPrcTag* tag);

    /**
     * Returns a string representation of the Uoid, in the form:
     * "<seqPrefix|pageNum>[typeID]object_name"
     */
    plString toString() const;

    /** Returns the class type of the object */
    short getType() const;

    /** Returns the name of the object */
    const plString& getName() const;

    /** Returns the location where the object is stored */
    const plLocation& getLocation() const;

    /** Returns the load mask of the object */
    const plLoadMask& getLoadMask() const;

    /**
     * Returns the list ID for the object in the Page Key index.
     * (Only meaningful for EoA and Hex Isle)
     */
    unsigned int getID() const;

    /** Returns the object's clone ID (useless) */
    unsigned int getCloneID() const;

    /** Returns the object's clone Player ID (useless) */
    unsigned int getClonePlayerID() const;

    /** Set the class type of the object referred to by this Uoid */
    void setType(short type);

    /** Set the name of the object referred to by this Uoid */
    void setName(const plString& name);

    /** Set the location of the object referred to by this Uoid */
    void setLocation(const plLocation& loc);

    /** Set the load mask of this Uoid and referenced object */
    void setLoadMask(const plLoadMask& mask);

    /**
     * Set the list ID for the object within the Page Key index.
     * This is only meaningful for EoA and Hex Isle, and should be
     * left for the ResManager to handle automatically.
     */
    void setID(unsigned int id);

    /** Sets the Clone IDs for the object (useless) */
    void setCloneIDs(unsigned int cloneID, unsigned int clonePlayerID);
};

#endif
