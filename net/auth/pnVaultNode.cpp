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

#include "pnVaultNode.h"
#include "pnNetMsg.h"
#include "Debug/plDebug.h"
#include <cstring>

/* pnVaultNode */
void pnVaultNode::copy(const pnVaultNode& init) {
    fFieldMask = init.fFieldMask;
    fDirtyMask = init.fDirtyMask;
    fCachedSize = init.fCachedSize;
    fDirtySize = init.fDirtySize;
    fNodeIdx = init.fNodeIdx;
    fCreateTime = init.fCreateTime;
    fModifyTime = init.fModifyTime;
    fCreateAgeName = init.fCreateAgeName;
    fCreateAgeUuid = init.fCreateAgeUuid;
    fCreatorUuid = init.fCreatorUuid;
    fCreatorIdx = init.fCreatorIdx;
    fNodeType = init.fNodeType;
    fInt32[0] = init.fInt32[0];
    fInt32[1] = init.fInt32[1];
    fInt32[2] = init.fInt32[2];
    fInt32[3] = init.fInt32[3];
    fUint32[0] = init.fUint32[0];
    fUint32[1] = init.fUint32[1];
    fUint32[2] = init.fUint32[2];
    fUint32[3] = init.fUint32[3];
    fUuid[0] = init.fUuid[0];
    fUuid[1] = init.fUuid[1];
    fUuid[2] = init.fUuid[2];
    fUuid[3] = init.fUuid[3];
    fString64[0] = init.fString64[0];
    fString64[1] = init.fString64[1];
    fString64[2] = init.fString64[2];
    fString64[3] = init.fString64[3];
    fString64[4] = init.fString64[4];
    fString64[5] = init.fString64[5];
    fIString64[0] = init.fIString64[0];
    fIString64[1] = init.fIString64[1];
    fText[0] = init.fText[0];
    fText[1] = init.fText[1];
    fBlob[0] = init.fBlob[0];
    fBlob[1] = init.fBlob[1];
}

void pnVaultNode::clear() {
    fFieldMask = 0;
    fDirtyMask = 0;
    fCachedSize = 0;
}

bool pnVaultNode::isValid() const {
    return (fFieldMask & (1<<kNodeIdx)) != 0 && fNodeIdx != 0;
}

void pnVaultNode::allDirty() {
    fDirtyMask = fFieldMask;
    fDirtySize = fCachedSize;
}

void pnVaultNode::allClean() {
    fDirtyMask = 0;
    fDirtySize = 0;
}

void pnVaultNode::setTimeNow() {
    setCreateTime((uint32_t)time(NULL));
    setModifyTime(fCreateTime);
}

void pnVaultNode::setModifyNow() {
    setModifyTime((uint32_t)time(NULL));
}

static uint64_t readU64(const unsigned char*& buffer, size_t& size) {
    uint64_t v = NCReadBuffer<uint64_t>(buffer);
    size -= sizeof(uint64_t);
    return v;
}

static uint32_t readU32(const unsigned char*& buffer, size_t& size) {
    uint32_t v = NCReadBuffer<uint32_t>(buffer);
    size -= sizeof(uint32_t);
    return v;
}

static int32_t readS32(const unsigned char*& buffer, size_t& size) {
    int32_t v = NCReadBuffer<int32_t>(buffer);
    size -= sizeof(int32_t);
    return v;
}

static plUuid readUuid(const unsigned char*& buffer, size_t& size) {
    plUuid v = NCReadBuffer<plUuid>(buffer);
    size -= sizeof(plUuid);
    return v;
}

static ST::string readString(const unsigned char*& buffer, size_t& size) {
    size_t len = readU32(buffer, size);
    ST::utf16_buffer u16buf;
    u16buf.allocate(len / sizeof(char16_t));
    memcpy(u16buf.data(), buffer, len);
    ST::string v = ST::string::from_utf16(u16buf.data(), (len-1) / sizeof(char16_t));
    buffer += len;
    size -= len;
    return v;
}

void pnVaultNode::read(const unsigned char* buffer, size_t size) {
    if (size < sizeof(uint64_t)) {
        plDebug::Error("Invalid node data");
        return;
    }
    fDirtyMask = 0;
    fDirtySize = 0;
    fFieldMask = readU64(buffer, size);
    fCachedSize = size;

    for (size_t bit=0; bit<kNumFields; bit++) {
        if ((fFieldMask & (1ULL<<bit)) == 0)
            continue;

        switch (bit) {
        case kNodeIdx:
            fNodeIdx = readU32(buffer, size);
            break;
        case kCreateTime:
            fCreateTime = readU32(buffer, size);
            break;
        case kModifyTime:
            fModifyTime = readU32(buffer, size);
            break;
        case kCreateAgeName:
            fCreateAgeName = readString(buffer, size);
            break;
        case kCreateAgeUuid:
            fCreateAgeUuid = readUuid(buffer, size);
            break;
        case kCreatorUuid:
            fCreatorUuid = readUuid(buffer, size);
            break;
        case kCreatorIdx:
            fCreatorIdx = readU32(buffer, size);
            break;
        case kNodeType:
            fNodeType = readU32(buffer, size);
            break;
        case kInt32_1:
        case kInt32_2:
        case kInt32_3:
        case kInt32_4:
            fInt32[bit - kInt32_1] = readS32(buffer, size);
            break;
        case kUint32_1:
        case kUint32_2:
        case kUint32_3:
        case kUint32_4:
            fUint32[bit - kUint32_1] = readU32(buffer, size);
            break;
        case kUuid_1:
        case kUuid_2:
        case kUuid_3:
        case kUuid_4:
            fUuid[bit - kUuid_1] = readUuid(buffer, size);
            break;
        case kString64_1:
        case kString64_2:
        case kString64_3:
        case kString64_4:
        case kString64_5:
        case kString64_6:
            fString64[bit - kString64_1] = readString(buffer, size);
            break;
        case kIString64_1:
        case kIString64_2:
            fIString64[bit - kIString64_1] = readString(buffer, size);
            break;
        case kText_1:
        case kText_2:
            fText[bit - kText_1] = readString(buffer, size);
            break;
        case kBlob_1:
        case kBlob_2:
            {
                size_t len = readU32(buffer, size);
                fBlob[bit - kBlob_1].setData(len, buffer);
                buffer += len;
                size -= len;
            }
            break;
        }
    }

    if (size != 0)
        plDebug::Warning("Incomplete read of node {}", fNodeIdx);
}

static void writeU64(uint64_t v, unsigned char*& buffer, size_t& size) {
    NCWriteBuffer<uint64_t>(buffer, v);
    size -= sizeof(uint64_t);
}

static void writeU32(uint32_t v, unsigned char*& buffer, size_t& size) {
    NCWriteBuffer<uint32_t>(buffer, v);
    size -= sizeof(uint32_t);
}

static void writeS32(int32_t v, unsigned char*& buffer, size_t& size) {
    NCWriteBuffer<int32_t>(buffer, v);
    size -= sizeof(int32_t);
}

static void writeUuid(const plUuid& v, unsigned char*& buffer, size_t& size) {
    NCWriteBuffer<plUuid>(buffer, v);
    size -= sizeof(plUuid);
}

static void writeString(const ST::string& v, unsigned char*& buffer, size_t& size) {
    ST::utf16_buffer ws = v.to_utf16();
    size_t len = (ws.size() + 1) * sizeof(char16_t);
    writeU32(len, buffer, size);
    memcpy(buffer, ws.data(), len);  // Includes the '\0'
    buffer += len;
    size -= len;
}

void pnVaultNode::write(unsigned char* buffer, size_t size) const {
    if (size < sizeof(uint64_t)) {
        plDebug::Error("Invalid node buffer");
        return;
    }
    writeU64(fDirtyMask, buffer, size);

    for (size_t bit=0; bit<kNumFields; bit++) {
        if ((fDirtyMask & (1ULL<<bit)) == 0)
            continue;

        switch (bit) {
        case kNodeIdx:
            writeU32(fNodeIdx, buffer, size);
            break;
        case kCreateTime:
            writeU32(fCreateTime, buffer, size);
            break;
        case kModifyTime:
            writeU32(fModifyTime, buffer, size);
            break;
        case kCreateAgeName:
            writeString(fCreateAgeName, buffer, size);
            break;
        case kCreateAgeUuid:
            writeUuid(fCreateAgeUuid, buffer, size);
            break;
        case kCreatorUuid:
            writeUuid(fCreatorUuid, buffer, size);
            break;
        case kCreatorIdx:
            writeU32(fCreatorIdx, buffer, size);
            break;
        case kNodeType:
            writeU32(fNodeType, buffer, size);
            break;
        case kInt32_1:
        case kInt32_2:
        case kInt32_3:
        case kInt32_4:
            writeS32(fInt32[bit - kInt32_1], buffer, size);
            break;
        case kUint32_1:
        case kUint32_2:
        case kUint32_3:
        case kUint32_4:
            writeU32(fUint32[bit - kUint32_1], buffer, size);
            break;
        case kUuid_1:
        case kUuid_2:
        case kUuid_3:
        case kUuid_4:
            writeUuid(fUuid[bit - kUuid_1], buffer, size);
            break;
        case kString64_1:
        case kString64_2:
        case kString64_3:
        case kString64_4:
        case kString64_5:
        case kString64_6:
            writeString(fString64[bit - kString64_1], buffer, size);
            break;
        case kIString64_1:
        case kIString64_2:
            writeString(fIString64[bit - kIString64_1], buffer, size);
            break;
        case kText_1:
        case kText_2:
            writeString(fText[bit - kText_1], buffer, size);
            break;
        case kBlob_1:
        case kBlob_2:
            writeU32(fBlob[bit - kBlob_1].getSize(), buffer, size);
            memcpy(buffer, fBlob[bit - kBlob_1].getData(), fBlob[bit - kBlob_1].getSize());
            buffer += fBlob[bit - kBlob_1].getSize();
            size -= fBlob[bit - kBlob_1].getSize();
            break;
        }
    }

    if (size != 0)
        plDebug::Warning("Node {} is truncated", fNodeIdx);
}

uint32_t pnVaultNode::getNodeIdx() const
{
    return (fFieldMask & (1<<kNodeIdx)) != 0 ? fNodeIdx : 0;
}

uint32_t pnVaultNode::getCreateTime() const
{
    return (fFieldMask & (1<<kCreateTime)) != 0 ? fCreateTime : 0;
}

uint32_t pnVaultNode::getModifyTime() const
{
    return (fFieldMask & (1<<kModifyTime)) != 0 ? fModifyTime : 0;
}

ST::string pnVaultNode::getCreateAgeName() const
{
    return (fFieldMask & (1<<kCreateAgeName)) != 0
           ? fCreateAgeName : ST::null;
}

plUuid pnVaultNode::getCreateAgeUuid() const
{
    return (fFieldMask & (1<<kCreateAgeUuid)) != 0 ? fCreateAgeUuid : plUuid();
}

plUuid pnVaultNode::getCreatorUuid() const
{
    return (fFieldMask & (1<<kCreatorUuid)) != 0 ? fCreatorUuid : plUuid();
}

uint32_t pnVaultNode::getCreatorIdx() const
{
    return (fFieldMask & (1<<kCreatorIdx)) != 0 ? fCreatorIdx : 0;
}

uint32_t pnVaultNode::getNodeType() const
{
    return (fFieldMask & (1<<kNodeType)) != 0 ? fNodeType : 0;
}

int32_t pnVaultNode::getInt32(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kInt32_1) << which)) != 0
           ? fInt32[which] : 0;
}

uint32_t pnVaultNode::getUint32(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kUint32_1) << which)) != 0
           ? fUint32[which] : 0;
}

plUuid pnVaultNode::getUuid(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kUuid_1) << which)) != 0
           ? fUuid[which] : plUuid();
}

ST::string pnVaultNode::getString64(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kString64_1) << which)) != 0
           ? fString64[which] : ST::null;
}

ST::string pnVaultNode::getIString64(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kIString64_1) << which)) != 0
           ? fIString64[which] : ST::null;
}

ST::string pnVaultNode::getText(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kText_1) << which)) != 0
           ? fText[which] : ST::null;
}

plVaultBlob pnVaultNode::getBlob(size_t which) const
{
    return (fFieldMask & (uint64_t)((1<<kBlob_1) << which)) != 0
           ? fBlob[which] : plVaultBlob();
}

void pnVaultNode::ISetField(size_t which, size_t size)
{
    if (!hasField(which))
        fCachedSize += size;
    if (!hasDirty(which))
        fDirtySize += size;
    fFieldMask |= (1ULL<<which);
    fDirtyMask |= (1ULL<<which);
}

void pnVaultNode::IClearField(size_t which, size_t size)
{
    if (hasField(which))
        fCachedSize -= size;
    if (hasDirty(which))
        fDirtySize -= size;
    fFieldMask &= ~(1<<which);
    fDirtyMask &= ~(1<<which);
}


void pnVaultNode::setNodeIdx(uint32_t idx)
{
    fNodeIdx = idx;
    ISetField(kNodeIdx, sizeof(uint32_t));
}

void pnVaultNode::setCreateTime(uint32_t createTime)
{
    fCreateTime = createTime;
    ISetField(kCreateTime, sizeof(uint32_t));
}

void pnVaultNode::setModifyTime(uint32_t modTime)
{
    fModifyTime = modTime;
    ISetField(kModifyTime, sizeof(uint32_t));
}

void pnVaultNode::setCreateAgeName(const ST::string& name)
{
    if (fCreateAgeName != NULL) {
        size_t oldLen = (fCreateAgeName.to_utf16().size() + 1) * sizeof(char16_t);
        IClearField(kCreateAgeName, oldLen + sizeof(uint32_t));
    }

    fCreateAgeName = name;
    size_t len = (fCreateAgeName.to_utf16().size() + 1) * sizeof(char16_t);
    ISetField(kCreateAgeName, len + sizeof(uint32_t));
}

void pnVaultNode::setCreateAgeUuid(const plUuid& uuid)
{
    fCreateAgeUuid = uuid;
    ISetField(kCreateAgeUuid, sizeof(plUuid));
}

void pnVaultNode::setCreatorUuid(const plUuid& uuid)
{
    fCreatorUuid = uuid;
    ISetField(kCreatorUuid, sizeof(plUuid));
}

void pnVaultNode::setCreatorIdx(uint32_t idx)
{
    fCreatorIdx = idx;
    ISetField(kCreatorIdx, sizeof(uint32_t));
}

void pnVaultNode::setNodeType(uint32_t type)
{
    fNodeType = type;
    ISetField(kNodeType, sizeof(uint32_t));
}

void pnVaultNode::setInt32(size_t which, int32_t value)
{
    fInt32[which] = value;
    ISetField(kInt32_1 + which, sizeof(int32_t));
}

void pnVaultNode::setUint32(size_t which, uint32_t value)
{
    fUint32[which] = value;
    ISetField(kUint32_1 + which, sizeof(uint32_t));
}

void pnVaultNode::setUuid(size_t which, const plUuid& value)
{
    fUuid[which] = value;
    ISetField(kUuid_1 + which, sizeof(plUuid));
}

void pnVaultNode::setString64(size_t which, const ST::string& value)
{
    if (fString64[which] != NULL) {
        size_t oldLen = (fString64[which].to_utf16().size() + 1) * sizeof(char16_t);
        IClearField(kString64_1 + which, oldLen + sizeof(uint32_t));
    }

    fString64[which] = value;
    size_t len = (fString64[which].to_utf16().size() + 1) * sizeof(char16_t);
    ISetField(kString64_1 + which, len + sizeof(uint32_t));
}

void pnVaultNode::setIString64(size_t which, const ST::string& value)
{
    if (fIString64[which] != NULL) {
        size_t oldLen = (fIString64[which].to_utf16().size() + 1) * sizeof(char16_t);
        IClearField(kIString64_1 + which, oldLen + sizeof(uint32_t));
    }

    fIString64[which] = value;
    size_t len = (fIString64[which].to_utf16().size() + 1) * sizeof(char16_t);
    ISetField(kIString64_1 + which, len + sizeof(uint32_t));
}

void pnVaultNode::setText(size_t which, const ST::string& value)
{
    if (fText[which] != NULL) {
        size_t oldLen = (fText[which].to_utf16().size() + 1) * sizeof(char16_t);
        IClearField(kText_1 + which, oldLen + sizeof(uint32_t));
    }

    fText[which] = value;
    size_t len = (fText[which].to_utf16().size() + 1) * sizeof(char16_t);
    ISetField(kText_1 + which, len + sizeof(uint32_t));
}

void pnVaultNode::setBlob(size_t which, const plVaultBlob& value)
{
    IClearField(kBlob_1 + which, fBlob[which].getSize() + sizeof(uint32_t));
    fBlob[which] = value;
    ISetField(kBlob_1 + which, fBlob[which].getSize() + sizeof(uint32_t));
}


/* pnVaultNodeRef */
void pnVaultNodeRef::read(const unsigned char* buffer)
{
    fParent = NCReadBuffer<uint32_t>(buffer);
    fChild  = NCReadBuffer<uint32_t>(buffer);
    fOwner  = NCReadBuffer<uint32_t>(buffer);
    fSeen   = NCReadBuffer<uint8_t>(buffer);
}

void pnVaultNodeRef::write(unsigned char* buffer)
{
    NCWriteBuffer<uint32_t>(buffer, fParent);
    NCWriteBuffer<uint32_t>(buffer, fChild);
    NCWriteBuffer<uint32_t>(buffer, fOwner);
    NCWriteBuffer<uint8_t>(buffer, fSeen);
}

bool pnVaultNodeRef::operator==(const pnVaultNodeRef& ref)
{
    return (ref.fParent == fParent) && (ref.fChild == fChild);
}
