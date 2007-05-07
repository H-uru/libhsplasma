#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "../../CoreLib/hsBitVector.h"
#include "../pnNetCommon/plSynchedObject.h"
#include "../pnMessage/plMessage.h"

class plObjInterface : public plSynchedObject {
public:
    plKey* Owner;
    hsBitVector Props;

public:
    plObjInterface();
    virtual ~plObjInterface();

    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

