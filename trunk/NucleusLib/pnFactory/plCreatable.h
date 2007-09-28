#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/pdUnifiedTypeMap.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

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


DllClass plCreatable /*: public hsRefCnt*/ {
public:
    plCreatable();
    virtual ~plCreatable();

    virtual short ClassIndex() const =0;
    short ClassIndex(PlasmaVer ver) const;
    const char* ClassName() const;
    virtual bool ClassInstance(short hClass) const;

    virtual void read(hsStream* S, class plResManager* mgr);
    virtual void write(hsStream* S, class plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
