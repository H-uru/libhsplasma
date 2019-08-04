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

#ifndef _PLVAULTNODETYPES_H
#define _PLVAULTNODETYPES_H

#include "plVaultNode.h"

class PLASMA_DLL plVaultPlayerNode : public plVaultNode
{
public:
    plVaultPlayerNode() { fNodeType = plVault::kNodePlayer; }
    plVaultPlayerNode(const plVaultNode& init);

    int getDisabled() const { return getInt32_1(); }
    int getExplorer() const { return getInt32_2(); }
    unsigned int getOnlineTime() const { return getUInt32_1(); }
    ST::string getAvatarShape() const { return getString64_1(); }
    ST::string getPlayerName() const { return getIString64_1(); }
    ST::string getAccountUuid() const { return getIString64_2(); }

    void setDisabled(int disabled) { setInt32_1(disabled); }
    void setExplorer(int explorer) { setInt32_2(explorer); }
    void setOnlineTime(unsigned int onlineTime) { setUInt32_1(onlineTime); }
    void setAvatarShape(const ST::string& shape) { setString64_1(shape); }
    void setPlayerName(const ST::string& name) { setIString64_1(name); }
    void setAccountUuid(const ST::string& uuid) { setIString64_2(uuid); }
};

class PLASMA_DLL plVaultAgeNode : public plVaultNode
{
public:
    plVaultAgeNode() { fNodeType = plVault::kNodeAge; }
    plVaultAgeNode(const plVaultNode& init);

    plServerGuid getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_1()); }

    void setAgeInstanceGuid(const plServerGuid& guid) { setString64_1(guid.toString()); }
};

class PLASMA_DLL plVaultGameServerNode : public plVaultNode
{
public:
    plVaultGameServerNode() { fNodeType = plVault::kNodeGameServer; }
    plVaultGameServerNode(const plVaultNode& init);

    ST::string getAgeFilename() const { return getString64_1(); }
    plServerGuid getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_2()); }

    void setAgeFilename(const ST::string& name) { setString64_1(name); }
    void setAgeInstanceGuid(const plServerGuid& guid) { setString64_2(guid.toString()); }
};

class PLASMA_DLL plVaultAdminNode : public plVaultNode
{
public:
    plVaultAdminNode() { fNodeType = plVault::kNodeAdmin; }
    plVaultAdminNode(const plVaultNode& init);
};

class PLASMA_DLL plVaultServerNode : public plVaultNode
{
public:
    plVaultServerNode() { fNodeType = plVault::kNodeVaultServer; }
    plVaultServerNode(const plVaultNode& init);
};

class PLASMA_DLL plVaultFolderNode : public plVaultNode
{
public:
    plVaultFolderNode() { fNodeType = plVault::kNodeFolder; }
    plVaultFolderNode(const plVaultNode& init);

    int getFolderType() const { return getInt32_1(); }
    ST::string getFolderName() const { return getString64_1(); }

    void setFolderType(int type) { setInt32_1(type); }
    void setFolderName(const ST::string& name) { setString64_1(name); }
};

class PLASMA_DLL plVaultPlayerInfoNode : public plVaultNode
{
public:
    plVaultPlayerInfoNode() { fNodeType = plVault::kNodePlayerInfo; }
    plVaultPlayerInfoNode(const plVaultNode& init);

    int getOnline() const { return getInt32_1(); }
    unsigned int getPlayerID() const { return getUInt32_1(); }
    ST::string getAgeInstName() const { return getString64_1(); }
    plServerGuid getAgeInstGuid() const { return plServerGuid::FromString(getString64_2()); }
    ST::string getPlayerName() const { return getIString64_1(); }

    void setOnline(int online) { setInt32_1(online); }
    void setPlayerID(unsigned int id) { setUInt32_1(id); }
    void setAgeInstName(const ST::string& name) { setString64_1(name); }
    void setAgeInstGuid(const plServerGuid& guid) { setString64_2(guid.toString()); }
    void setPlayerName(const ST::string& name) { setIString64_1(name); }
};

class PLASMA_DLL plVaultSystemNode : public plVaultNode
{
public:
    plVaultSystemNode() { fNodeType = plVault::kNodeSystem; }
    plVaultSystemNode(const plVaultNode& init);

    int getCCRStatus() const { return getInt32_1(); }

    void setCCRStatus(int status) { setInt32_1(status); }
};

class PLASMA_DLL plVaultImageNode : public plVaultNode
{
public:
    plVaultImageNode() { fNodeType = plVault::kNodeImage; }
    plVaultImageNode(const plVaultNode& init);

    int getImageType() const { return getInt32_1(); }
    ST::string getImageTitle() const { return getString64_1(); }
    plVaultBlob getImageData() const { return getBlob_1(); }

    void setImageType(int type) { setInt32_1(type); }
    void setImageTitle(const ST::string& title) { setString64_1(title); }
    void setImageData(const plVaultBlob& data) { setBlob_1(data); }
};

class PLASMA_DLL plVaultTextNoteNode : public plVaultNode
{
public:
    plVaultTextNoteNode() { fNodeType = plVault::kNodeTextNote; }
    plVaultTextNoteNode(const plVaultNode& init);

    int getNoteType() const { return getInt32_1(); }
    int getNoteSubType() const { return getInt32_2(); }
    ST::string getNoteTitle() const { return getString64_1(); }
    plVaultBlob getNoteContents() const { return getBlob_1(); }

    void setNoteType(int type) { setInt32_1(type); }
    void setNoteSubType(int type) { setInt32_2(type); }
    void setNoteTitle(const ST::string& title) { setString64_1(title); }
    void setNoteContents(const plVaultBlob& contents) { setBlob_1(contents); }
};

class PLASMA_DLL plVaultSDLNode : public plVaultNode
{
public:
    plVaultSDLNode() { fNodeType = plVault::kNodeSDL; }
    plVaultSDLNode(const plVaultNode& init);

    int getSDLIdent() const { return getInt32_1(); }
    plVaultBlob getSDLData() const { return getBlob_1(); }

    void setSDLIdent(int ident) { setInt32_1(ident); }
    void setSDLData(const plVaultBlob& data) { setBlob_1(data); }
};

class PLASMA_DLL plVaultAgeLinkNode : public plVaultNode
{
public:
    plVaultAgeLinkNode() { fNodeType = plVault::kNodeAgeLink; }
    plVaultAgeLinkNode(const plVaultNode& init);

    int getUnlocked() const { return getInt32_1(); }
    int getVolatile() const { return getInt32_2(); }
    plVaultBlob getSpawnPoints() const { return getBlob_1(); }

    void setUnlocked(int unlocked) { setInt32_1(unlocked); }
    void setVolatile(int isVolatile) { setInt32_2(isVolatile); }
    void setSpawnPoints(const plVaultBlob& spawnPoints) { setBlob_1(spawnPoints); }
};

class PLASMA_DLL plVaultChronicleNode : public plVaultNode
{
public:
    plVaultChronicleNode() { fNodeType = plVault::kNodeChronicle; }
    plVaultChronicleNode(const plVaultNode& init);

    int getEntryType() const { return getInt32_1(); }
    ST::string getEntryName() const { return getString64_1(); }
    ST::string getEntryValue() const { return getText_1(); }

    void setEntryType(int type) { setInt32_1(type); }
    void setEntryName(const ST::string& name) { setString64_1(name); }
    void setEntryValue(const ST::string& value) { setText_1(value); }
};

class PLASMA_DLL plVaultPlayerInfoListNode : public plVaultFolderNode
{
public:
    plVaultPlayerInfoListNode() { fNodeType = plVault::kNodePlayerInfoList; }
    plVaultPlayerInfoListNode(const plVaultNode& init);
};

class PLASMA_DLL plVaultMarkerNode : public plVaultNode
{
public:
    plVaultMarkerNode() { fNodeType = plVault::kNodeMarker; }
    plVaultMarkerNode(const plVaultNode& init);

    ST::string getAgeName() const { return getCreateAgeName(); }
    int getTorans() const { return getInt32_1(); }
    int getHSpans() const { return getInt32_2(); }
    int getVSpans() const { return getInt32_3(); }
    float getMarkerPosX() const;
    float getMarkerPosY() const;
    float getMarkerPosZ() const;
    ST::string getMarkerText() const { return getText_1(); }

    void setAgeName(const ST::string& name) { setCreateAgeName(name); }
    void setTorans(int torans) { setInt32_1(torans); }
    void setHSpans(int hspans) { setInt32_2(hspans); }
    void setVSpans(int vspans) { setInt32_3(vspans); }
    void setMarkerPosX(float x);
    void setMarkerPosY(float y);
    void setMarkerPosZ(float z);
    void setMarkerText(const ST::string& text) { setText_1(text); }
};

class PLASMA_DLL plVaultAgeInfoNode : public plVaultNode
{
public:
    plVaultAgeInfoNode() { fNodeType = plVault::kNodeAgeInfo; }
    plVaultAgeInfoNode(const plVaultNode& init);

    int getAgeSequenceNumber() const { return getInt32_1(); }
    int getIsPublic() const { return getInt32_2(); }
    int getAgeLanguage() const { return getInt32_3(); }
    unsigned int getAgeID() const { return getUInt32_1(); }
    unsigned int getAgeCzarID() const { return getUInt32_2(); }
    unsigned int getAgeInfoFlags() const { return getUInt32_3(); }
    ST::string getAgeFilename() const { return getString64_1(); }
    ST::string getAgeInstanceName() const { return getString64_2(); }
    ST::string getAgeUserDefinedName() const { return getString64_3(); }
    plServerGuid getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_4()); }
    ST::string getAgeDescription() const { return getText_1(); }

    void setAgeSequenceNumber(int seqNum) { setInt32_1(seqNum); }
    void setIsPublic(int isPublic) { setInt32_2(isPublic); }
    void setAgeLanguage(int lang) { setInt32_3(lang); }
    void setAgeID(unsigned int ageID) { setUInt32_1(ageID); }
    void setAgeCzarID(unsigned int id) { setUInt32_2(id); }
    void setAgeInfoFlags(unsigned int flags) { setUInt32_3(flags); }
    void setAgeFilename(const ST::string& name) { setString64_1(name); }
    void setAgeInstanceName(const ST::string& name) { setString64_2(name); }
    void setAgeUserDefinedName(const ST::string& name) { setString64_3(name); }
    void setAgeInstanceGuid(const plServerGuid& guid) { setString64_4(guid.toString()); }
    void setAgeDescription(const ST::string& desc) { setText_1(desc); }
};

class PLASMA_DLL plVaultAgeInfoListNode : public plVaultFolderNode
{
public:
    plVaultAgeInfoListNode() { fNodeType = plVault::kNodeAgeInfoList; }
    plVaultAgeInfoListNode(const plVaultNode& init);
};

class PLASMA_DLL plVaultMarkerListNode : public plVaultNode
{
public:
    plVaultMarkerListNode() { fNodeType = plVault::kNodeMarkerList; }
    plVaultMarkerListNode(const plVaultNode& init);

    ST::string getAgeName() const { return getCreateAgeName(); }
    int getGameType() const { return getInt32_1(); }
    int getRoundLength() const { return getInt32_2(); }
    unsigned int getAuthorID() const { return getUInt32_1(); }
    ST::string getGameTitle() const { return getString64_1(); }
    ST::string getAuthorName() const { return getString64_2(); }

    void setAgeName(const ST::string& name) { setCreateAgeName(name); }
    void setGameType(int type) { setInt32_1(type); }
    void setRoundLength(int length) { setInt32_2(length); }
    void setAuthorID(unsigned int id) { setUInt32_1(id); }
    void setGameTitle(const ST::string& title) { setString64_1(title); }
    void setAuthorName(const ST::string& name) { setString64_2(name); }
};

#endif
