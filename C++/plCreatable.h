#ifndef _PLCREATABLE_H
#define _PLCREATABLE_H

#include "hsRefCount.h"
#include "CoreLib/hsStream.h"

class plCreatable : public hsRefCount {
protected:
    virtual const char* getTypeName();
    virtual const int getTypeNum();

public:
    plCreatable();
    virtual ~plCreatable();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

