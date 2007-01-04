#ifndef _HSREFCOUNT_H
#define _HSREFCOUNT_H

class hsRefCount {
protected:
    static int refCount;

public:
    hsRefCount();
    ~hsRefCount();

    static int getRefCount();
    static int RemoveRef();
    static void AddRef();
};

#endif

