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

    virtual short ClassIndex() const =0;
    short ClassIndex(PlasmaVer ver) const;
    virtual const char* ClassName() const;
    virtual bool ClassInstance(short hClass) const;
    virtual bool isStub() const;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc) =0;
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
    short getClassIdx() const;
    const unsigned char* getData() const;
    size_t getLength() const;
};

#endif
