#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "ResManager/pdUnifiedTypeMap.h"
#include "ResManager/plResManager.h"

#define CREATABLE(classname, classid, parentclass) \
public: \
    virtual short ClassIndex() const { return classid; } \
    virtual bool ClassInstance(short hClass) const { \
        if (hClass == classid) \
            return true; \
        return parentclass::ClassInstance(hClass); \
    } \
    static classname* Convert(plCreatable* pCre, bool requireValid = true) { \
        if (pCre == NULL) \
            return NULL; \
        if (pCre->ClassInstance(classid)) \
            return (classname*)pCre; \
        if (requireValid) { \
            short otherClassId = pCre->ClassIndex(); \
            delete pCre; \
            throw hsBadParamException(__FILE__, __LINE__, \
                    plString::Format("Required conversion failed for %s -> %s", \
                                     pdUnifiedTypeMap::ClassName(otherClassId), \
                                     pdUnifiedTypeMap::ClassName(classid))); \
        } \
        return NULL; \
    }


DllClass plCreatable {
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
DllClass plCreatableStub : public plCreatable {
private:
    short fClassIdx;
    unsigned char* fData;
    size_t fDataLen;

public:
    /** Constructs an empty stub.  Only useful for NULL creatables. */
    plCreatableStub();

    /** Constructs a stub whose type is \a hClass, and size is \a length */
    plCreatableStub(short hClass, size_t length);

    virtual ~plCreatableStub();

    virtual short ClassIndex() const { return fClassIdx; }
    virtual bool isStub() const { return true; }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    /**
     * Returns a pointer to the data buffer that contains the
     * creatable's contents.
     * \sa getLength()
     */
    const unsigned char* getData() const { return fData; }

    /**
     * Returns the size of the creatable's data buffer
     * \sa getData()
     */
    size_t getLength() const { return fDataLen; }
};


/**
 * \brief Base class that can receive plMessages.
 *
 * Within the Plasma game engines, any class that can receive (and handle)
 * a plMessage is derived from this class.  Specifically, it implements
 * a MsgReceive() function that handles the message that was thrown at it.
 * In libPlasma, this functionality is not necessary, so its only real
 * purpose here is to reserve the plReceiver Class Index.
 */
DllClass plReceiver : public plCreatable {
    CREATABLE(plReceiver, kReceiver, plCreatable)
};

#endif
