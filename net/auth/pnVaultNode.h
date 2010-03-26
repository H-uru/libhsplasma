#ifndef _PNVAULTNODE_H
#define _PNVAULTNODE_H

#include "Vault/plVaultNode.h"
#include "Sys/plUnifiedTime.h"
#include "Sys/plUuid.h"
#include "Protocol.h"

DllClass pnVaultNode {
public:
    enum {
        kNodeIdx, kCreateTime, kModifyTime, kCreateAgeName, kCreateAgeUuid,
        kCreatorUuid, kCreatorIdx, kNodeType, kInt32_1, kInt32_2, kInt32_3,
        kInt32_4, kUint32_1, kUint32_2, kUint32_3, kUint32_4, kUuid_1, kUuid_2,
        kUuid_3, kUuid_4, kString64_1, kString64_2, kString64_3, kString64_4,
        kString64_5, kString64_6, kIString64_1, kIString64_2, kText_1, kText_2,
        kBlob_1, kBlob_2, kNumFields,
    };

    enum {
        /* For those who can't handle starting at 0 ;)  */
        k_1, k_2, k_3, k_4, k_5, k_6
    };

protected:
    hsUint64 fFieldMask;
    hsUint64 fDirtyMask;
    size_t fCachedSize, fDirtySize;

    hsInt32 fNodeIdx;
    hsUint32 fCreateTime, fModifyTime;
    NCchar_t* fCreateAgeName;
    plUuid fCreateAgeUuid, fCreatorUuid;
    hsInt32 fCreatorIdx, fNodeType;
    hsInt32 fInt32[4];
    hsUint32 fUint32[4];
    plUuid fUuid[4];
    NCchar_t* fString64[6];
    NCchar_t* fIString64[2];
    NCchar_t* fText[2];
    plVaultBlob fBlob[2];

public:
    pnVaultNode();
    pnVaultNode(const pnVaultNode& init);
    ~pnVaultNode();
    void copy(const pnVaultNode& init);
    void clear();

    bool isValid() const;
    bool isDirty() const;
    bool hasField(size_t field) const;
    bool hasDirty(size_t field) const;
    void allDirty();
    void allClean();
    void setTimeNow();
    void setModifyNow();

    size_t bufferSize() const;
    void read(const unsigned char* buffer, size_t size);
    void write(unsigned char* buffer, size_t size) const;

    hsUint32 getNodeIdx() const;
    hsUint32 getCreateTime() const;
    hsUint32 getModifyTime() const;
    plString getCreateAgeName() const;
    plUuid getCreateAgeUuid() const;
    plUuid getCreatorUuid() const;
    hsUint32 getCreatorIdx() const;
    hsUint32 getNodeType() const;
    hsInt32 getInt32(size_t which) const;
    hsUint32 getUint32(size_t which) const;
    plUuid getUuid(size_t which) const;
    plString getString64(size_t which) const;
    plString getIString64(size_t which) const;
    plString getText(size_t which) const;
    plVaultBlob getBlob(size_t which) const;

    void setNodeIdx(hsUint32 idx);
    void setCreateTime(hsUint32 createTime);
    void setModifyTime(hsUint32 modTime);
    void setCreateAgeName(const plString& name);
    void setCreateAgeUuid(const plUuid& uuid);
    void setCreatorUuid(const plUuid& uuid);
    void setCreatorIdx(hsUint32 idx);
    void setNodeType(hsUint32 type);
    void setInt32(size_t which, hsInt32 value);
    void setUInt32(size_t which, hsUint32 value);
    void setUuid(size_t which, const plUuid& value);
    void setString64(size_t which, const plString& value);
    void setIString64(size_t which, const plString& value);
    void setText(size_t which, const plString& value);
    void setBlob(size_t which, const plVaultBlob& value);

private:
    void ISetField(size_t which, size_t size);
    void IClearField(size_t which, size_t size);
};

DllStruct pnVaultNodeRef {
    enum { Stride = 13 };

    hsUint32 fParent, fChild, fOwner;
    hsUbyte fSeen;

    void read(const unsigned char* buffer);
    void write(const unsigned char* buffer);
    bool operator==(const pnVaultNodeRef& ref);
};

#endif
