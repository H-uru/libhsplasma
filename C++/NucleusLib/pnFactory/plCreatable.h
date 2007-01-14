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
    ~plCreatable();

    short ClassIndex();
    
    PlasmaVer getVersion();
    void setVersion(PlasmaVer pv, bool mutate = false);

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

