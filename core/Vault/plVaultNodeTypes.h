#ifndef _PLVAULTNODETYPES_H
#define _PLVAULTNODETYPES_H

#include "plVaultNode.h"

DllClass plVaultPlayerNode : public plVaultNode {
public:
    plVaultPlayerNode();
    plVaultPlayerNode(const plVaultNode& init);

    int getDisabled() const { return getInt32_1(); }
    int getExplorer() const { return getInt32_2(); }
    unsigned int getOnlineTime() const { return getUInt32_1(); }
    plString getAvatarShape() const { return getString64_1(); }
    plString getPlayerName() const { return getIString64_1(); }
    plString getAccountUuid() const { return getIString64_2(); }

    void setDisabled(int disabled) { setInt32_1(disabled); }
    void setExplorer(int explorer) { setInt32_2(explorer); }
    void setOnlineTime(unsigned int onlineTime) { setUInt32_1(onlineTime); }
    void setAvatarShape(const plString& shape) { setString64_1(shape); }
    void setPlayerName(const plString& name) { setIString64_1(name); }
    void setAccountUuid(const plString& uuid) { setIString64_2(uuid); }
};

DllClass plVaultAgeNode : public plVaultNode {
public:
    plVaultAgeNode();
    plVaultAgeNode(const plVaultNode& init);

    plServerGuid getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_1()); }

    void setAgeInstanceGuid(const plServerGuid& guid) { setString64_1(guid.toString()); }
};

DllClass plVaultGameServerNode : public plVaultNode {
public:
    plVaultGameServerNode();
    plVaultGameServerNode(const plVaultNode& init);

    plString getAgeFilename() const { return getString64_1(); }
    plServerGuid getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_2()); }

    void setAgeFilename(const plString& name) { setString64_1(name); }
    void setAgeInstanceGuid(const plServerGuid& guid) { setString64_2(guid.toString()); }
};

DllClass plVaultAdminNode : public plVaultNode {
public:
    plVaultAdminNode();
    plVaultAdminNode(const plVaultNode& init);
};

DllClass plVaultServerNode : public plVaultNode {
public:
    plVaultServerNode();
    plVaultServerNode(const plVaultNode& init);
};

DllClass plVaultFolderNode : public plVaultNode {
public:
    plVaultFolderNode();
    plVaultFolderNode(const plVaultNode& init);

    int getFolderType() const { return getInt32_1(); }
    plString getFolderName() const { return getString64_1(); }

    void setFolderType(int type) { setInt32_1(type); }
    void setFolderName(const plString& name) { setString64_1(name); }
};

DllClass plVaultPlayerInfoNode : public plVaultNode {
public:
    plVaultPlayerInfoNode();
    plVaultPlayerInfoNode(const plVaultNode& init);

    int getOnline() const { return getInt32_1(); }
    unsigned int getPlayerID() const { return getUInt32_1(); }
    plString getAgeInstName() const { return getString64_1(); }
    plServerGuid getAgeInstGuid() const { return plServerGuid::FromString(getString64_2()); }
    plString getPlayerName() const { return getIString64_1(); }

    void setOnline(int online) { setInt32_1(online); }
    void setPlayerID(unsigned int id) { setUInt32_1(id); }
    void setAgeInstName(const plString& name) { setString64_1(name); }
    void setAgeInstGuid(const plServerGuid& guid) { setString64_2(guid.toString()); }
    void setPlayerName(const plString& name) { setIString64_1(name); }
};

DllClass plVaultSystemNode : public plVaultNode {
public:
    plVaultSystemNode();
    plVaultSystemNode(const plVaultNode& init);

    int getCCRStatus() const { return getInt32_1(); }

    void setCCRStatus(int status) { setInt32_1(status); }
};

DllClass plVaultImageNode : public plVaultNode {
public:
    plVaultImageNode();
    plVaultImageNode(const plVaultNode& init);

    int getImageType() const { return getInt32_1(); }
    plString getImageTitle() const { return getString64_1(); }
    plVaultBlob getImageData() const { return getBlob_1(); }

    void setImageType(int type) { setInt32_1(type); }
    void setImageTitle(const plString& title) { setString64_1(title); }
    void setImageData(const plVaultBlob& data) { setBlob_1(data); }
};

DllClass plVaultTextNoteNode : public plVaultNode {
public:
    plVaultTextNoteNode();
    plVaultTextNoteNode(const plVaultNode& init);

    int getNoteType() const { return getInt32_1(); }
    int getNoteSubType() const { return getInt32_2(); }
    plString getNoteTitle() const { return getString64_1(); }
    plVaultBlob getNoteContents() const { return getBlob_1(); }

    void setNoteType(int type) { setInt32_1(type); }
    void setNoteSubType(int type) { setInt32_2(type); }
    void setNoteTitle(const plString& title) { setString64_1(title); }
    void setNoteContents(const plVaultBlob& contents) { setBlob_1(contents); }
};

DllClass plVaultSDLNode : public plVaultNode {
public:
    plVaultSDLNode();
    plVaultSDLNode(const plVaultNode& init);

    int getSDLIdent() const { return getInt32_1(); }
    plVaultBlob getSDLData() const { return getBlob_1(); }

    void setSDLIdent(int ident) { setInt32_1(ident); }
    void setSDLData(const plVaultBlob& data) { setBlob_1(data); }
};

DllClass plVaultAgeLinkNode : public plVaultNode {
public:
    plVaultAgeLinkNode();
    plVaultAgeLinkNode(const plVaultNode& init);

    int getUnlocked() const { return getInt32_1(); }
    int getVolatile() const { return getInt32_2(); }
    plVaultBlob getSpawnPoints() const { return getBlob_1(); }

    void setUnlocked(int unlocked) { setInt32_1(unlocked); }
    void setVolatile(int isVolatile) { setInt32_2(isVolatile); }
    void setSpawnPoints(const plVaultBlob& spawnPoints) { setBlob_1(spawnPoints); }
};

DllClass plVaultChronicleNode : public plVaultNode {
public:
    plVaultChronicleNode();
    plVaultChronicleNode(const plVaultNode& init);

    int getEntryType() const { return getInt32_1(); }
    plString getEntryName() const { return getString64_1(); }
    plString getEntryValue() const { return getText_1(); }

    void setEntryType(int type) { setInt32_1(type); }
    void setEntryName(const plString& name) { setString64_1(name); }
    void setEntryValue(const plString& value) { setText_1(value); }
};

DllClass plVaultPlayerInfoListNode : public plVaultFolderNode {
public:
    plVaultPlayerInfoListNode();
    plVaultPlayerInfoListNode(const plVaultNode& init);
};

DllClass plVaultMarkerNode : public plVaultNode {
public:
    plVaultMarkerNode();
    plVaultMarkerNode(const plVaultNode& init);

    plString getAgeName() const { return getCreateAgeName(); }
    int getTorans() const { return getInt32_1(); }
    int getHSpans() const { return getInt32_2(); }
    int getVSpans() const { return getInt32_3(); }
    float getMarkerPosX() const;
    float getMarkerPosY() const;
    float getMarkerPosZ() const;
    plString getMarkerText() const { return getText_1(); }

    void setAgeName(const plString& name) { setCreateAgeName(name); }
    void setTorans(int torans) { setInt32_1(torans); }
    void setHSpans(int hspans) { setInt32_2(hspans); }
    void setVSpans(int vspans) { setInt32_3(vspans); }
    void setMarkerPosX(float x);
    void setMarkerPosY(float y);
    void setMarkerPosZ(float z);
    void setMarkerText(const plString& text) { setText_1(text); }
};

DllClass plVaultAgeInfoNode : public plVaultNode {
public:
    plVaultAgeInfoNode();
    plVaultAgeInfoNode(const plVaultNode& init);

    int getAgeSequenceNumber() const { return getInt32_1(); }
    int getIsPublic() const { return getInt32_2(); }
    int getAgeLanguage() const { return getInt32_3(); }
    unsigned int getAgeID() const { return getUInt32_1(); }
    unsigned int getAgeCzarID() const { return getUInt32_2(); }
    unsigned int getAgeInfoFlags() const { return getUInt32_3(); }
    plString getAgeFilename() const { return getString64_1(); }
    plString getAgeInstanceName() const { return getString64_2(); }
    plString getAgeUserDefinedName() const { return getString64_3(); }
    plServerGuid getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_4()); }
    plString getAgeDescription() const { return getText_1(); }

    void setAgeSequenceNumber(int seqNum) { setInt32_1(seqNum); }
    void setIsPublic(int isPublic) { setInt32_2(isPublic); }
    void setAgeLanguage(int lang) { setInt32_3(lang); }
    void setAgeID(unsigned int ageID) { setUInt32_1(ageID); }
    void setAgeCzarID(unsigned int id) { setUInt32_2(id); }
    void setAgeInfoFlags(unsigned int flags) { setUInt32_3(flags); }
    void setAgeFilename(const plString& name) { setString64_1(name); }
    void setAgeInstanceName(const plString& name) { setString64_2(name); }
    void setAgeUserDefinedName(const plString& name) { setString64_3(name); }
    void setAgeInstanceGuid(const plServerGuid& guid) { setString64_4(guid.toString()); }
    void setAgeDescription(const plString& desc) { setText_1(desc); }
};

DllClass plVaultAgeInfoListNode : public plVaultFolderNode {
public:
    plVaultAgeInfoListNode();
    plVaultAgeInfoListNode(const plVaultNode& init);
};

DllClass plVaultMarkerListNode : public plVaultNode {
public:
    plVaultMarkerListNode();
    plVaultMarkerListNode(const plVaultNode& init);

    plString getAgeName() const { return getCreateAgeName(); }
    int getGameType() const { return getInt32_1(); }
    int getRoundLength() const { return getInt32_2(); }
    unsigned int getAuthorID() const { return getUInt32_1(); }
    plString getGameTitle() const { return getString64_1(); }
    plString getAuthorName() const { return getString64_2(); }

    void setAgeName(const plString& name) { setCreateAgeName(name); }
    void setGameType(int type) { setInt32_1(type); }
    void setRoundLength(int length) { setInt32_2(length); }
    void setAuthorID(unsigned int id) { setUInt32_1(id); }
    void setGameTitle(const plString& title) { setString64_1(title); }
    void setAuthorName(const plString& name) { setString64_2(name); }
};

#endif
