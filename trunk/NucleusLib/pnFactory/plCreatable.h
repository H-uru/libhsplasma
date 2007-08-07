#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/pdUnifiedTypeMap.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

#define DECLARE_CREATABLE(classname) \
    virtual short ClassIndex(); \
    virtual bool ClassInstance(short hClass); \
    static classname* Convert(plCreatable* pCre);

#define IMPLEMENT_CREATABLE(classname, classid, parentclass) \
    short classname::ClassIndex() { return classid; } \
    bool classname::ClassInstance(short hClass) { \
        if (hClass == classid) return true; \
        return parentclass::ClassInstance(hClass); \
    } \
    classname* classname::Convert(plCreatable* pCre) { \
        if (pCre != NULL && pCre->ClassInstance(classid)) \
            return (classname*)pCre; \
        return NULL; \
    }


DllClass plCreatable : public hsRefCnt {
public:
    plCreatable();
    virtual ~plCreatable();

    virtual short ClassIndex() = 0;
    short ClassIndex(PlasmaVer ver);
    const char* ClassName();
    virtual bool ClassInstance(short hClass);

    virtual void read(hsStream* S) = 0;
    virtual void write(hsStream* S) = 0;
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
