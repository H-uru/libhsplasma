/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PNVAULTNODE_H
#define _PNVAULTNODE_H

#include "Vault/plVaultNode.h"
#include "Sys/plUnifiedTime.h"
#include "Sys/plUuid.h"
#include "Protocol.h"

class PLASMANET_DLL pnVaultNode {
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
    uint64_t fFieldMask;
    uint64_t fDirtyMask;
    size_t fCachedSize, fDirtySize;

    int32_t fNodeIdx;
    uint32_t fCreateTime, fModifyTime;
    ST::string fCreateAgeName;
    plUuid fCreateAgeUuid, fCreatorUuid;
    int32_t fCreatorIdx, fNodeType;
    int32_t fInt32[4];
    uint32_t fUint32[4];
    plUuid fUuid[4];
    ST::string fString64[6];
    ST::string fIString64[2];
    ST::string fText[2];
    plVaultBlob fBlob[2];

public:
    pnVaultNode() : fFieldMask(0), fDirtyMask(0), fCachedSize(0), fDirtySize(0),
                    fNodeIdx(0), fNodeType(0) { }
    pnVaultNode(const pnVaultNode& init) { copy(init); }
    void copy(const pnVaultNode& init);
    void clear();

    bool isValid() const;
    bool isDirty() const { return fDirtyMask != 0; }
    bool hasField(size_t field) const { return (fFieldMask & (1ULL<<field)) != 0; }
    bool hasDirty(size_t field) const { return (fDirtyMask & (1ULL<<field)) != 0; }
    void allDirty();
    void allClean();
    void setTimeNow();
    void setModifyNow();

    size_t bufferSize() const { return fDirtySize + sizeof(uint64_t); }
    void read(const unsigned char* buffer, size_t size);
    void write(unsigned char* buffer, size_t size) const;

    uint32_t getNodeIdx() const;
    uint32_t getCreateTime() const;
    uint32_t getModifyTime() const;
    ST::string getCreateAgeName() const;
    plUuid getCreateAgeUuid() const;
    plUuid getCreatorUuid() const;
    uint32_t getCreatorIdx() const;
    uint32_t getNodeType() const;
    int32_t getInt32(size_t which) const;
    uint32_t getUint32(size_t which) const;
    plUuid getUuid(size_t which) const;
    ST::string getString64(size_t which) const;
    ST::string getIString64(size_t which) const;
    ST::string getText(size_t which) const;
    plVaultBlob getBlob(size_t which) const;

    void setNodeIdx(uint32_t idx);
    void setCreateTime(uint32_t createTime);
    void setModifyTime(uint32_t modTime);
    void setCreateAgeName(const ST::string& name);
    void setCreateAgeUuid(const plUuid& uuid);
    void setCreatorUuid(const plUuid& uuid);
    void setCreatorIdx(uint32_t idx);
    void setNodeType(uint32_t type);
    void setInt32(size_t which, int32_t value);
    void setUint32(size_t which, uint32_t value);
    void setUuid(size_t which, const plUuid& value);
    void setString64(size_t which, const ST::string& value);
    void setIString64(size_t which, const ST::string& value);
    void setText(size_t which, const ST::string& value);
    void setBlob(size_t which, const plVaultBlob& value);

private:
    void ISetField(size_t which, size_t size);
    void IClearField(size_t which, size_t size);
};

struct PLASMANET_DLL pnVaultNodeRef {
    enum { Stride = 13 };

    uint32_t fParent, fChild, fOwner;
    uint8_t fSeen;

    void read(const unsigned char* buffer);
    void write(unsigned char* buffer);
    bool operator==(const pnVaultNodeRef& ref);
};

#endif
