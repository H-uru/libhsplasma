#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "ResManager/pdUnifiedTypeMap.h"
#include "ResManager/plResManager.h"

#define DECLARE_CREATABLE(classname) \
    virtual short ClassIndex() const; \
    virtual bool ClassInstance(short hClass) const; \
    static classname* Convert(plCreatable* pCre);

#define IMPLEMENT_CREATABLE(classname, classid, parentclass) \
    short classname::ClassIndex() const { return classid; } \
    bool classname::ClassInstance(short hClass) const { \
        if (hClass == classid) return true; \
        return parentclass::ClassInstance(hClass); \
    } \
    classname* classname::Convert(plCreatable* pCre) { \
        if (pCre != NULL && pCre->ClassInstance(classid)) \
            return (classname*)pCre; \
        return NULL; \
    }


DllClass plCreatable {
public:
    plCreatable();
    virtual ~plCreatable();

    /**
     * Returns the Creatable Class ID for this Creatable.  Use the
     * DECLARE_CREATABLE and IMPLEMENT_CREATABLE macros to set this
     * automatically in subclasses.
     */
    virtual short ClassIndex() const =0;

    /**
     * Returns the Plasma-Engine specific Class ID for this Creatable
     * within the specified Plasma Version.
     */
    short ClassIndex(PlasmaVer ver) const;

    /**
     * Returns a string of the creatable's class name.  Use the
     * DECLARE_CREATABLE and IMPLEMENT_CREATABLE macros to set this
     * automatically in subclasses.
     */
    virtual const char* ClassName() const;

    /**
     * Determines whether a creatable is an instance of the specified
     * Class Index (or one of its subclasses).  Use the
     * DECLARE_CREATABLE and IMPLEMENT_CREATABLE macros to set this
     * automatically in subclasses.
     */
    virtual bool ClassInstance(short hClass) const;

    /**
     * Returns whether this is really a plCreatableStub.  Note that
     * stubs will still report their ClassIndex and ClassName correctly,
     * so you must use this function to determine whether a class is
     * actually a stub or the real class.
     */
    virtual bool isStub() const;

    /**
     * Reads this creatable directly from the stream.  If any keys are
     * read, they will be added to the plResManager automatically.
     */
    virtual void read(hsStream* S, plResManager* mgr);

    /**
     * Writes this creatable directly to the stream.  The plResManager
     * is used to manage any key references written by this creatable.
     */
    virtual void write(hsStream* S, plResManager* mgr);

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
    virtual void IPrcWrite(pfPrcHelper* prc) =0;

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

DllClass plCreatableStub : public plCreatable {
protected:
    short fClassIdx;
    unsigned char* fData;
    size_t fDataLen;

public:
    plCreatableStub();
    plCreatableStub(short hClass, size_t length);
    virtual ~plCreatableStub();

    virtual short ClassIndex() const;
    virtual bool isStub() const;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const unsigned char* getData() const;
    size_t getLength() const;
};

#endif
