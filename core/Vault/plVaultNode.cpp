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

#include "plVaultNode.h"
#include "plVaultNodeTypes.h"
#include <cstring>

/* plVaultBlob */
plVaultBlob::BlobData::~BlobData()
{
    delete[] fData;
}

void plVaultBlob::BlobData::unRef()
{
    if (--fRefs == 0)
        delete this;
}

plVaultBlob::plVaultBlob(const plVaultBlob& init) : fBlob(init.fBlob)
{
    if (fBlob)
        fBlob->ref();
}

plVaultBlob::~plVaultBlob()
{
    if (fBlob)
        fBlob->unRef();
}

plVaultBlob& plVaultBlob::operator=(const plVaultBlob& init)
{
    if (init.fBlob)
        init.fBlob->ref();
    if (fBlob)
        fBlob->unRef();
    fBlob = init.fBlob;
    return *this;
}

void plVaultBlob::read(hsStream* S)
{
    if (fBlob)
        fBlob->unRef();

    fBlob = new BlobData();
    fBlob->fSize = S->readInt();
    fBlob->fData = new unsigned char[fBlob->fSize];
    S->read(fBlob->fSize, fBlob->fData);
}

void plVaultBlob::write(hsStream* S)
{
    S->writeInt(fBlob->fSize);
    S->write(fBlob->fSize, fBlob->fData);
}

void plVaultBlob::setData(size_t size, const unsigned char* data)
{
    if (fBlob)
        fBlob->unRef();

    fBlob = new BlobData();
    fBlob->fSize = size;
    fBlob->fData = new unsigned char[size];
    memcpy(fBlob->fData, data, size);
}


/* plVaultNode */
plVaultNode::plVaultNode()
    : fNodeID(), fOwner(), fGroup(), fCreator(), fNodeType(),
      fPermissions(plVault::kDefaultPermissions)
{
    fInt32[0] = 0;
    fInt32[1] = 0;
    fInt32[2] = 0;
    fInt32[3] = 0;
    fUInt32[0] = 0;
    fUInt32[1] = 0;
    fUInt32[2] = 0;
    fUInt32[3] = 0;
}

void plVaultNode::copy(const plVaultNode& init)
{
    fFields = init.fFields;
    fNodeID = init.fNodeID;
    fOwner = init.fOwner;
    fGroup = init.fGroup;
    fCreator = init.fCreator;
    fNodeType = init.fNodeType;
    fPermissions = init.fPermissions;
    fAutoTime = init.fAutoTime;
    fModifyTime = init.fModifyTime;
    fCreateAgeTime = init.fCreateAgeTime;
    fCreateAgeGuid = init.fCreateAgeGuid;
    fGuid1 = init.fGuid1;
    fGuid2 = init.fGuid2;
    fCreateAgeName = init.fCreateAgeName;
    fBlob1 = init.fBlob1;
    fBlob2 = init.fBlob2;
    fInt32[0] = init.fInt32[0];
    fInt32[1] = init.fInt32[1];
    fInt32[2] = init.fInt32[2];
    fInt32[3] = init.fInt32[3];
    fUInt32[0] = init.fUInt32[0];
    fUInt32[1] = init.fUInt32[1];
    fUInt32[2] = init.fUInt32[2];
    fUInt32[3] = init.fUInt32[3];
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
}

void plVaultNode::makeField(unsigned int field)
{
    fFields[field] = true;
    switch (field) {
    case kFieldNodeID:
        fNodeID = 0;
        break;
    case kFieldNodeType:
        fNodeType = 0;
        break;
    case kFieldPermissions:
        fPermissions = 0;
        break;
    case kFieldOwner:
        fOwner = 0;
        break;
    case kFieldGroup:
        fGroup = 0;
        break;
    case kFieldAutoTime:
        fAutoTime = plUnifiedTime();
        break;
    case kFieldCreator:
        fCreator = 0;
        break;
    case kFieldModifyTime:
        fModifyTime = plUnifiedTime();
        break;
    case kFieldCreateAgeTime:
        fCreateAgeTime = plUnifiedTime();
        break;
    case kFieldCreateAgeName:
        fCreateAgeName = "";
        break;
    case kFieldCreateAgeGuid:
        fCreateAgeGuid = plServerGuid();
        break;
    case kFieldInt32_1:
        fInt32[0] = 0;
        break;
    case kFieldInt32_2:
        fInt32[1] = 0;
        break;
    case kFieldInt32_3:
        fInt32[2] = 0;
        break;
    case kFieldInt32_4:
        fInt32[3] = 0;
        break;
    case kFieldUInt32_1:
        fUInt32[0] = 0;
        break;
    case kFieldUInt32_2:
        fUInt32[1] = 0;
        break;
    case kFieldUInt32_3:
        fUInt32[2] = 0;
        break;
    case kFieldUInt32_4:
        fUInt32[3] = 0;
        break;
    case kFieldString64_1:
        fString64[0] = "";
        break;
    case kFieldString64_2:
        fString64[1] = "";
        break;
    case kFieldString64_3:
        fString64[2] = "";
        break;
    case kFieldString64_4:
        fString64[3] = "";
        break;
    case kFieldString64_5:
        fString64[4] = "";
        break;
    case kFieldString64_6:
        fString64[5] = "";
        break;
    case kFieldIString64_1:
        fIString64[0] = "";
        break;
    case kFieldIString64_2:
        fIString64[1] = "";
        break;
    case kFieldText_1:
        fText[0] = "";
        break;
    case kFieldText_2:
        fText[1] = "";
        break;
    case kFieldBlob_1:
        fBlob1 = plVaultBlob();
        break;
    case kFieldBlob_2:
        fBlob2 = plVaultBlob();
        break;
    case kFieldGuid_1:
        fGuid1 = plServerGuid();
        break;
    case kFieldGuid_2:
        fGuid2 = plServerGuid();
        break;
    default:
        break;
    }
}

void plVaultNode::read(hsStream* S)
{
    fFields.read(S);

    fNodeID = S->readInt();
    fNodeType = S->readByte();
    fPermissions = S->readInt();
    fOwner = S->readInt();
    fGroup = S->readInt();
    fAutoTime.read(S);

    if (fFields[kFieldCreator])
        fCreator = S->readInt();
    if (fFields[kFieldModifyTime])
        fModifyTime.read(S);
    if (fFields[kFieldCreateAgeTime])
        fCreateAgeTime.read(S);
    if (fFields[kFieldCreateAgeName]) {
        size_t len = S->readShort();
        fCreateAgeName = S->readStr(len);
    }
    if (fFields[kFieldCreateAgeGuid])
        fCreateAgeGuid.read(S);
    if (fFields[kFieldInt32_1])
        fInt32[0] = S->readInt();
    if (fFields[kFieldInt32_2])
        fInt32[1] = S->readInt();
    if (fFields[kFieldInt32_3])
        fInt32[2] = S->readInt();
    if (fFields[kFieldInt32_4])
        fInt32[3] = S->readInt();
    if (fFields[kFieldUInt32_1])
        fUInt32[0] = S->readInt();
    if (fFields[kFieldUInt32_2])
        fUInt32[1] = S->readInt();
    if (fFields[kFieldUInt32_3])
        fUInt32[2] = S->readInt();
    if (fFields[kFieldUInt32_4])
        fUInt32[3] = S->readInt();
    if (fFields[kFieldString64_1]) {
        size_t len = S->readShort();
        fString64[0] = S->readStr(len);
    }
    if (fFields[kFieldString64_2]) {
        size_t len = S->readShort();
        fString64[1] = S->readStr(len);
    }
    if (fFields[kFieldString64_3]) {
        size_t len = S->readShort();
        fString64[2] = S->readStr(len);
    }
    if (fFields[kFieldString64_4]) {
        size_t len = S->readShort();
        fString64[3] = S->readStr(len);
    }
    if (fFields[kFieldString64_5]) {
        size_t len = S->readShort();
        fString64[4] = S->readStr(len);
    }
    if (fFields[kFieldString64_6]) {
        size_t len = S->readShort();
        fString64[5] = S->readStr(len);
    }
    if (fFields[kFieldIString64_1]) {
        size_t len = S->readShort();
        fIString64[0] = S->readStr(len);
    }
    if (fFields[kFieldIString64_2]) {
        size_t len = S->readShort();
        fIString64[1] = S->readStr(len);
    }
    if (fFields[kFieldText_1]) {
        size_t len = S->readShort();
        fText[0] = S->readStr(len);
    }
    if (fFields[kFieldText_2]) {
        size_t len = S->readShort();
        fText[1] = S->readStr(len);
    }
    if (fFields[kFieldBlob_1])
        fBlob1.read(S);
    if (fFields[kFieldBlob_2])
        fBlob2.read(S);
    if (fFields[kFieldGuid_1])
        fGuid1.read(S);
    if (fFields[kFieldGuid_2])
        fGuid2.read(S);
}

void plVaultNode::write(hsStream* S)
{
    fFields.write(S);

    S->writeInt(fNodeID);
    S->writeByte(fNodeType);
    S->writeInt(fPermissions);
    S->writeInt(fOwner);
    S->writeInt(fGroup);
    fAutoTime.write(S);

    if (fFields[kFieldCreator])
        S->writeInt(fCreator);
    if (fFields[kFieldModifyTime])
        fModifyTime.write(S);
    if (fFields[kFieldCreateAgeTime])
        fCreateAgeTime.write(S);
    if (fFields[kFieldCreateAgeName]) {
        S->writeShort(fCreateAgeName.size());
        S->writeStr(fCreateAgeName);
    }
    if (fFields[kFieldCreateAgeGuid])
        fCreateAgeGuid.write(S);
    if (fFields[kFieldInt32_1])
        S->writeInt(fInt32[0]);
    if (fFields[kFieldInt32_2])
        S->writeInt(fInt32[1]);
    if (fFields[kFieldInt32_3])
        S->writeInt(fInt32[2]);
    if (fFields[kFieldInt32_4])
        S->writeInt(fInt32[3]);
    if (fFields[kFieldUInt32_1])
        S->writeInt(fUInt32[0]);
    if (fFields[kFieldUInt32_2])
        S->writeInt(fUInt32[1]);
    if (fFields[kFieldUInt32_3])
        S->writeInt(fUInt32[2]);
    if (fFields[kFieldUInt32_4])
        S->writeInt(fUInt32[3]);
    if (fFields[kFieldString64_1]) {
        S->writeShort(fString64[0].size());
        S->writeStr(fString64[0]);
    }
    if (fFields[kFieldString64_2]) {
        S->writeShort(fString64[1].size());
        S->writeStr(fString64[1]);
    }
    if (fFields[kFieldString64_3]) {
        S->writeShort(fString64[2].size());
        S->writeStr(fString64[2]);
    }
    if (fFields[kFieldString64_4]) {
        S->writeShort(fString64[3].size());
        S->writeStr(fString64[3]);
    }
    if (fFields[kFieldString64_5]) {
        S->writeShort(fString64[4].size());
        S->writeStr(fString64[4]);
    }
    if (fFields[kFieldString64_6]) {
        S->writeShort(fString64[5].size());
        S->writeStr(fString64[5]);
    }
    if (fFields[kFieldIString64_1]) {
        S->writeShort(fIString64[0].size());
        S->writeStr(fIString64[0]);
    }
    if (fFields[kFieldIString64_2]) {
        S->writeShort(fIString64[1].size());
        S->writeStr(fIString64[1]);
    }
    if (fFields[kFieldText_1]) {
        S->writeShort(fText[0].size());
        S->writeStr(fText[0]);
    }
    if (fFields[kFieldText_2]) {
        S->writeShort(fText[1].size());
        S->writeStr(fText[1]);
    }
    if (fFields[kFieldBlob_1])
        fBlob1.write(S);
    if (fFields[kFieldBlob_2])
        fBlob2.write(S);
    if (fFields[kFieldGuid_1])
        fGuid1.write(S);
    if (fFields[kFieldGuid_2])
        fGuid2.write(S);
}

unsigned int plVaultNode::getNodeID() const
{
    return fFields[kFieldNodeID] ? fNodeID : 0;
}

unsigned int plVaultNode::getOwner() const
{
    return fFields[kFieldOwner] ? fOwner : 0;
}

unsigned int plVaultNode::getGroup() const
{
    return fFields[kFieldGroup] ? fGroup : 0;
}

unsigned int plVaultNode::getCreator() const
{
    return fFields[kFieldCreator] ? fCreator : 0;
}

unsigned int plVaultNode::getNodeType() const
{
    return fFields[kFieldNodeType] ? fNodeType : 0;
}

unsigned int plVaultNode::getPermissions() const
{
    return fFields[kFieldPermissions] ? fPermissions : 0;
}

plUnifiedTime plVaultNode::getAutoTime() const
{
    return fFields[kFieldAutoTime] ? fAutoTime : plUnifiedTime();
}

plUnifiedTime plVaultNode::getModifyTime() const
{
    return fFields[kFieldModifyTime] ? fModifyTime : plUnifiedTime();
}

plUnifiedTime plVaultNode::getCreateAgeTime() const
{
    return fFields[kFieldCreateAgeTime] ? fCreateAgeTime : plUnifiedTime();
}

plServerGuid plVaultNode::getCreateAgeGuid() const
{
    return fFields[kFieldCreateAgeGuid] ? fCreateAgeGuid : plServerGuid();
}

plServerGuid plVaultNode::getGuid1() const
{
    return fFields[kFieldGuid_1] ? fGuid1 : plServerGuid();
}

plServerGuid plVaultNode::getGuid2() const
{
    return fFields[kFieldGuid_2] ? fGuid2 : plServerGuid();
}

ST::string plVaultNode::getCreateAgeName() const
{
    return fFields[kFieldCreateAgeName] ? fCreateAgeName : "";
}

int plVaultNode::getInt32_1() const
{
    return fFields[kFieldInt32_1] ? fInt32[0] : 0;
}

int plVaultNode::getInt32_2() const
{
    return fFields[kFieldInt32_2] ? fInt32[1] : 0;
}

int plVaultNode::getInt32_3() const
{
    return fFields[kFieldInt32_3] ? fInt32[2] : 0;
}

int plVaultNode::getInt32_4() const
{
    return fFields[kFieldInt32_4] ? fInt32[3] : 0;
}

unsigned int plVaultNode::getUInt32_1() const
{
    return fFields[kFieldUInt32_1] ? fUInt32[0] : 0;
}

unsigned int plVaultNode::getUInt32_2() const
{
    return fFields[kFieldUInt32_2] ? fUInt32[1] : 0;
}

unsigned int plVaultNode::getUInt32_3() const
{
    return fFields[kFieldUInt32_3] ? fUInt32[2] : 0;
}

unsigned int plVaultNode::getUInt32_4() const
{
    return fFields[kFieldUInt32_4] ? fUInt32[3] : 0;
}

ST::string plVaultNode::getString64_1() const
{
    return fFields[kFieldString64_1] ? fString64[0] : "";
}

ST::string plVaultNode::getString64_2() const
{
    return fFields[kFieldString64_2] ? fString64[1] : "";
}

ST::string plVaultNode::getString64_3() const
{
    return fFields[kFieldString64_3] ? fString64[2] : "";
}

ST::string plVaultNode::getString64_4() const
{
    return fFields[kFieldString64_4] ? fString64[3] : "";
}

ST::string plVaultNode::getString64_5() const
{
    return fFields[kFieldString64_5] ? fString64[4] : "";
}

ST::string plVaultNode::getString64_6() const
{
    return fFields[kFieldString64_6] ? fString64[5] : "";
}

ST::string plVaultNode::getIString64_1() const
{
    return fFields[kFieldIString64_1] ? fIString64[0] : "";
}

ST::string plVaultNode::getIString64_2() const
{
    return fFields[kFieldIString64_2] ? fIString64[1] : "";
}

ST::string plVaultNode::getText_1() const
{
    return fFields[kFieldText_1] ? fText[0] : "";
}

ST::string plVaultNode::getText_2() const
{
    return fFields[kFieldText_2] ? fText[1] : "";
}

plVaultBlob plVaultNode::getBlob_1() const
{
    return fFields[kFieldBlob_1] ? fBlob1 : plVaultBlob();
}

plVaultBlob plVaultNode::getBlob_2() const
{
    return fFields[kFieldBlob_2] ? fBlob2 : plVaultBlob();
}

void plVaultNode::setNodeID(unsigned int id)
{
    fFields[kFieldNodeID] = true;
    fNodeID = id;
}

void plVaultNode::setOwner(unsigned int id)
{
    fFields[kFieldOwner] = true;
    fOwner = id;
}

void plVaultNode::setGroup(unsigned int id)
{
    fFields[kFieldGroup] = true;
    fGroup = id;
}

void plVaultNode::setCreator(unsigned int id)
{
    fFields[kFieldCreator] = true;
    fCreator = id;
}

void plVaultNode::setNodeType(unsigned int type)
{
    fFields[kFieldNodeType] = true;
    fNodeType = type;
}

void plVaultNode::setPermissions(unsigned int permissions)
{
    fFields[kFieldPermissions] = true;
    fPermissions = permissions;
}

void plVaultNode::setAutoTime(const plUnifiedTime& time)
{
    fFields[kFieldAutoTime] = true;
    fAutoTime = time;
}

void plVaultNode::setModifyTime(const plUnifiedTime& time)
{
    fFields[kFieldModifyTime] = true;
    fModifyTime = time;
}

void plVaultNode::setCreateAgeTime(const plUnifiedTime& time)
{
    fFields[kFieldCreateAgeTime] = true;
    fCreateAgeTime = time;
}

void plVaultNode::setCreateAgeGuid(const plServerGuid& guid)
{
    fFields[kFieldCreateAgeGuid] = true;
    fCreateAgeGuid = guid;
}

void plVaultNode::setGuid1(const plServerGuid& guid)
{
    fFields[kFieldGuid_1] = true;
    fGuid1 = guid;
}

void plVaultNode::setGuid2(const plServerGuid& guid)
{
    fFields[kFieldGuid_2] = true;
    fGuid2 = guid;
}

void plVaultNode::setCreateAgeName(const ST::string& name)
{
    fFields[kFieldCreateAgeName] = true;
    fCreateAgeName = name;
}

void plVaultNode::setInt32_1(int value)
{
    fFields[kFieldInt32_1] = true;
    fInt32[0] = value;
}

void plVaultNode::setInt32_2(int value)
{
    fFields[kFieldInt32_2] = true;
    fInt32[1] = value;
}

void plVaultNode::setInt32_3(int value)
{
    fFields[kFieldInt32_3] = true;
    fInt32[2] = value;
}

void plVaultNode::setInt32_4(int value)
{
    fFields[kFieldInt32_4] = true;
    fInt32[3] = value;
}

void plVaultNode::setUInt32_1(unsigned int value)
{
    fFields[kFieldUInt32_1] = true;
    fUInt32[0] = value;
}

void plVaultNode::setUInt32_2(unsigned int value)
{
    fFields[kFieldUInt32_2] = true;
    fUInt32[1] = value;
}

void plVaultNode::setUInt32_3(unsigned int value)
{
    fFields[kFieldUInt32_3] = true;
    fUInt32[2] = value;
}

void plVaultNode::setUInt32_4(unsigned int value)
{
    fFields[kFieldUInt32_4] = true;
    fUInt32[3] = value;
}

void plVaultNode::setString64_1(const ST::string& value)
{
    fFields[kFieldString64_1] = true;
    fString64[0] = value;
}

void plVaultNode::setString64_2(const ST::string& value)
{
    fFields[kFieldString64_2] = true;
    fString64[1] = value;
}

void plVaultNode::setString64_3(const ST::string& value)
{
    fFields[kFieldString64_3] = true;
    fString64[2] = value;
}

void plVaultNode::setString64_4(const ST::string& value)
{
    fFields[kFieldString64_4] = true;
    fString64[3] = value;
}

void plVaultNode::setString64_5(const ST::string& value)
{
    fFields[kFieldString64_5] = true;
    fString64[4] = value;
}

void plVaultNode::setString64_6(const ST::string& value)
{
    fFields[kFieldString64_6] = true;
    fString64[5] = value;
}

void plVaultNode::setIString64_1(const ST::string& value)
{
    fFields[kFieldIString64_1] = true;
    fIString64[0] = value;
}

void plVaultNode::setIString64_2(const ST::string& value)
{
    fFields[kFieldIString64_2] = true;
    fIString64[1] = value;
}

void plVaultNode::setText_1(const ST::string& value)
{
    fFields[kFieldText_1] = true;
    fText[0] = value;
}

void plVaultNode::setText_2(const ST::string& value)
{
    fFields[kFieldText_2] = true;
    fText[1] = value;
}

void plVaultNode::setBlob_1(const plVaultBlob& value)
{
    fFields[kFieldBlob_1] = true;
    fBlob1 = value;
}

void plVaultNode::setBlob_2(const plVaultBlob& value)
{
    fFields[kFieldBlob_2] = true;
    fBlob2 = value;
}

plVaultPlayerNode* plVaultNode::upcastToPlayerNode() const
{
    return (fNodeType == plVault::kNodePlayer)
         ? (plVaultPlayerNode*)this
         : nullptr;
}

plVaultAgeNode* plVaultNode::upcastToAgeNode() const
{
    return (fNodeType == plVault::kNodeAge)
         ? (plVaultAgeNode*)this
         : nullptr;
}

plVaultGameServerNode* plVaultNode::upcastToGameServerNode() const
{
    return (fNodeType == plVault::kNodeGameServer)
         ? (plVaultGameServerNode*)this
         : nullptr;
}

plVaultAdminNode* plVaultNode::upcastToAdminNode() const
{
    return (fNodeType == plVault::kNodeAdmin)
         ? (plVaultAdminNode*)this
         : nullptr;
}

plVaultServerNode* plVaultNode::upcastToServerNode() const
{
    return (fNodeType == plVault::kNodeVaultServer)
         ? (plVaultServerNode*)this
         : nullptr;
}

plVaultFolderNode* plVaultNode::upcastToFolderNode() const
{
    return (fNodeType == plVault::kNodeFolder||
            fNodeType == plVault::kNodePlayerInfoList ||
            fNodeType == plVault::kNodeAgeInfoList ||
            fNodeType == plVault::kNodeMarkerList)
         ? (plVaultFolderNode*)this
         : nullptr;
}

plVaultPlayerInfoNode* plVaultNode::upcastToPlayerInfoNode() const
{
    return (fNodeType == plVault::kNodePlayerInfo)
         ? (plVaultPlayerInfoNode*)this
         : nullptr;
}

plVaultSystemNode* plVaultNode::upcastToSystemNode() const
{
    return (fNodeType == plVault::kNodeSystem)
         ? (plVaultSystemNode*)this
         : nullptr;
}

plVaultImageNode* plVaultNode::upcastToImageNode() const
{
    return (fNodeType == plVault::kNodeImage)
         ? (plVaultImageNode*)this
         : nullptr;
}

plVaultTextNoteNode* plVaultNode::upcastToTextNoteNode() const
{
    return (fNodeType == plVault::kNodeTextNote)
         ? (plVaultTextNoteNode*)this
         : nullptr;
}

plVaultSDLNode* plVaultNode::upcastToSDLNode() const
{
    return (fNodeType == plVault::kNodeSDL)
         ? (plVaultSDLNode*)this
         : nullptr;
}

plVaultAgeLinkNode* plVaultNode::upcastToAgeLinkNode() const
{
    return (fNodeType == plVault::kNodeAgeLink)
         ? (plVaultAgeLinkNode*)this
         : nullptr;
}

plVaultChronicleNode* plVaultNode::upcastToChronicleNode() const
{
    return (fNodeType == plVault::kNodeChronicle)
         ? (plVaultChronicleNode*)this
         : nullptr;
}

plVaultPlayerInfoListNode* plVaultNode::upcastToPlayerInfoListNode() const
{
    return (fNodeType == plVault::kNodePlayerInfoList)
         ? (plVaultPlayerInfoListNode*)this
         : nullptr;
}

plVaultMarkerNode* plVaultNode::upcastToMarkerNode() const
{
    return (fNodeType == plVault::kNodeMarker)
         ? (plVaultMarkerNode*)this
         : nullptr;
}

plVaultAgeInfoNode* plVaultNode::upcastToAgeInfoNode() const
{
    return (fNodeType == plVault::kNodeAgeInfo)
         ? (plVaultAgeInfoNode*)this
         : nullptr;
}

plVaultAgeInfoListNode* plVaultNode::upcastToAgeInfoListNode() const
{
    return (fNodeType == plVault::kNodeAgeInfoList)
         ? (plVaultAgeInfoListNode*)this
         : nullptr;
}

plVaultMarkerListNode* plVaultNode::upcastToMarkerListNode() const
{
    return (fNodeType == plVault::kNodeMarkerList)
         ? (plVaultMarkerListNode*)this
         : nullptr;
}
