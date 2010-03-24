#include "pnVaultNode.h"
#include "pnNetMsg.h"
#include "Debug/plDebug.h"
#include <cstring>

/* pnVaultNode */
pnVaultNode::pnVaultNode()
           : fFieldMask(0), fDirtyMask(0), fCachedSize(0), fDirtySize(0),
             fNodeIdx(0), fNodeType(0) {
    fCreateAgeName = NULL;
    memset(fString64, 0, sizeof(fString64));
    memset(fIString64, 0, sizeof(fIString64));
    memset(fText, 0, sizeof(fText));
}

pnVaultNode::pnVaultNode(const pnVaultNode& init) {
    fCreateAgeName = NULL;
    memset(fString64, 0, sizeof(fString64));
    memset(fIString64, 0, sizeof(fIString64));
    memset(fText, 0, sizeof(fText));
    copy(init);
}

pnVaultNode::~pnVaultNode() {
    if (fCreateAgeName != NULL)
        delete[] fCreateAgeName;
    if (fString64[0] != NULL)
        delete[] fString64[0];
    if (fString64[1] != NULL)
        delete[] fString64[1];
    if (fString64[2] != NULL)
        delete[] fString64[2];
    if (fString64[3] != NULL)
        delete[] fString64[3];
    if (fString64[4] != NULL)
        delete[] fString64[4];
    if (fString64[5] != NULL)
        delete[] fString64[5];
    if (fIString64[0] != NULL)
        delete[] fIString64[0];
    if (fIString64[1] != NULL)
        delete[] fIString64[1];
    if (fText[0] != NULL)
        delete[] fText[0];
    if (fText[1] != NULL)
        delete[] fText[1];
}

void pnVaultNode::copy(const pnVaultNode& init) {
    fFieldMask = init.fFieldMask;
    fDirtyMask = init.fDirtyMask;
    fCachedSize = init.fCachedSize;
    fDirtySize = init.fDirtySize;
    fNodeIdx = init.fNodeIdx;
    fCreateTime = init.fCreateTime;
    fModifyTime = init.fModifyTime;
    fCreateAgeName = NCstrdup(init.fCreateAgeName);
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
    fString64[0] = NCstrdup(init.fString64[0]);
    fString64[1] = NCstrdup(init.fString64[1]);
    fString64[2] = NCstrdup(init.fString64[2]);
    fString64[3] = NCstrdup(init.fString64[3]);
    fString64[4] = NCstrdup(init.fString64[4]);
    fString64[5] = NCstrdup(init.fString64[5]);
    fIString64[0] = NCstrdup(init.fIString64[0]);
    fIString64[1] = NCstrdup(init.fIString64[1]);
    fText[0] = NCstrdup(init.fText[0]);
    fText[1] = NCstrdup(init.fText[1]);
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

bool pnVaultNode::isDirty() const {
    return fDirtyMask != 0;
}

bool pnVaultNode::hasField(size_t field) const {
    return (fFieldMask & (1<<field)) != 0;
}

bool pnVaultNode::hasDirty(size_t field) const {
    return (fDirtyMask & (1<<field)) != 0;
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
    setCreateTime((hsUint32)time(NULL));
    setModifyTime(fCreateTime);
}

void pnVaultNode::setModifyNow() {
    setModifyTime((hsUint32)time(NULL));
}

size_t pnVaultNode::bufferSize() const {
    return fDirtySize + sizeof(hsUint64);
}

static hsUint64 readU64(const unsigned char*& buffer, size_t& size) {
    hsUint64 v = *(hsUint64*)buffer;
    buffer += sizeof(hsUint64);
    size -= sizeof(hsUint64);
    return v;
}

static hsUint32 readU32(const unsigned char*& buffer, size_t& size) {
    hsUint32 v = *(hsUint32*)buffer;
    buffer += sizeof(hsUint32);
    size -= sizeof(hsUint32);
    return v;
}

static hsInt32 readS32(const unsigned char*& buffer, size_t& size) {
    hsInt32 v = *(hsInt32*)buffer;
    buffer += sizeof(hsInt32);
    size -= sizeof(hsInt32);
    return v;
}

static plUuid readUuid(const unsigned char*& buffer, size_t& size) {
    plUuid v = *(plUuid*)buffer;
    buffer += sizeof(plUuid);
    size -= sizeof(plUuid);
    return v;
}

static NCchar_t* readString(const unsigned char*& buffer, size_t& size) {
    size_t len = readU32(buffer, size);
    NCchar_t* v = NCstrdup((NCchar_t*)buffer);
    buffer += len;
    size -= len;
    return v;
}

void pnVaultNode::read(const unsigned char* buffer, size_t size) {
    if (size < sizeof(hsUint64)) {
        plDebug::Error("Invalid node data");
        return;
    }
    fCachedSize = size;
    fDirtyMask = 0;
    fDirtySize = 0;
    fFieldMask = readU64(buffer, size);

    for (size_t bit=0; bit<kNumFields; bit++) {
        if ((fFieldMask & (1<<bit)) == 0)
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
            if (fCreateAgeName != NULL)
                delete[] fCreateAgeName;
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
            if (fString64[bit - kString64_1] != NULL)
                delete[] fString64[bit - kString64_1];
            fString64[bit - kString64_1] = readString(buffer, size);
            break;
        case kIString64_1:
        case kIString64_2:
            if (fIString64[bit - kIString64_1] != NULL)
                delete[] fIString64[bit - kIString64_1];
            fIString64[bit - kIString64_1] = readString(buffer, size);
            break;
        case kText_1:
        case kText_2:
            if (fText[bit - kText_1] != NULL)
                delete[] fText[bit - kText_1];
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
        plDebug::Warning("Incomplete read of node %d", fNodeIdx);
}

static void writeU64(hsUint64 v, unsigned char*& buffer, size_t& size) {
    *(hsUint64*)buffer = v;
    buffer += sizeof(hsUint64);
    size -= sizeof(hsUint64);
}

static void writeU32(hsUint32 v, unsigned char*& buffer, size_t& size) {
    *(hsUint32*)buffer = v;
    buffer += sizeof(hsUint32);
    size -= sizeof(hsUint32);
}

static void writeS32(hsInt32 v, unsigned char*& buffer, size_t& size) {
    *(hsInt32*)buffer = v;
    buffer += sizeof(hsInt32);
    size -= sizeof(hsInt32);
}

static void writeUuid(const plUuid& v, unsigned char*& buffer, size_t& size) {
    *(plUuid*)buffer = v;
    buffer += sizeof(plUuid);
    size -= sizeof(plUuid);
}

static void writeString(const NCchar_t* v, unsigned char*& buffer, size_t& size) {
    size_t len = (NCstrlen(v) + 1) * sizeof(NCchar_t);
    writeU32(len, buffer, size);
    memcpy(buffer, v, len);
    buffer += len;
    size -= len;
}

void pnVaultNode::write(unsigned char* buffer, size_t size) const {
    if (size < sizeof(hsUint64)) {
        plDebug::Error("Invalid node buffer");
        return;
    }
    writeU64(fDirtyMask, buffer, size);

    for (size_t bit=0; bit<kNumFields; bit++) {
        if ((fDirtyMask & (1<<bit)) == 0)
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
        plDebug::Warning("Node %d is truncated", fNodeIdx);
}

hsUint32 pnVaultNode::getNodeIdx() const
{
    return (fFieldMask & (1<<kNodeIdx)) != 0 ? fNodeIdx : 0;
}

hsUint32 pnVaultNode::getCreateTime() const
{
    return (fFieldMask & (1<<kCreateTime)) != 0 ? fCreateTime : 0;
}

hsUint32 pnVaultNode::getModifyTime() const
{
    return (fFieldMask & (1<<kModifyTime)) != 0 ? fModifyTime : 0;
}

plString pnVaultNode::getCreateAgeName() const
{
    return (fFieldMask & (1<<kCreateAgeName)) != 0
           ? NCstrToString(fCreateAgeName) : plString();
}

plUuid pnVaultNode::getCreateAgeUuid() const
{
    return (fFieldMask & (1<<kCreateAgeUuid)) != 0 ? fCreateAgeUuid : plUuid();
}

plUuid pnVaultNode::getCreatorUuid() const
{
    return (fFieldMask & (1<<kCreatorUuid)) != 0 ? fCreatorUuid : plUuid();
}

hsUint32 pnVaultNode::getCreatorIdx() const
{
    return (fFieldMask & (1<<kCreatorIdx)) != 0 ? fCreatorIdx : 0;
}

hsUint32 pnVaultNode::getNodeType() const
{
    return (fFieldMask & (1<<kNodeType)) != 0 ? fNodeType : 0;
}

hsInt32 pnVaultNode::getInt32(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kInt32_1) << which)) != 0
           ? fInt32[which] : 0;
}

hsUint32 pnVaultNode::getUint32(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kUint32_1) << which)) != 0
           ? fUint32[which] : 0;
}

plUuid pnVaultNode::getUuid(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kUuid_1) << which)) != 0
           ? fUuid[which] : plUuid();
}

plString pnVaultNode::getString64(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kString64_1) << which)) != 0
           ? NCstrToString(fString64[which]) : plString();
}

plString pnVaultNode::getIString64(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kIString64_1) << which)) != 0
           ? NCstrToString(fIString64[which]) : plString();
}

plString pnVaultNode::getText(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kText_1) << which)) != 0
           ? NCstrToString(fText[which]) : plString();
}

plVaultBlob pnVaultNode::getBlob(size_t which) const
{
    return (fFieldMask & (hsUint64)((1<<kBlob_1) << which)) != 0
           ? fBlob[which] : plVaultBlob();
}

void pnVaultNode::ISetField(size_t which, size_t size)
{
    if (!hasField(which))
        fCachedSize += size;
    if (!hasDirty(which))
        fDirtySize += size;
    fFieldMask |= (1<<which);
    fDirtyMask |= (1<<which);
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


void pnVaultNode::setNodeIdx(hsUint32 idx)
{
    fNodeIdx = idx;
    ISetField(kNodeIdx, sizeof(hsUint32));
}

void pnVaultNode::setCreateTime(hsUint32 createTime)
{
    fCreateTime = createTime;
    ISetField(kCreateTime, sizeof(hsUint32));
}

void pnVaultNode::setModifyTime(hsUint32 modTime)
{
    fModifyTime = modTime;
    ISetField(kModifyTime, sizeof(hsUint32));
}

void pnVaultNode::setCreateAgeName(const plString& name)
{
    if (fCreateAgeName != NULL) {
        size_t oldLen = (NCstrlen(fCreateAgeName) + 1) * sizeof(NCchar_t);
        IClearField(kCreateAgeName, oldLen + sizeof(hsUint32));
        delete[] fCreateAgeName;
    }

    fCreateAgeName = StringToNCstr(name);
    size_t len = (NCstrlen(fCreateAgeName) + 1) * sizeof(NCchar_t);
    ISetField(kCreateAgeName, len + sizeof(hsUint32));
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

void pnVaultNode::setCreatorIdx(hsUint32 idx)
{
    fCreatorIdx = idx;
    ISetField(kCreatorIdx, sizeof(hsUint32));
}

void pnVaultNode::setNodeType(hsUint32 type)
{
    fNodeType = type;
    ISetField(kNodeType, sizeof(hsUint32));
}

void pnVaultNode::setInt32(size_t which, hsInt32 value)
{
    fInt32[which] = value;
    ISetField(kInt32_1 + which, sizeof(hsInt32));
}

void pnVaultNode::setUInt32(size_t which, hsUint32 value)
{
    fUint32[which] = value;
    ISetField(kUint32_1 + which, sizeof(hsUint32));
}

void pnVaultNode::setUuid(size_t which, const plUuid& value)
{
    fUuid[which] = value;
    ISetField(kUuid_1 + which, sizeof(plUuid));
}

void pnVaultNode::setString64(size_t which, const plString& value)
{
    if (fString64[which] != NULL) {
        size_t oldLen = (NCstrlen(fString64[which]) + 1) * sizeof(NCchar_t);
        IClearField(kString64_1 + which, oldLen + sizeof(hsUint32));
        delete[] fString64[which];
    }

    fString64[which] = StringToNCstr(value);
    size_t len = (NCstrlen(fString64[which]) + 1) * sizeof(NCchar_t);
    ISetField(kString64_1 + which, len + sizeof(hsUint32));
}

void pnVaultNode::setIString64(size_t which, const plString& value)
{
    if (fIString64[which] != NULL) {
        size_t oldLen = (NCstrlen(fIString64[which]) + 1) * sizeof(NCchar_t);
        IClearField(kIString64_1 + which, oldLen + sizeof(hsUint32));
        delete[] fIString64[which];
    }

    fIString64[which] = StringToNCstr(value);
    size_t len = (NCstrlen(fIString64[which]) + 1) * sizeof(NCchar_t);
    ISetField(kIString64_1 + which, len + sizeof(hsUint32));
}

void pnVaultNode::setText(size_t which, const plString& value)
{
    if (fText[which] != NULL) {
        size_t oldLen = (NCstrlen(fText[which]) + 1) * sizeof(NCchar_t);
        IClearField(kText_1 + which, oldLen + sizeof(hsUint32));
        delete[] fText[which];
    }

    fText[which] = StringToNCstr(value);
    size_t len = (NCstrlen(fText[which]) + 1) * sizeof(NCchar_t);
    ISetField(kText_1 + which, len + sizeof(hsUint32));
}

void pnVaultNode::setBlob(size_t which, const plVaultBlob& value)
{
    IClearField(kBlob_1 + which, fBlob[which].getSize() + sizeof(hsUint32));
    fBlob[which] = value;
    ISetField(kBlob_1 + which, fBlob[which].getSize() + sizeof(hsUint32));
}


/* pnVaultNodeRef */
void pnVaultNodeRef::read(const unsigned char* buffer)
{
    fParent = *(hsUint32*)(buffer     );
    fChild  = *(hsUint32*)(buffer +  4);
    fOwner  = *(hsUint32*)(buffer +  8);
    fSeen   = *(hsUbyte* )(buffer + 12);
}

void pnVaultNodeRef::write(const unsigned char* buffer)
{
    *(hsUint32*)(buffer     ) = fParent;
    *(hsUint32*)(buffer +  4) = fChild;
    *(hsUint32*)(buffer +  8) = fOwner;
    *(hsUbyte* )(buffer + 12) = fSeen;
}

bool pnVaultNodeRef::operator==(const pnVaultNodeRef& ref)
{
    return (ref.fParent == fParent) && (ref.fChild == fChild);
}
