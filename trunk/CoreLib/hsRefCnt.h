#ifndef _HSREFCOUNT_H
#define _HSREFCOUNT_H

#include "PlasmaDefs.h"

DllClass hsRefCnt {
protected:
    int refCount;

public:
    hsRefCnt();
    virtual ~hsRefCnt();

    virtual int RefCnt();
    virtual int UnRef();
    virtual void Ref();
};

/*
class plRefFlags {
public:
    enum Type { kNone };
};
*/

#endif
