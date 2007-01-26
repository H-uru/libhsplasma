#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "../../CoreLib/hsBitVector.h"
#include "../pnNetCommon/plSynchedObject.h"
#include "../pnMessage/plMessage.h"

class plObjInterface : public plSynchedObject {
private:
    plKey * Owner;
    hsBitVector Properties;

public:
    plObjInterface(PlasmaVer pv = pvUnknown);
    virtual ~plObjInterface();

    virtual short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

