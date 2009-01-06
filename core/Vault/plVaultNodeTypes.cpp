#include "plVaultNodeTypes.h"

static float uintAsFloat(unsigned int i) {
    return *(float*)(&i);
}

static unsigned int floatAsUint(float f) {
    return *(unsigned int*)(&f);
}


/* plVaultPlayerNode */
plVaultPlayerNode::plVaultPlayerNode() : plVaultNode() {
    fNodeType = plVault::kNodePlayer;
}

plVaultPlayerNode::plVaultPlayerNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodePlayer;
    if (init.getNodeType() == plVault::kNodePlayer)
        copy(init);
}

int plVaultPlayerNode::getDisabled() const { return getInt32_1(); }
int plVaultPlayerNode::getExplorer() const { return getInt32_2(); }
unsigned int plVaultPlayerNode::getOnlineTime() const { return getUInt32_1(); }
plString plVaultPlayerNode::getAvatarShape() const { return getString64_1(); }
plString plVaultPlayerNode::getPlayerName() const { return getIString64_1(); }
plString plVaultPlayerNode::getAccountUuid() const { return getIString64_2(); }

void plVaultPlayerNode::setDisabled(int disabled) { setInt32_1(disabled); }
void plVaultPlayerNode::setExplorer(int explorer) { setInt32_2(explorer); }
void plVaultPlayerNode::setOnlineTime(unsigned int onlineTime) { setUInt32_1(onlineTime); }
void plVaultPlayerNode::setAvatarShape(const plString& shape) { setString64_1(shape); }
void plVaultPlayerNode::setPlayerName(const plString& name) { setIString64_1(name); }
void plVaultPlayerNode::setAccountUuid(const plString& uuid) { setIString64_2(uuid); }


/* plVaultAgeNode */
plVaultAgeNode::plVaultAgeNode() : plVaultNode() {
    fNodeType = plVault::kNodeAge;
}

plVaultAgeNode::plVaultAgeNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAge;
    if (init.getNodeType() == plVault::kNodeAge)
        copy(init);
}

plServerGuid plVaultAgeNode::getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_1()); }

void plVaultAgeNode::setAgeInstanceGuid(const plServerGuid& guid) { setString64_1(guid.toString()); }


/* plVaultGameServerNode */
plVaultGameServerNode::plVaultGameServerNode() : plVaultNode() {
    fNodeType = plVault::kNodeGameServer;
}

plVaultGameServerNode::plVaultGameServerNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeGameServer;
    if (init.getNodeType() == plVault::kNodeGameServer)
        copy(init);
}

plString plVaultGameServerNode::getAgeFilename() const { return getString64_1(); }
plServerGuid plVaultGameServerNode::getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_2()); }

void plVaultGameServerNode::setAgeFilename(const plString& name) { setString64_1(name); }
void plVaultGameServerNode::setAgeInstanceGuid(const plServerGuid& guid) { setString64_2(guid.toString()); }


/* plVaultAdminNode */
plVaultAdminNode::plVaultAdminNode() : plVaultNode() {
    fNodeType = plVault::kNodeAdmin;
}

plVaultAdminNode::plVaultAdminNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAdmin;
    if (init.getNodeType() == plVault::kNodeAdmin)
        copy(init);
}


/* plVaultServerNode */
plVaultServerNode::plVaultServerNode() : plVaultNode() {
    fNodeType = plVault::kNodeVaultServer;
}

plVaultServerNode::plVaultServerNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeVaultServer;
    if (init.getNodeType() == plVault::kNodeVaultServer)
        copy(init);
}


/* plVaultFolderNode */
plVaultFolderNode::plVaultFolderNode() : plVaultNode() {
    fNodeType = plVault::kNodeFolder;
}

plVaultFolderNode::plVaultFolderNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeFolder;
    if (init.getNodeType() == plVault::kNodeFolder ||
        init.getNodeType() == plVault::kNodePlayerInfoList ||
        init.getNodeType() == plVault::kNodeAgeInfoList ||
        init.getNodeType() == plVault::kNodeMarkerList)
        copy(init);
}

int plVaultFolderNode::getFolderType() const { return getInt32_1(); }
plString plVaultFolderNode::getFolderName() const { return getString64_1(); }

void plVaultFolderNode::setFolderType(int type) { setInt32_1(type); }
void plVaultFolderNode::setFolderName(const plString& name) { setString64_1(name); }


/* plVaultPlayerInfoNode */
plVaultPlayerInfoNode::plVaultPlayerInfoNode() : plVaultNode() {
    fNodeType = plVault::kNodePlayerInfo;
}

plVaultPlayerInfoNode::plVaultPlayerInfoNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodePlayerInfo;
    if (init.getNodeType() == plVault::kNodePlayerInfo)
        copy(init);
}

int plVaultPlayerInfoNode::getOnline() const { return getInt32_1(); }
unsigned int plVaultPlayerInfoNode::getPlayerID() const { return getUInt32_1(); }
plString plVaultPlayerInfoNode::getAgeInstName() const { return getString64_1(); }
plServerGuid plVaultPlayerInfoNode::getAgeInstGuid() const { return plServerGuid::FromString(getString64_2()); }
plString plVaultPlayerInfoNode::getPlayerName() const { return getIString64_1(); }

void plVaultPlayerInfoNode::setOnline(int online) { setInt32_1(online); }
void plVaultPlayerInfoNode::setPlayerID(unsigned int id) { setUInt32_1(id); }
void plVaultPlayerInfoNode::setAgeInstName(const plString& name) { setString64_1(name); }
void plVaultPlayerInfoNode::setAgeInstGuid(const plServerGuid& guid) { setString64_2(guid.toString()); }
void plVaultPlayerInfoNode::setPlayerName(const plString& name) { setIString64_1(name); }


/* plVaultSystemNode */
plVaultSystemNode::plVaultSystemNode() : plVaultNode() {
    fNodeType = plVault::kNodeSystem;
}

plVaultSystemNode::plVaultSystemNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeSystem;
    if (init.getNodeType() == plVault::kNodeSystem)
        copy(init);
}

int plVaultSystemNode::getCCRStatus() const { return getInt32_1(); }

void plVaultSystemNode::setCCRStatus(int status) { setInt32_1(status); }


/* plVaultImageNode */
plVaultImageNode::plVaultImageNode() : plVaultNode() {
    fNodeType = plVault::kNodeImage;
}

plVaultImageNode::plVaultImageNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeImage;
    if (init.getNodeType() == plVault::kNodeImage)
        copy(init);
}

int plVaultImageNode::getImageType() const { return getInt32_1(); }
plString plVaultImageNode::getImageTitle() const { return getString64_1(); }
plVaultBlob plVaultImageNode::getImageData() const { return getBlob_1(); }

void plVaultImageNode::setImageType(int type) { setInt32_1(type); }
void plVaultImageNode::setImageTitle(const plString& title) { setString64_1(title); }
void plVaultImageNode::setImageData(const plVaultBlob& data) { setBlob_1(data); }


/* plVaultTextNoteNode */
plVaultTextNoteNode::plVaultTextNoteNode() : plVaultNode() {
    fNodeType = plVault::kNodeTextNote;
}

plVaultTextNoteNode::plVaultTextNoteNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeTextNote;
    if (init.getNodeType() == plVault::kNodeTextNote)
        copy(init);
}

int plVaultTextNoteNode::getNoteType() const { return getInt32_1(); }
int plVaultTextNoteNode::getNoteSubType() const { return getInt32_2(); }
plString plVaultTextNoteNode::getNoteTitle() const { return getString64_1(); }
plVaultBlob plVaultTextNoteNode::getNoteContents() const { return getBlob_1(); }

void plVaultTextNoteNode::setNoteType(int type) { setInt32_1(type); }
void plVaultTextNoteNode::setNoteSubType(int type) { setInt32_2(type); }
void plVaultTextNoteNode::setNoteTitle(const plString& title) { setString64_1(title); }
void plVaultTextNoteNode::setNoteContents(const plVaultBlob& contents) { setBlob_1(contents); }


/* plVaultSDLNode */
plVaultSDLNode::plVaultSDLNode() : plVaultNode() {
    fNodeType = plVault::kNodeSDL;
}

plVaultSDLNode::plVaultSDLNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeSDL;
    if (init.getNodeType() == plVault::kNodeSDL)
        copy(init);
}

int plVaultSDLNode::getSDLIdent() const { return getInt32_1(); }
plVaultBlob plVaultSDLNode::getSDLData() const { return getBlob_1(); }

void plVaultSDLNode::setSDLIdent(int ident) { setInt32_1(ident); }
void plVaultSDLNode::setSDLData(const plVaultBlob& data) { setBlob_1(data); }


/* plVaultAgeLinkNode */
plVaultAgeLinkNode::plVaultAgeLinkNode() : plVaultNode() {
    fNodeType = plVault::kNodeAgeLink;
}

plVaultAgeLinkNode::plVaultAgeLinkNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAgeLink;
    if (init.getNodeType() == plVault::kNodeAgeLink)
        copy(init);
}

int plVaultAgeLinkNode::getUnlocked() const { return getInt32_1(); }
int plVaultAgeLinkNode::getVolatile() const { return getInt32_2(); }
plVaultBlob plVaultAgeLinkNode::getSpawnPoints() const { return getBlob_1(); }

void plVaultAgeLinkNode::setUnlocked(int unlocked) { setInt32_1(unlocked); }
void plVaultAgeLinkNode::setVolatile(int isVolatile) { setInt32_2(isVolatile); }
void plVaultAgeLinkNode::setSpawnPoints(const plVaultBlob& spawnPoints) { setBlob_1(spawnPoints); }


/* plVaultChronicleNode */
plVaultChronicleNode::plVaultChronicleNode() : plVaultNode() {
    fNodeType = plVault::kNodeChronicle;
}

plVaultChronicleNode::plVaultChronicleNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeChronicle;
    if (init.getNodeType() == plVault::kNodeChronicle)
        copy(init);
}

int plVaultChronicleNode::getEntryType() const { return getInt32_1(); }
plString plVaultChronicleNode::getEntryName() const { return getString64_1(); }
plString plVaultChronicleNode::getEntryValue() const { return getText_1(); }

void plVaultChronicleNode::setEntryType(int type) { setInt32_1(type); }
void plVaultChronicleNode::setEntryName(const plString& name) { setString64_1(name); }
void plVaultChronicleNode::setEntryValue(const plString& value) { setText_1(value); }


/* plVaultPlayerInfoListNode */
plVaultPlayerInfoListNode::plVaultPlayerInfoListNode() : plVaultFolderNode() {
    fNodeType = plVault::kNodePlayerInfoList;
}

plVaultPlayerInfoListNode::plVaultPlayerInfoListNode(const plVaultNode& init) : plVaultFolderNode() {
    fNodeType = plVault::kNodePlayerInfoList;
    if (init.getNodeType() == plVault::kNodePlayerInfoList)
        copy(init);
}


/* plVaultMarkerNode */
plVaultMarkerNode::plVaultMarkerNode(): plVaultNode() {
    fNodeType = plVault::kNodeMarker;
}

plVaultMarkerNode::plVaultMarkerNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeMarker;
    if (init.getNodeType() == plVault::kNodeMarker)
        copy(init);
}

plString plVaultMarkerNode::getAgeName() const { return getCreateAgeName(); }
int plVaultMarkerNode::getTorans() const { return getInt32_1(); }
int plVaultMarkerNode::getHSpans() const { return getInt32_2(); }
int plVaultMarkerNode::getVSpans() const { return getInt32_3(); }
float plVaultMarkerNode::getMarkerPosX() const { return uintAsFloat(getUInt32_1()); }
float plVaultMarkerNode::getMarkerPosY() const { return uintAsFloat(getUInt32_2()); }
float plVaultMarkerNode::getMarkerPosZ() const { return uintAsFloat(getUInt32_3()); }
plString plVaultMarkerNode::getMarkerText() const { return getText_1(); }

void plVaultMarkerNode::setAgeName(const plString& name) { setCreateAgeName(name); }
void plVaultMarkerNode::setTorans(int torans) { setInt32_1(torans); }
void plVaultMarkerNode::setHSpans(int hspans) { setInt32_2(hspans); }
void plVaultMarkerNode::setVSpans(int vspans) { setInt32_3(vspans); }
void plVaultMarkerNode::setMarkerPosX(float x) { setUInt32_1(floatAsUint(x)); }
void plVaultMarkerNode::setMarkerPosY(float y) { setUInt32_2(floatAsUint(y)); }
void plVaultMarkerNode::setMarkerPosZ(float z) { setUInt32_3(floatAsUint(z)); }
void plVaultMarkerNode::setMarkerText(const plString& text) { setText_1(text); }


/* plVaultAgeInfoNode */
plVaultAgeInfoNode::plVaultAgeInfoNode(): plVaultNode() {
    fNodeType = plVault::kNodeAgeInfo;
}

plVaultAgeInfoNode::plVaultAgeInfoNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAgeInfo;
    if (init.getNodeType() == plVault::kNodeAgeInfo)
        copy(init);
}

int plVaultAgeInfoNode::getAgeSequenceNumber() const { return getInt32_1(); }
int plVaultAgeInfoNode::getIsPublic() const { return getInt32_2(); }
int plVaultAgeInfoNode::getAgeLanguage() const { return getInt32_3(); }
unsigned int plVaultAgeInfoNode::getAgeID() const { return getUInt32_1(); }
unsigned int plVaultAgeInfoNode::getAgeCzarID() const { return getUInt32_2(); }
unsigned int plVaultAgeInfoNode::getAgeInfoFlags() const { return getUInt32_3(); }
plString plVaultAgeInfoNode::getAgeFilename() const { return getString64_1(); }
plString plVaultAgeInfoNode::getAgeInstanceName() const { return getString64_2(); }
plString plVaultAgeInfoNode::getAgeUserDefinedName() const { return getString64_3(); }
plServerGuid plVaultAgeInfoNode::getAgeInstanceGuid() const { return plServerGuid::FromString(getString64_4()); }
plString plVaultAgeInfoNode::getAgeDescription() const { return getText_1(); }

void plVaultAgeInfoNode::setAgeSequenceNumber(int seqNum) { setInt32_1(seqNum); }
void plVaultAgeInfoNode::setIsPublic(int isPublic) { setInt32_2(isPublic); }
void plVaultAgeInfoNode::setAgeLanguage(int lang) { setInt32_3(lang); }
void plVaultAgeInfoNode::setAgeID(unsigned int ageID) { setUInt32_1(ageID); }
void plVaultAgeInfoNode::setAgeCzarID(unsigned int id) { setUInt32_2(id); }
void plVaultAgeInfoNode::setAgeInfoFlags(unsigned int flags) { setUInt32_3(flags); }
void plVaultAgeInfoNode::setAgeFilename(const plString& name) { setString64_1(name); }
void plVaultAgeInfoNode::setAgeInstanceName(const plString& name) { setString64_2(name); }
void plVaultAgeInfoNode::setAgeUserDefinedName(const plString& name) { setString64_3(name); }
void plVaultAgeInfoNode::setAgeInstanceGuid(const plServerGuid& guid) { setString64_4(guid.toString()); }
void plVaultAgeInfoNode::setAgeDescription(const plString& desc) { setText_1(desc); }


/* plVaultAgeInfoListNode */
plVaultAgeInfoListNode::plVaultAgeInfoListNode() : plVaultFolderNode() {
    fNodeType = plVault::kNodeAgeInfoList;
}

plVaultAgeInfoListNode::plVaultAgeInfoListNode(const plVaultNode& init) : plVaultFolderNode() {
    fNodeType = plVault::kNodeAgeInfoList;
    if (init.getNodeType() == plVault::kNodeAgeInfoList)
        copy(init);
}


/* plVaultMarkerListNode */
plVaultMarkerListNode::plVaultMarkerListNode(): plVaultNode() {
    fNodeType = plVault::kNodeMarkerList;
}

plVaultMarkerListNode::plVaultMarkerListNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeMarkerList;
    if (init.getNodeType() == plVault::kNodeMarkerList)
        copy(init);
}

plString plVaultMarkerListNode::getAgeName() const { return getCreateAgeName(); }
int plVaultMarkerListNode::getGameType() const { return getInt32_1(); }
int plVaultMarkerListNode::getRoundLength() const { return getInt32_2(); }
unsigned int plVaultMarkerListNode::getAuthorID() const { return getUInt32_1(); }
plString plVaultMarkerListNode::getGameTitle() const { return getString64_1(); }
plString plVaultMarkerListNode::getAuthorName() const { return getString64_2(); }

void plVaultMarkerListNode::setAgeName(const plString& name) { setCreateAgeName(name); }
void plVaultMarkerListNode::setGameType(int type) { setInt32_1(type); }
void plVaultMarkerListNode::setRoundLength(int length) { setInt32_2(length); }
void plVaultMarkerListNode::setAuthorID(unsigned int id) { setUInt32_1(id); }
void plVaultMarkerListNode::setGameTitle(const plString& title) { setString64_1(title); }
void plVaultMarkerListNode::setAuthorName(const plString& name) { setString64_2(name); }
