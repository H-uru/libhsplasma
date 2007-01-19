#ifndef _PLSYNCHEDOBJECT_H
#define _PLSYNCHEDOBJECT_H

#include "../pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsTArray.hpp"

class plSynchedObject : public hsKeyedObject {
protected:
    int flags;
    hsTArray<char*> SDLKeys;
    hsTArray<char*> SDLKeys2;

public:
    plSynchedObject(PlasmaVer pv = pvUnknown);
    virtual ~plSynchedObject();

    virtual void read(hsStream * S);
    virtual void write(hsStream * S);
};

#endif

