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

#ifndef _PLVAULTNODE_H
#define _PLVAULTNODE_H

#include "plServerGuid.h"
#include "Sys/plUnifiedTime.h"
#include "Util/hsBitVector.h"

namespace plVault
{
    enum NodeTypes
    {
        kNodeInvalid, kNodeVNodeMgrLow, kNodePlayer, kNodeAge, kNodeGameServer,
        kNodeAdmin, kNodeVaultServer, kNodeCCR, kNodeVNodeMgrHigh = 21,
        kNodeFolder, kNodePlayerInfo, kNodeSystem, kNodeImage, kNodeTextNote,
        kNodeSDL, kNodeAgeLink, kNodeChronicle, kNodePlayerInfoList,
        kNodeUNUSED, kNodeMarker, kNodeAgeInfo, kNodeAgeInfoList,
        kNodeMarkerList, kNodeNumTypes,
    };

    enum StandardNodes
    {
        kUserDefinedNode, kInboxFolder, kBuddyListFolder, kIgnoreListFolder,
        kPeopleIKnowAboutFolder, kVaultMgrGlobalDataFolder, kChronicleFolder,
        kAvatarOutfitFolder, kAgeTypeJournalFolder, kSubAgesFolder,
        kDeviceInboxFolder, kHoodMembersFolder, kAllPlayersFolder,
        kAgeMembersFolder, kAgeJournalsFolder, kAgeDevicesFolder,
        kAgeInstanceSDLNode, kAgeGlobalSDLNode, kCanVisitFolder,
        kAgeOwnersFolder, kAllAgeGlobalSDLNodesFolder, kPlayerInfoNode,
        kPublicAgesFolder, kAgesIOwnFolder, kAgesICanVisitFolder,
        kAvatarClosetFolder, kAgeInfoNode, kSystemNode, kPlayerInviteFolder,
        kCCRPlayersFolder, kGlobalInboxFolder, kChildAgesFolder,
        kGameScoresFolder, kLastStandardNode
    };

    enum NoteTypes
    {
        kNoteGeneric, kNoteCCRPetition, kNoteDevice, kNoteInvite, kNoteVisit,
        kNoteUnVisit, kNumNoteTypes
    };

    enum ImageTypes
    {
        kNone, kJPEG, kPNG
    };

    enum NodePermissions
    {
        kOwnerRead = 0x1,
        kOwnerWrite = 0x2,
        kGroupRead = 0x4,
        kGroupWrite = 0x8,
        kOtherRead = 0x10,
        kOtherWrite = 0x20,
        kDefaultPermissions = 0x17
    };
}

class PLASMA_DLL plVaultBlob
{
private:
    struct PLASMA_DLL BlobData
    {
        unsigned int fRefs;
        size_t fSize;
        unsigned char* fData;

        BlobData() : fRefs(1), fSize(), fData() { }
        ~BlobData();
        void ref() { ++fRefs; }
        void unRef();
    };
    BlobData* fBlob;

public:
    plVaultBlob() : fBlob() { }
    plVaultBlob(const plVaultBlob& init);
    ~plVaultBlob();

    plVaultBlob& operator=(const plVaultBlob& init);

    void read(hsStream* S);
    void write(hsStream* S);

    size_t getSize() const { return fBlob ? fBlob->fSize : 0; }
    const unsigned char* getData() const { return fBlob ? fBlob->fData : nullptr; }
    void setData(size_t size, const unsigned char* data);
};

class PLASMA_DLL plVaultNode
{
public:
    enum
    {
        kFieldNodeID, kFieldNodeType, kFieldPermissions, kFieldOwner,
        kFieldGroup, kFieldAutoTime, kFieldCreator, kFieldModifyTime,
        kFieldCreateAgeCoordsBlob, kFieldCreateAgeTime, kFieldCreateAgeName,
        kFieldCreateAgeGuid, kFieldInt32_1, kFieldInt32_2, kFieldInt32_3,
        kFieldInt32_4, kFieldUInt32_1, kFieldUInt32_2, kFieldUInt32_3,
        kFieldUInt32_4, kFieldString64_1, kFieldString64_2, kFieldString64_3,
        kFieldString64_4, kFieldString64_5, kFieldString64_6,
        kFieldIString64_1, kFieldIString64_2, kFieldText_1, kFieldText_2,
        kFieldBlob_1, kFieldBlob_2, kFieldGuid_1, kFieldGuid_2, kFieldLast
    };

protected:
    hsBitVector fFields;
    unsigned int fNodeID, fOwner, fGroup, fCreator;
    unsigned int fNodeType, fPermissions;
    plUnifiedTime fAutoTime, fModifyTime, fCreateAgeTime;
    plServerGuid fCreateAgeGuid, fGuid1, fGuid2;
    ST::string fCreateAgeName;
    int fInt32[4];
    unsigned int fUInt32[4];
    ST::string fString64[6];
    ST::string fIString64[2];
    ST::string fText[2];
    plVaultBlob fBlob1, fBlob2;

    void copy(const plVaultNode& init);

public:
    plVaultNode();

    bool isValid() const { return fNodeID != 0; }
    bool hasField(unsigned int field) const { return fFields[field]; }
    void delField(unsigned int field) { fFields[field] = false; }
    void makeField(unsigned int field);

    void read(hsStream* S);
    void write(hsStream* S);

    unsigned int getNodeID() const;
    unsigned int getOwner() const;
    unsigned int getGroup() const;
    unsigned int getCreator() const;
    unsigned int getNodeType() const;
    unsigned int getPermissions() const;
    plUnifiedTime getAutoTime() const;
    plUnifiedTime getModifyTime() const;
    plUnifiedTime getCreateAgeTime() const;
    plServerGuid getCreateAgeGuid() const;
    plServerGuid getGuid1() const;
    plServerGuid getGuid2() const;
    ST::string getCreateAgeName() const;
    int getInt32_1() const;
    int getInt32_2() const;
    int getInt32_3() const;
    int getInt32_4() const;
    unsigned int getUInt32_1() const;
    unsigned int getUInt32_2() const;
    unsigned int getUInt32_3() const;
    unsigned int getUInt32_4() const;
    ST::string getString64_1() const;
    ST::string getString64_2() const;
    ST::string getString64_3() const;
    ST::string getString64_4() const;
    ST::string getString64_5() const;
    ST::string getString64_6() const;
    ST::string getIString64_1() const;
    ST::string getIString64_2() const;
    ST::string getText_1() const;
    ST::string getText_2() const;
    plVaultBlob getBlob_1() const;
    plVaultBlob getBlob_2() const;

    void setNodeID(unsigned int id);
    void setOwner(unsigned int id);
    void setGroup(unsigned int id);
    void setCreator(unsigned int id);
    void setNodeType(unsigned int type);
    void setPermissions(unsigned int permissions);
    void setAutoTime(const plUnifiedTime& time);
    void setModifyTime(const plUnifiedTime& time);
    void setCreateAgeTime(const plUnifiedTime& time);
    void setCreateAgeGuid(const plServerGuid& guid);
    void setGuid1(const plServerGuid& guid);
    void setGuid2(const plServerGuid& guid);
    void setCreateAgeName(const ST::string& name);
    void setInt32_1(int value);
    void setInt32_2(int value);
    void setInt32_3(int value);
    void setInt32_4(int value);
    void setUInt32_1(unsigned int value);
    void setUInt32_2(unsigned int value);
    void setUInt32_3(unsigned int value);
    void setUInt32_4(unsigned int value);
    void setString64_1(const ST::string& value);
    void setString64_2(const ST::string& value);
    void setString64_3(const ST::string& value);
    void setString64_4(const ST::string& value);
    void setString64_5(const ST::string& value);
    void setString64_6(const ST::string& value);
    void setIString64_1(const ST::string& value);
    void setIString64_2(const ST::string& value);
    void setText_1(const ST::string& value);
    void setText_2(const ST::string& value);
    void setBlob_1(const plVaultBlob& value);
    void setBlob_2(const plVaultBlob& value);

    class plVaultPlayerNode* upcastToPlayerNode() const;
    class plVaultAgeNode* upcastToAgeNode() const;
    class plVaultGameServerNode* upcastToGameServerNode() const;
    class plVaultAdminNode* upcastToAdminNode() const;
    class plVaultServerNode* upcastToServerNode() const;
    class plVaultFolderNode* upcastToFolderNode() const;
    class plVaultPlayerInfoNode* upcastToPlayerInfoNode() const;
    class plVaultSystemNode* upcastToSystemNode() const;
    class plVaultImageNode* upcastToImageNode() const;
    class plVaultTextNoteNode* upcastToTextNoteNode() const;
    class plVaultSDLNode* upcastToSDLNode() const;
    class plVaultAgeLinkNode* upcastToAgeLinkNode() const;
    class plVaultChronicleNode* upcastToChronicleNode() const;
    class plVaultPlayerInfoListNode* upcastToPlayerInfoListNode() const;
    class plVaultMarkerNode* upcastToMarkerNode() const;
    class plVaultAgeInfoNode* upcastToAgeInfoNode() const;
    class plVaultAgeInfoListNode* upcastToAgeInfoListNode() const;
    class plVaultMarkerListNode* upcastToMarkerListNode() const;
};

#endif
