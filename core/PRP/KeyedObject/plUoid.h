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
 * an identification for the object that the plKey references.
 */
class PLASMA_DLL plUoid
{
private:
    enum ContentsFlags
    {
        kHasCloneIDs  = 0x1,
        kHasLoadMask  = 0x2,
        kHasLoadMask2 = 0x4
    };

private:
    plLocation location;
    plLoadMask loadMask;
    short classType;
    ST::string objName;
    unsigned int objID, clonePlayerID, cloneID;

public:
    /** Constructs a new, empty Uoid */
    plUoid() : classType((short)0x8000), objID(), clonePlayerID(), cloneID() { }

    /**
     * Compares two Uoids by contents.  Only the location, type and name
     * are actually compared -- fields such as flags, object ID, and
     * clone IDs are ignored in the comparison
     */
    bool operator==(const plUoid& other) const;
    bool operator!=(const plUoid& other) const { return !operator==(other); }

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
    ST::string toString() const;

public:
    /** Returns the class type of the object */
    short getType() const { return classType; }

    /** Returns the name of the object */
    const ST::string& getName() const { return objName; }

    /** Returns the location where the object is stored */
    const plLocation& getLocation() const { return location; }

    /** Returns the load mask of the object */
    const plLoadMask& getLoadMask() const { return loadMask; }

    /**
     * Returns the list ID for the object in the Page Key index.
     * (Only meaningful for EoA and Hex Isle)
     */
    unsigned int getID() const { return objID; }

    /** Returns the object's clone ID (useless) */
    unsigned int getCloneID() const { return cloneID; }

    /** Returns the object's clone Player ID (useless) */
    unsigned int getClonePlayerID() const { return clonePlayerID; }

    /** Set the class type of the object referred to by this Uoid */
    void setType(short type) { classType = type; }

    /** Set the name of the object referred to by this Uoid */
    void setName(const ST::string& name) { objName = name; }

    /** Set the location of the object referred to by this Uoid */
    void setLocation(const plLocation& loc) { location = loc; }

    /** Set the load mask of this Uoid and referenced object */
    void setLoadMask(const plLoadMask& mask) { loadMask = mask; }

    /**
     * Set the list ID for the object within the Page Key index.
     * This is only meaningful for EoA and Hex Isle, and should be
     * left for the ResManager to handle automatically.
     */
    void setID(unsigned int id) { objID = id; }

    /** Sets the Clone IDs for the object (useless) */
    void setCloneIDs(unsigned int clone, unsigned int clonePlayer)
    {
        cloneID = clone;
        clonePlayerID = clonePlayer;
    }
};

#endif
