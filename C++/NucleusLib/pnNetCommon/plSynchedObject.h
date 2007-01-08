#ifndef _PLSYNCHEDOBJECT_H
#define _PLSYNCHEDOBJECT_H

#include "../pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../DynLib/plString.h"

class plSynchedObject : public hsKeyedObject {
protected:
    int flags;
    hsTArray<plString> SDLKeys;
    hsTArray<plString> SDLKeys2;

public:
    plSynchedObject();
    ~plSynchedObject();

    void read(hsStream * S);
    void write(hsStream * S);
};

#endif

