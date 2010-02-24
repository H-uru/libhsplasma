#ifndef _PNVAULTNODE_H
#define _PNVAULTNODE_H

#include "Vault/plVaultNode.h"
#include "Sys/plUnifiedTime.h"
#include "Sys/plUuid.h"

DllClass pnVaultNode {
public:
    enum {
        kNodeIdx        = (1<<0),
        kCreateTime     = (1<<1),
        kModifyTime     = (1<<2),
        kCreateAgeName  = (1<<3),
        kCreateAgeUuid  = (1<<4),
        kCreatorUuid    = (1<<5),
        kCreatorIdx     = (1<<6),
        kNodeType       = (1<<7),
        kInt32_1        = (1<<8),
        kInt32_2        = (1<<9),
        kInt32_3        = (1<<10),
        kInt32_4        = (1<<11),
        kUint32_1       = (1<<12),
        kUint32_2       = (1<<13),
        kUint32_3       = (1<<14),
        kUint32_4       = (1<<15),
        kUuid_1         = (1<<16),
        kUuid_2         = (1<<17),
        kUuid_3         = (1<<18),
        kUuid_4         = (1<<19),
        kString64_1     = (1<<20),
        kString64_2     = (1<<21),
        kString64_3     = (1<<22),
        kString64_4     = (1<<23),
        kString64_5     = (1<<24),
        kString64_6     = (1<<25),
        kIString64_1    = (1<<26),
        kIString64_2    = (1<<27),
        kText_1         = (1<<28),
        kText_2         = (1<<29),
        kBlob_1         = (1<<30),
        kBlob_2         = (1<<31),
    };

protected:
    hsUint64 fFieldMask;

    hsInt32 fNodeIdx;
    hsUint32 fCreateTime, fModifyTime;
    plString fCreateAgeName;
    plUuid fCreateAgeUuid, fCreatorUuid;
    hsInt32 fCreatorIdx, fNodeType;
    hsInt32 fInt32[4];
    hsUint32 fUint32[4];
    plUuid fUuid[4];
    plString fString64[6], fIString64[2];
    plString fText[2];
    plVaultBlob fBlob[2];

public:
    pnVaultNode();
    pnVaultNode(const pnVaultNode& init);
    void copy(const pnVaultNode& init);
    void clear();

    bool isValid() const;
    bool hasField(hsUint64 field) const;
    void clearField(hsUint64 field);
    void setTimeNow();
    void setModifyNow();

    size_t calcSize() const;
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
};

DllStruct pnVaultNodeRef {
    enum { Stride = 13 };

    hsInt32 fParent, fChild, fOwner;
    hsUbyte fSeen;

    void read(const unsigned char* buffer);
    void write(const unsigned char* buffer);
};

#endif
