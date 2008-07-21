#ifndef _PLKEY_H
#define _PLKEY_H

#include "plUoid.h"

DllClass plKeyData {
protected:
    plUoid fUoid;
    class hsKeyedObject* fObjPtr;
    
    hsUint32 fFileOff, fObjSize;
    hsUint32 fRefCnt;

public:
    plKeyData();
    plKeyData(plKeyData* init);
    ~plKeyData();
    void dispose();

private:
    hsUint32 RefCnt() const;
    hsUint32 Ref();
    void UnRef();
    friend class plKey;

public:
    bool operator==(plKeyData& other) const;
    plString toString() const;
    
    void read(hsStream* S);
    void write(hsStream* S);
    void readUoid(hsStream* S);
    void writeUoid(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    static plKeyData* PrcParse(const pfPrcTag* tag);

    plUoid& getUoid();
    class hsKeyedObject* getObj();
    void setObj(class hsKeyedObject* obj);
    
    short getType() const;
    const plString& getName() const;
    const plLocation& getLocation() const;
    const plLoadMask& getLoadMask() const;
    hsUint32 getID() const;
    hsUint32 getFileOff() const;
    hsUint32 getObjSize() const;

    void setType(short type);
    void setName(const plString& name);
    void setLocation(const plLocation& loc);
    void setLoadMask(const plLoadMask& mask);
    void setID(hsUint32 id);
    void setFileOff(hsUint32 off);
    void setObjSize(hsUint32 size);
};

DllClass plWeakKey {
protected:
    plKeyData* fKeyData;

public:
    plWeakKey();
    plWeakKey(const plWeakKey& init);
    plWeakKey(plKeyData* init);
    virtual ~plWeakKey();

    plKeyData& operator*() const;
    plKeyData* operator->() const;
    operator plKeyData*() const;

    virtual plWeakKey& operator=(const plWeakKey& other);
    virtual plWeakKey& operator=(plKeyData* other);
    bool operator==(const plWeakKey& other) const;
    bool operator==(const plKeyData* other) const;
    bool operator!=(const plWeakKey& other) const;
    bool operator!=(const plKeyData* other) const;
    bool operator<(const plWeakKey& other) const;

    bool Exists() const;
    bool isLoaded() const;
};

DllClass plKey : public plWeakKey {
public:
    plKey();
    plKey(const plWeakKey& init);
    plKey(const plKey& init);
    plKey(plKeyData* init);
    virtual ~plKey();

    virtual plKey& operator=(const plWeakKey& other);
    virtual plKey& operator=(const plKey& other);
    virtual plKey& operator=(plKeyData* other);
};

#endif
