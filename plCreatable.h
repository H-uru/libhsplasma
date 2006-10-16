#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "CoreLib/hsStream.h"

class plCreatable {
public:
    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

