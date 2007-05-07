#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/pdUnifiedTypeMap.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

class plCreatable : public hsRefCnt {
public:
    plCreatable();
    virtual ~plCreatable();

    virtual short ClassIndex() = 0;
    virtual short ClassIndex(PlasmaVer ver) = 0;
    const char* ClassName();

    virtual void read(hsStream* S) = 0;
    virtual void write(hsStream* S) = 0;
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc) = 0;
};

#endif
