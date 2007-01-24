#ifndef _HSREFCOUNT_H
#define _HSREFCOUNT_H

class hsRefCnt {
protected:
    int refCount;

public:
    hsRefCnt();
    virtual ~hsRefCnt();

    virtual int RefCnt();
    virtual int UnRef();
    virtual void Ref();
};

#endif

