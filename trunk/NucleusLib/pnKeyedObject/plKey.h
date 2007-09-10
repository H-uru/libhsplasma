#ifndef _PLKEY_H
#define _PLKEY_H

#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsRefCnt.h"
#include "plUoid.h"

DllClass plKeyData {
protected:
    plUoid fUoid;
    class hsKeyedObject* fObjPtr;
    
    uint32 fFileOff, fObjSize;
    uint32 fRefCnt;

public:
    plKeyData();
    plKeyData(plKeyData* init);
    ~plKeyData();

private:
    friend class plKey;
    uint32 RefCnt() const;
    uint32 Ref();
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
    uint32 getID() const;
    void setID(uint32 id);
    uint32 getFileOff() const;
    void setFileOff(uint32 off);
    uint32 getObjSize() const;
    void setObjSize(uint32 size);
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
