#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "hsRefCount.h"
#include "CoreLib/hsStream.h"

class plCreatable : public hsRefCount {
public:
    plCreatable();
    ~plCreatable();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

