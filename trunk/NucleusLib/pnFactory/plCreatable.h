#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PlasmaVersions.h"

class plCreatable : public hsRefCnt {
protected:
    PlasmaVer ver;

public:
    plCreatable(PlasmaVer pv = pvUnknown);
    virtual ~plCreatable();

    virtual short ClassIndex() = 0;
    
    PlasmaVer getVer();
    virtual void setVer(PlasmaVer pv, bool mutate = false);

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

