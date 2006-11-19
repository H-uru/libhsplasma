#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "../../CoreLib/hsBitVector.h"
#include "../pnNetCommon/plSynchedObject.h"

class plObjInterface : public plSynchedObject {
private:
    plKey * SceneObj;
    hsBitVector ifFlags;

public:
    plObjInterface();
    ~plObjInterface();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

