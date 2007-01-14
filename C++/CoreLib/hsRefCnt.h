#ifndef _HSREFCOUNT_H
#define _HSREFCOUNT_H

class hsRefCnt {
protected:
    int refCount;

public:
    hsRefCnt();
    ~hsRefCnt();

    int RefCnt();
    int UnRef();
    void Ref();
};

#endif

