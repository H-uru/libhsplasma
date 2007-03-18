#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

class plCreatable : public hsRefCnt {
protected:
    PlasmaVer ver;

public:
    plCreatable(PlasmaVer pv = pvUnknown);
    virtual ~plCreatable();

    virtual short ClassIndex() = 0;
    
    PlasmaVer getVer();
    virtual void setVer(PlasmaVer pv, bool mutate = false);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    
    //virtual void prcRead();
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

