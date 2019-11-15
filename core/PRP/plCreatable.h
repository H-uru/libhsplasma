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

#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include "ResManager/pdUnifiedTypeMap.h"
#include <string_theory/format>

#define CREATABLE(classname, classid, parentclass) \
public: \
    short ClassIndex() const HS_OVERRIDE { return classid; } \
    bool ClassInstance(short hClass) const HS_OVERRIDE \
    { \
        if (hClass == classid) \
            return true; \
        return parentclass::ClassInstance(hClass); \
    } \
    static classname* Convert(plCreatable* pCre, bool requireValid = true) \
    { \
        if (pCre == nullptr) \
            return nullptr; \
        if (pCre->ClassInstance(classid)) { \
            return static_cast<classname*>(pCre); \
        } else if (requireValid) { \
            short otherClassId = pCre->ClassIndex(); \
            throw hsBadParamException(__FILE__, __LINE__, \
                ST::format("Required conversion failed for {} -> {}", \
                           pdUnifiedTypeMap::ClassName(otherClassId), \
                           pdUnifiedTypeMap::ClassName(classid))); \
        } else { \
            return nullptr; \
        } \
    }


class plResManager;

class PLASMA_DLL plCreatable
{
public:
    plCreatable() { }
    virtual ~plCreatable() { }

    /**
     * Returns the Creatable Class ID for this Creatable.  Use the
     * CREATABLE macro to set this automatically in subclasses.
     */
    virtual short ClassIndex() const = 0;

    /**
     * Returns the Plasma-Engine specific Class ID for this Creatable
     * within the specified Plasma Version.
     */
    short ClassIndex(PlasmaVer ver) const;

    /**
     * Returns a string of the creatable's class name.  Use the
     * CREATABLE macro to set this automatically in subclasses.
     */
    virtual const char* ClassName() const;

    /**
     * Determines whether a creatable is an instance of the specified
     * Class Index (or one of its subclasses).  Use the CREATABLE macro
     * to set this automatically in subclasses.
     */
    virtual bool ClassInstance(short) const { return false; }

    /**
     * Returns whether this is really a plCreatableStub.  Note that
     * stubs will still report their ClassIndex and ClassName correctly,
     * so you must use this function to determine whether a class is
     * actually a stub or the real class.
     */
    virtual bool isStub() const { return false; }

    /**
     * Reads this creatable directly from the stream.  If any keys are
     * read, they will be added to the plResManager automatically.
     */
    virtual void read(hsStream*, plResManager*) { }

    /**
     * Writes this creatable directly to the stream.  The plResManager
     * is used to manage any key references written by this creatable.
     */
    virtual void write(hsStream*, plResManager*) { }

    /**
     * Writes this creatable to a PRC document.
     */
    virtual void prcWrite(pfPrcHelper* prc);

    /**
     * Read this creatable from a PRC tag.  If any keys are parsed,
     * they will be added to the plResManager automatically.
     */
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

    /**
     * Writes this creatable to a PRC document and returns it as a string.
     */
    ST::string toPrc(pfPrcHelper::PrcExclude exclude = pfPrcHelper::kNone);

protected:
    /**
     * This must be overloaded by subclasses to write PRC data specific
     * to the class to the PRC document.  Do not write the top-level
     * creatable tag, that is handled by prcWrite().
     */
    virtual void IPrcWrite(pfPrcHelper* prc) = 0;

    /**
     * This must be overloaded by subclasses to parse PRC data specific
     * to the class from the PRC document.  It is called once for each
     * tag that is a child to the Creatable tag itself, so subclasses
     * should check for each supported tag and handle it accordingly if
     * it matches.  If the tag is not recognized, it should be passed
     * along to the parent class.
     */
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


/**
 * \brief Stores the contents of a Creatable without actually parsing it.
 *
 * This stores a plCreatable (most commonly, one that isn't supported,
 * or one found in an SDL node) as a data buffer that can easily be
 * read or written as a chunk of data, but is not parsed.  This can be
 * useful so that files with unsupported classes don't lose information,
 * but can also be harmful, as changes to plKeys stored in the stubbed
 * object will not get updated if they are changed.  In general, it's
 * a good idea to use a real Creatable class whenever possible.
 * \sa hsKeyedObjectStub
 */
class PLASMA_DLL plCreatableStub : public plCreatable
{
private:
    short fClassIdx;
    uint8_t* fData;
    size_t fDataLen;

public:
    /** Constructs an empty stub.  Only useful for NULL creatables. */
    plCreatableStub() : fClassIdx((short)0x8000), fData(), fDataLen() { }

    /** Constructs a stub whose type is \a hClass, and size is \a length */
    plCreatableStub(short hClass, size_t length);

    ~plCreatableStub();

    short ClassIndex() const HS_FINAL_OVERRIDE { return fClassIdx; }
    bool isStub() const HS_FINAL_OVERRIDE { return true; }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper*) HS_OVERRIDE { }
    void IPrcParse(const pfPrcTag*, plResManager*) HS_OVERRIDE { }

public:
    /**
     * Returns a pointer to the data buffer that contains the
     * creatable's contents.
     * \sa getLength()
     */
    const uint8_t* getData() const { return fData; }

    /**
     * Returns the size of the creatable's data buffer
     * \sa getData()
     */
    size_t getLength() const { return fDataLen; }
};

/**
 * Cast any plCreatable to another creatable subclass.  Alternate syntax
 * for plCastedType::Convert(pCre).
 */
template <class Creatable_T>
Creatable_T *creatable_cast(plCreatable *pCre, bool requireValid = true)
{
    return Creatable_T::Convert(pCre, requireValid);
}

#endif
