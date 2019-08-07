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

#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "PRP/plCreatable.h"
#include "ResManager/plResManager.h"
#include "plKey.h"

/**
 * \brief The base class for any top-level PRP object.
 *
 * Any class that has a unique plKey and can be loaded from a PRP is
 * derived from this class.  hsKeyedObject and plKey go hand-in-hand,
 * and as such, each contains a reference to the other.  For Creatable
 * Class IDs, hsKeyedObject classes will always be in the < 0x0200 range,
 * whereas non-keyed classes are >= 0x0200.
 */
class PLASMA_DLL hsKeyedObject : public plCreatable
{
    CREATABLE(hsKeyedObject, kKeyedObject, plCreatable)

private:
    plKey myKey;

public:
    /**
     * Initializes the key for this KeyedObject with the specified
     * object name.  You will need to either set the location manually
     * or add it to the ResManager for the key's location to be valid.
     * \sa plResManager::AddKey(), plResManager::AddObject()
     */
    void init(const ST::string& name);

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    /**
     * Determine if this object's key should be ordered after the specified
     * object's key (for use in plKey list sorting).
     * Important Note:  This is not a strict ordering -- that is, if
     * key A is not ordered after key B, it does not necessarily imply that
     * key B should be ordered after key A.
     */
    virtual bool orderAfter(const hsKeyedObject*) const { return false; }

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    /** Returns the key that describes this object */
    plKey getKey() const { return myKey; }

    /**
     * Set the object's key.  Most of the time, you will never need to
     * use this directly; you should use init() instead
     * \sa init(), plResManager::AddKey(), plResManager::AddObject()
     */
    void setKey(plKey key);
};

/**
 * \brief Stores the stub of an hsKeyedObject class
 *
 * Like plCreatableStub, this class stores a data buffer containing
 * the contents of an unparsed Creatable.  hsKeyedObjectStub is actually
 * just a convenience class to provide the hsKeyedObject interface to
 * the plCreatableStub, specifically, being able to access the object's
 * key.  If your stub is an hsKeyedObject-derived class, it's very
 * highly recommended you use this instead of a normal plCreatableStub!
 * \sa plCreatableStub
 */
class PLASMA_DLL hsKeyedObjectStub : public hsKeyedObject
{
private:
    plCreatableStub* fStub;

public:
    hsKeyedObjectStub() : fStub() { }
    ~hsKeyedObjectStub();

    short ClassIndex() const HS_FINAL_OVERRIDE { return fStub->ClassIndex(); }
    const char* ClassName() const HS_FINAL_OVERRIDE { return "hsKeyedObjectStub"; }
    bool isStub() const HS_FINAL_OVERRIDE { return true; }

    void write(hsStream* S, plResManager* mgr) HS_FINAL_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_FINAL_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_FINAL_OVERRIDE;

public:
    /** Returns the underlying plCreatableStub object of this stub */
    plCreatableStub* getStub() const { return fStub; }

    /** Sets the underlying plCreatableStub object of this stub */
    void setStub(plCreatableStub* stub);
};

#endif
