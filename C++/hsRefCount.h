#ifndef _HSREFCOUNT_H
#define _HSREFCOUNT_H

class hsRefCount {
protected:
    int refCount;

public:
    hsRefCount();
    ~hsRefCount();

    int getRefCount();
    int UnRef();
    void Ref();
};

#endif

