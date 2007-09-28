#ifndef _PLKEY_H
#define _PLKEY_H

#include "../../CoreLib/hsStream.h"
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

private:
    friend class plKey;
    hsUint32 RefCnt() const;
    hsUint32 Ref();
    void UnRef();

public:
    bool operator==(plKeyData& other) const;
    plString toString() const;
    
    void read(hsStream* S);
    void write(hsStream* S);
    void readUoid(hsStream* S);
    void writeUoid(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    plUoid& getUoid();
    class hsKeyedObject* getObj();
    void setObj(class hsKeyedObject* obj);
    short getType() const;
    const PageID& getPageID() const;
    const plString& getName() const;
    hsUint32 getID() const;
    void setID(hsUint32 id);
    hsUint32 getFileOff() const;
    void setFileOff(hsUint32 off);
    hsUint32 getObjSize() const;
    void setObjSize(hsUint32 size);
};

DllClass plKey {
protected:
    plKeyData* fKeyData;

public:
    plKey();
    plKey(const plKey& init);
    plKey(plKeyData* init);
    ~plKey();

    plKeyData& operator*() const;
    plKeyData* operator->() const;
    operator plKeyData*() const;

    plKey& operator=(const plKey& other);
    plKey& operator=(plKeyData* other);
    bool operator==(const plKey& other) const;
    bool operator==(const plKeyData* other) const;
    bool operator!=(const plKey& other) const;
    bool operator!=(const plKeyData* other) const;
    bool operator<(const plKey& other) const;

    bool Exists() const;
};

#endif
