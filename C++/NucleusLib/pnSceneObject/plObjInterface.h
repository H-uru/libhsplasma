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
    ~plObjInterface();

    bool msgReceive(plMessage * msg);

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

