#include "pnVaultNode.h"
#include "pnNetMsg.h"
#include "Debug/plDebug.h"
#include <cstring>

/* pnVaultNode */
pnVaultNode::pnVaultNode()
           : fFieldMask(0), fNodeIdx(0), fNodeType(0) { }

pnVaultNode::pnVaultNode(const pnVaultNode& init) {
    copy(init);
}

void pnVaultNode::copy(const pnVaultNode& init) {
    fFieldMask = init.fFieldMask;
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
}

bool pnVaultNode::isValid() const {
    return fNodeIdx != 0;
}

bool pnVaultNode::hasField(hsUint64 field) const {
    return (fFieldMask & field) != 0;
}

void pnVaultNode::clearField(hsUint64 field) {
    fFieldMask &= ~field;
}

void pnVaultNode::setTimeNow() {
    setCreateTime((hsUint32)time(NULL));
    setModifyTime(fCreateTime);
}

void pnVaultNode::setModifyNow() {
    setModifyTime((hsUint32)time(NULL));
}

size_t pnVaultNode::calcSize() {
    size_t size = sizeof(hsUint64); // Field Mask

    hsUint64 bit = 1;
    while (bit != 0 && bit <= fFieldMask) {
        switch (fFieldMask & bit) {
        case kNodeIdx:
        case kCreatorIdx:
        case kNodeType:
        case kInt32_1:
        case kInt32_2:
        case kInt32_3:
        case kInt32_4:
            size += sizeof(hsInt32);
            break;
        case kCreateTime:
        case kModifyTime:
        case kUint32_1:
        case kUint32_2:
        case kUint32_3:
        case kUint32_4:
            size += sizeof(hsUint32);
            break;
        case kCreateAgeUuid:
        case kCreatorUuid:
        case kUuid_1:
        case kUuid_2:
        case kUuid_3:
        case kUuid_4:
            size += sizeof(plUuid);
            break;
        case kCreateAgeName:
            size += sizeof(hsUint32) + ((fCreateAgeName.len() + 1) * sizeof(NCchar_t));
            break;
        case kString64_1:
            size += sizeof(hsUint32) + ((fString64[0].len() + 1) * sizeof(NCchar_t));
            break;
        case kString64_2:
            size += sizeof(hsUint32) + ((fString64[1].len() + 1) * sizeof(NCchar_t));
            break;
        case kString64_3:
            size += sizeof(hsUint32) + ((fString64[2].len() + 1) * sizeof(NCchar_t));
            break;
        case kString64_4:
            size += sizeof(hsUint32) + ((fString64[3].len() + 1) * sizeof(NCchar_t));
            break;
        case kString64_5:
            size += sizeof(hsUint32) + ((fString64[4].len() + 1) * sizeof(NCchar_t));
            break;
        case kString64_6:
            size += sizeof(hsUint32) + ((fString64[5].len() + 1) * sizeof(NCchar_t));
            break;
        case kIString64_1:
            size += sizeof(hsUint32) + ((fIString64[0].len() + 1) * sizeof(NCchar_t));
            break;
        case kIString64_2:
            size += sizeof(hsUint32) + ((fIString64[1].len() + 1) * sizeof(NCchar_t));
            break;
        case kText_1:
            size += sizeof(hsUint32) + ((fText[0].len() + 1) * sizeof(NCchar_t));
            break;
        case kText_2:
            size += sizeof(hsUint32) + ((fText[1].len() + 1) * sizeof(NCchar_t));
            break;
        case kBlob_1:
            size += sizeof(hsUint32) + fBlob[0].getSize();
            break;
        case kBlob_2:
            size += sizeof(hsUint32) + fBlob[1].getSize();
            break;
        }
        bit <<= 1;
    }
    return size;
}

void pnVaultNode::read(const unsigned char* buffer, size_t size) {
    if (size < sizeof(hsUint64)) {
        plDebug::Error("Invalid node data");
        return;
    }
    fFieldMask = *(hsUint64*)buffer;
    buffer += sizeof(hsUint64);
    size -= sizeof(hsUint64);

    hsUint64 bit = 1;
    while (bit != 0 && bit <= fFieldMask && ((int)size) > 0) {
        switch (fFieldMask & bit) {
        case kNodeIdx:
            fNodeIdx = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kCreateTime:
            fCreateTime = *(hsUint32*)buffer;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kModifyTime:
            fModifyTime = *(hsUint32*)buffer;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kCreateAgeName:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fCreateAgeName = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kCreateAgeUuid:
            fCreateAgeUuid = *(plUuid*)buffer;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kCreatorUuid:
            fCreatorUuid = *(plUuid*)buffer;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kCreatorIdx:
            fCreatorIdx = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kNodeType:
            fNodeType = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_1:
            fInt32[0] = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_2:
            fInt32[1] = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_3:
            fInt32[2] = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_4:
            fInt32[3] = *(hsInt32*)buffer;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kUint32_1:
            fUint32[0] = *(hsUint32*)buffer;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUint32_2:
            fUint32[1] = *(hsUint32*)buffer;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUint32_3:
            fUint32[2] = *(hsUint32*)buffer;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUint32_4:
            fUint32[3] = *(hsUint32*)buffer;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUuid_1:
            fUuid[0] = *(plUuid*)buffer;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kUuid_2:
            fUuid[1] = *(plUuid*)buffer;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kUuid_3:
            fUuid[2] = *(plUuid*)buffer;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kUuid_4:
            fUuid[3] = *(plUuid*)buffer;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kString64_1:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fString64[0] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kString64_2:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fString64[1] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kString64_3:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fString64[2] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kString64_4:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fString64[3] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kString64_5:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fString64[4] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kString64_6:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fString64[5] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kIString64_1:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fIString64[0] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kIString64_2:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fIString64[1] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kText_1:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fText[0] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kText_2:
            {
                size_t len = *(hsUint32*)buffer / sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fText[1] = NCstrToString((NCchar_t*)buffer);
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
            }
            break;
        case kBlob_1:
            {
                size_t len = *(hsUint32*)buffer;
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fBlob[0].setData(len, buffer);
                buffer += len;
                size -= len;
            }
            break;
        case kBlob_2:
            {
                size_t len = *(hsUint32*)buffer;
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                fBlob[1].setData(len, buffer);
                buffer += len;
                size -= len;
            }
            break;
        }
        bit <<= 1;
    }

    if (bit <= fFieldMask || size != 0)
        plDebug::Warning("Incomplete read of node %d", fNodeIdx);
}

void pnVaultNode::write(unsigned char* buffer, size_t size) {
    if (size < sizeof(hsUint64)) {
        plDebug::Error("Invalid node buffer");
        return;
    }
    *(hsUint64*)buffer = fFieldMask;
    buffer += sizeof(hsUint64);
    size -= sizeof(hsUint64);

    hsUint64 bit = 1;
    while (bit != 0 && bit <= fFieldMask && ((int)size) > 0) {
        switch (fFieldMask & bit) {
        case kNodeIdx:
            *(hsInt32*)buffer = fNodeIdx;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kCreateTime:
            *(hsUint32*)buffer = fCreateTime;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kModifyTime:
            *(hsUint32*)buffer = fModifyTime;
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kCreateAgeName:
            {
                NCchar_t* str = StringToNCstr(fCreateAgeName);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kCreateAgeUuid:
            *(plUuid*)buffer = fCreateAgeUuid;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kCreatorUuid:
            *(plUuid*)buffer = fCreatorUuid;
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kCreatorIdx:
            *(hsInt32*)buffer = fCreatorIdx;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kNodeType:
            *(hsInt32*)buffer = fNodeType;
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_1:
            *(hsInt32*)buffer = fInt32[0];
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_2:
            *(hsInt32*)buffer = fInt32[1];
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_3:
            *(hsInt32*)buffer = fInt32[2];
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kInt32_4:
            *(hsInt32*)buffer = fInt32[3];
            buffer += sizeof(hsInt32);
            size -= sizeof(hsInt32);
            break;
        case kUint32_1:
            *(hsUint32*)buffer = fUint32[0];
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUint32_2:
            *(hsUint32*)buffer = fUint32[1];
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUint32_3:
            *(hsUint32*)buffer = fUint32[2];
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUint32_4:
            *(hsUint32*)buffer = fUint32[3];
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);
            break;
        case kUuid_1:
            *(plUuid*)buffer = fUuid[0];
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kUuid_2:
            *(plUuid*)buffer = fUuid[1];
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kUuid_3:
            *(plUuid*)buffer = fUuid[2];
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kUuid_4:
            *(plUuid*)buffer = fUuid[3];
            buffer += sizeof(plUuid);
            size -= sizeof(plUuid);
            break;
        case kString64_1:
            {
                NCchar_t* str = StringToNCstr(fString64[0]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kString64_2:
            {
                NCchar_t* str = StringToNCstr(fString64[1]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kString64_3:
            {
                NCchar_t* str = StringToNCstr(fString64[2]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kString64_4:
            {
                NCchar_t* str = StringToNCstr(fString64[3]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kString64_5:
            {
                NCchar_t* str = StringToNCstr(fString64[4]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kString64_6:
            {
                NCchar_t* str = StringToNCstr(fString64[5]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kIString64_1:
            {
                NCchar_t* str = StringToNCstr(fIString64[0]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kIString64_2:
            {
                NCchar_t* str = StringToNCstr(fIString64[1]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kText_1:
            {
                NCchar_t* str = StringToNCstr(fText[0]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kText_2:
            {
                NCchar_t* str = StringToNCstr(fText[1]);
                size_t len = NCstrlen(str) + 1;
                *(hsUint32*)buffer = len * sizeof(NCchar_t);
                buffer += sizeof(hsUint32);
                size -= sizeof(hsUint32);

                memcpy(buffer, str, len * sizeof(NCchar_t));
                buffer += len * sizeof(NCchar_t);
                size -= len * sizeof(NCchar_t);
                delete[] str;
            }
            break;
        case kBlob_1:
            *(hsUint32*)buffer = fBlob[0].getSize();
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);

            memcpy(buffer, fBlob[0].getData(), fBlob[0].getSize());
            buffer += fBlob[0].getSize();
            size -= fBlob[0].getSize();
            break;
        case kBlob_2:
            *(hsUint32*)buffer = fBlob[1].getSize();
            buffer += sizeof(hsUint32);
            size -= sizeof(hsUint32);

            memcpy(buffer, fBlob[1].getData(), fBlob[1].getSize());
            buffer += fBlob[1].getSize();
            size -= fBlob[1].getSize();
            break;
        }
        bit <<= 1;
    }

    if (bit <= fFieldMask || size != 0)
        plDebug::Warning("Node %d is truncated", fNodeIdx);
}

hsInt32 pnVaultNode::getNodeIdx() const
{
    return (fFieldMask & kNodeIdx) != 0 ? fNodeIdx : 0;
}

hsUint32 pnVaultNode::getCreateTime() const
{
    return (fFieldMask & kCreateTime) != 0 ? fCreateTime : 0;
}

hsUint32 pnVaultNode::getModifyTime() const
{
    return (fFieldMask & kModifyTime) != 0 ? fModifyTime : 0;
}

plString pnVaultNode::getCreateAgeName() const
{
    return (fFieldMask & kCreateAgeName) != 0 ? fCreateAgeName : plString();
}

plUuid pnVaultNode::getCreateAgeUuid() const
{
    return (fFieldMask & kCreateAgeUuid) != 0 ? fCreateAgeUuid : plUuid();
}

plUuid pnVaultNode::getCreatorUuid() const
{
    return (fFieldMask & kCreatorUuid) != 0 ? fCreatorUuid : plUuid();
}

hsInt32 pnVaultNode::getCreatorIdx() const
{
    return (fFieldMask & kCreatorIdx) != 0 ? fCreatorIdx : 0;
}

hsInt32 pnVaultNode::getNodeType() const
{
    return (fFieldMask & kNodeType) != 0 ? fNodeType : 0;
}

hsInt32 pnVaultNode::getInt32(size_t which) const
{
    return (fFieldMask & (hsUint64)(kInt32_1 << which)) != 0
           ? fInt32[which] : 0;
}

hsUint32 pnVaultNode::getUint32(size_t which) const
{
    return (fFieldMask & (hsUint64)(kUint32_1 << which)) != 0
           ? fUint32[which] : 0;
}

plUuid pnVaultNode::getUuid(size_t which) const
{
    return (fFieldMask & (hsUint64)(kUuid_1 << which)) != 0
           ? fUuid[which] : plUuid();
}

plString pnVaultNode::getString64(size_t which) const
{
    return (fFieldMask & (hsUint64)(kString64_1 << which)) != 0
           ? fString64[which] : plString();
}

plString pnVaultNode::getIString64(size_t which) const
{
    return (fFieldMask & (hsUint64)(kIString64_1 << which)) != 0
           ? fIString64[which] : plString();
}

plString pnVaultNode::getText(size_t which) const
{
    return (fFieldMask & (hsUint64)(kText_1 << which)) != 0
           ? fText[which] : plString();
}

plVaultBlob pnVaultNode::getBlob(size_t which) const
{
    return (fFieldMask & (hsUint64)(kBlob_1 << which)) != 0
           ? fBlob[which] : plVaultBlob();
}

void pnVaultNode::setNodeIdx(hsInt32 idx)
{
    fNodeIdx = idx;
    fFieldMask |= kNodeIdx;
}

void pnVaultNode::setCreateTime(hsUint32 createTime)
{
    fCreateTime = createTime;
    fFieldMask |= kCreateTime;
}

void pnVaultNode::setModifyTime(hsUint32 modTime)
{
    fModifyTime = modTime;
    fFieldMask |= kModifyTime;
}

void pnVaultNode::setCreateAgeName(const plString& name)
{
    fCreateAgeName = name;
    fFieldMask |= kCreateAgeName;
}

void pnVaultNode::setCreateAgeUuid(const plUuid& uuid)
{
    fCreateAgeUuid = uuid;
    fFieldMask |= kCreateAgeUuid;
}

void pnVaultNode::setCreatorUuid(const plUuid& uuid)
{
    fCreatorUuid = uuid;
    fFieldMask |= kCreatorUuid;
}

void pnVaultNode::setCreatorIdx(hsInt32 idx)
{
    fCreatorIdx = idx;
    fFieldMask |= kCreatorIdx;
}

void pnVaultNode::setNodeType(hsInt32 type)
{
    fNodeType = type;
    fFieldMask |= kNodeType;
}

void pnVaultNode::setInt32(size_t which, hsInt32 value)
{
    fInt32[which] = value;
    fFieldMask |= (hsUint64)(kInt32_1 << which);
}

void pnVaultNode::setUInt32(size_t which, hsUint32 value)
{
    fUint32[which] = value;
    fFieldMask |= (hsUint64)(kUint32_1 << which);
}

void pnVaultNode::setUuid(size_t which, const plUuid& value)
{
    fUuid[which] = value;
    fFieldMask |= (hsUint64)(kUuid_1 << which);
}

void pnVaultNode::setString64(size_t which, const plString& value)
{
    fString64[which] = value;
    fFieldMask |= (hsUint64)(kString64_1 << which);
}

void pnVaultNode::setIString64(size_t which, const plString& value)
{
    fIString64[which] = value;
    fFieldMask |= (hsUint64)(kIString64_1 << which);
}

void pnVaultNode::setText(size_t which, const plString& value)
{
    fText[which] = value;
    fFieldMask |= (hsUint64)(kText_1 << which);
}

void pnVaultNode::setBlob(size_t which, const plVaultBlob& value)
{
    fBlob[which] = value;
    fFieldMask |= (hsUint64)(kBlob_1 << which);
}
