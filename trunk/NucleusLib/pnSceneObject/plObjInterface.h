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
    plObjInterface(PlasmaVer pv = pvUnknown);
    virtual ~plObjInterface();

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

