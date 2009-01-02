#ifndef _PLVAULTNODETYPES_H
#define _PLVAULTNODETYPES_H

#include "plVaultNode.h"

DllClass plVaultPlayerNode : public plVaultNode {
public:
    plVaultPlayerNode();
    plVaultPlayerNode(const plVaultNode& init);

    int getDisabled() const;
    int getExplorer() const;
    unsigned int getOnlineTime() const;
    plString getAvatarShape() const;
    plString getPlayerName() const;
    plString getAccountUuid() const;

    void setDisabled(int disabled);
    void setExplorer(int explorer);
    void setOnlineTime(unsigned int onlineTime);
    void setAvatarShape(const plString& shape);
    void setPlayerName(const plString& name);
    void setAccountUuid(const plString& uuid);
};

DllClass plVaultAgeNode : public plVaultNode {
public:
    plVaultAgeNode();
    plVaultAgeNode(const plVaultNode& init);

    plServerGuid getAgeInstanceGuid() const;

    void setAgeInstanceGuid(const plServerGuid& guid);
};

DllClass plVaultGameServerNode : public plVaultNode {
public:
    plVaultGameServerNode();
    plVaultGameServerNode(const plVaultNode& init);

    plString getAgeFilename() const;
    plServerGuid getAgeInstanceGuid() const;

    void setAgeFilename(const plString& name);
    void setAgeInstanceGuid(const plServerGuid& guid);
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

    int getFolderType() const;
    plString getFolderName() const;

    void setFolderType(int type);
    void setFolderName(const plString& name);
};

DllClass plVaultPlayerInfoNode : public plVaultNode {
public:
    plVaultPlayerInfoNode();
    plVaultPlayerInfoNode(const plVaultNode& init);

    int getOnline() const;
    unsigned int getPlayerID() const;
    plString getAgeInstName() const;
    plServerGuid getAgeInstGuid() const;
    plString getPlayerName() const;

    void setOnline(int online);
    void setPlayerID(unsigned int id);
    void setAgeInstName(const plString& name);
    void setAgeInstGuid(const plServerGuid& guid);
    void setPlayerName(const plString& name);
};

DllClass plVaultSystemNode : public plVaultNode {
public:
    plVaultSystemNode();
    plVaultSystemNode(const plVaultNode& init);

    int getCCRStatus() const;

    void setCCRStatus(int status);
};

DllClass plVaultImageNode : public plVaultNode {
public:
    plVaultImageNode();
    plVaultImageNode(const plVaultNode& init);

    int getImageType() const;
    plString getImageTitle() const;
    plVaultBlob getImageData() const;

    void setImageType(int type);
    void setImageTitle(const plString& title);
    void setImageData(const plVaultBlob& data);
};

DllClass plVaultTextNoteNode : public plVaultNode {
public:
    plVaultTextNoteNode();
    plVaultTextNoteNode(const plVaultNode& init);

    int getNoteType() const;
    int getNoteSubType() const;
    plString getNoteTitle() const;
    plVaultBlob getNoteContents() const;

    void setNoteType(int type);
    void setNoteSubType(int type);
    void setNoteTitle(const plString& title);
    void setNoteContents(const plVaultBlob& contents);
};

DllClass plVaultSDLNode : public plVaultNode {
public:
    plVaultSDLNode();
    plVaultSDLNode(const plVaultNode& init);

    plString getSDLName() const;
    int getSDLIdent() const;
    plVaultBlob getSDLData() const;

    void setSDLName(const plString& name);
    void setSDLIdent(int ident);
    void setSDLData(const plVaultBlob& data);
};

DllClass plVaultAgeLinkNode : public plVaultNode {
public:
    plVaultAgeLinkNode();
    plVaultAgeLinkNode(const plVaultNode& init);

    int getUnlocked() const;
    int getVolatile() const;
    plVaultBlob getSpawnPoints() const;

    void setUnlocked(int unlocked);
    void setVolatile(int isVolatile);
    void setSpawnPoints(const plVaultBlob& spawnPoints);
};

DllClass plVaultChronicleNode : public plVaultNode {
public:
    plVaultChronicleNode();
    plVaultChronicleNode(const plVaultNode& init);

    int getEntryType() const;
    plString getEntryName() const;
    plString getEntryValue() const;

    void setEntryType(int type);
    void setEntryName(const plString& name);
    void setEntryValue(const plString& value);
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

    plString getAgeName() const;
    int getTorans() const;
    int getHSpans() const;
    int getVSpans() const;
    float getMarkerPosX() const;
    float getMarkerPosY() const;
    float getMarkerPosZ() const;
    plString getMarkerText() const;

    void setAgeName(const plString& name);
    void setTorans(int torans);
    void setHSpans(int hspans);
    void setVSpans(int vspans);
    void setMarkerPosX(float x);
    void setMarkerPosY(float y);
    void setMarkerPosZ(float z);
    void setMarkerText(const plString& text);
};

DllClass plVaultAgeInfoNode : public plVaultNode {
public:
    plVaultAgeInfoNode();
    plVaultAgeInfoNode(const plVaultNode& init);

    int getAgeSequenceNumber() const;
    int getIsPublic() const;
    int getAgeLanguage() const;
    unsigned int getAgeID() const;
    unsigned int getAgeCzarID() const;
    unsigned int getAgeInfoFlags() const;
    plString getAgeFilename() const;
    plString getAgeInstanceName() const;
    plString getAgeUserDefinedName() const;
    plServerGuid getAgeInstanceGuid() const;
    plString getAgeDescription() const;

    void setAgeSequenceNumber(int seqNum);
    void setIsPublic(int isPublic);
    void setAgeLanguage(int lang);
    void setAgeID(unsigned int ageID);
    void setAgeCzarID(unsigned int id);
    void setAgeInfoFlags(unsigned int flags);
    void setAgeFilename(const plString& name);
    void setAgeInstanceName(const plString& name);
    void setAgeUserDefinedName(const plString& name);
    void setAgeInstanceGuid(const plServerGuid& guid);
    void setAgeDescription(const plString& desc);
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

    plString getAgeName() const;
    int getGameType() const;
    int getRoundLength() const;
    unsigned int getAuthorID() const;
    plString getGameTitle() const;
    plString getAuthorName() const;

    void setAgeName(const plString& name);
    void setGameType(int type);
    void setRoundLength(int length);
    void setAuthorID(unsigned int id);
    void setGameTitle(const plString& title);
    void setAuthorName(const plString& name);
};

#endif
