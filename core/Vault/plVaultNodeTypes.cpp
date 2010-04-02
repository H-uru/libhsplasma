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


/* plVaultAgeNode */
plVaultAgeNode::plVaultAgeNode() : plVaultNode() {
    fNodeType = plVault::kNodeAge;
}

plVaultAgeNode::plVaultAgeNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAge;
    if (init.getNodeType() == plVault::kNodeAge)
        copy(init);
}


/* plVaultGameServerNode */
plVaultGameServerNode::plVaultGameServerNode() : plVaultNode() {
    fNodeType = plVault::kNodeGameServer;
}

plVaultGameServerNode::plVaultGameServerNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeGameServer;
    if (init.getNodeType() == plVault::kNodeGameServer)
        copy(init);
}


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


/* plVaultPlayerInfoNode */
plVaultPlayerInfoNode::plVaultPlayerInfoNode() : plVaultNode() {
    fNodeType = plVault::kNodePlayerInfo;
}

plVaultPlayerInfoNode::plVaultPlayerInfoNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodePlayerInfo;
    if (init.getNodeType() == plVault::kNodePlayerInfo)
        copy(init);
}


/* plVaultSystemNode */
plVaultSystemNode::plVaultSystemNode() : plVaultNode() {
    fNodeType = plVault::kNodeSystem;
}

plVaultSystemNode::plVaultSystemNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeSystem;
    if (init.getNodeType() == plVault::kNodeSystem)
        copy(init);
}


/* plVaultImageNode */
plVaultImageNode::plVaultImageNode() : plVaultNode() {
    fNodeType = plVault::kNodeImage;
}

plVaultImageNode::plVaultImageNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeImage;
    if (init.getNodeType() == plVault::kNodeImage)
        copy(init);
}


/* plVaultTextNoteNode */
plVaultTextNoteNode::plVaultTextNoteNode() : plVaultNode() {
    fNodeType = plVault::kNodeTextNote;
}

plVaultTextNoteNode::plVaultTextNoteNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeTextNote;
    if (init.getNodeType() == plVault::kNodeTextNote)
        copy(init);
}


/* plVaultSDLNode */
plVaultSDLNode::plVaultSDLNode() : plVaultNode() {
    fNodeType = plVault::kNodeSDL;
}

plVaultSDLNode::plVaultSDLNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeSDL;
    if (init.getNodeType() == plVault::kNodeSDL)
        copy(init);
}


/* plVaultAgeLinkNode */
plVaultAgeLinkNode::plVaultAgeLinkNode() : plVaultNode() {
    fNodeType = plVault::kNodeAgeLink;
}

plVaultAgeLinkNode::plVaultAgeLinkNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAgeLink;
    if (init.getNodeType() == plVault::kNodeAgeLink)
        copy(init);
}


/* plVaultChronicleNode */
plVaultChronicleNode::plVaultChronicleNode() : plVaultNode() {
    fNodeType = plVault::kNodeChronicle;
}

plVaultChronicleNode::plVaultChronicleNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeChronicle;
    if (init.getNodeType() == plVault::kNodeChronicle)
        copy(init);
}


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

float plVaultMarkerNode::getMarkerPosX() const { return uintAsFloat(getUInt32_1()); }
float plVaultMarkerNode::getMarkerPosY() const { return uintAsFloat(getUInt32_2()); }
float plVaultMarkerNode::getMarkerPosZ() const { return uintAsFloat(getUInt32_3()); }

void plVaultMarkerNode::setMarkerPosX(float x) { setUInt32_1(floatAsUint(x)); }
void plVaultMarkerNode::setMarkerPosY(float y) { setUInt32_2(floatAsUint(y)); }
void plVaultMarkerNode::setMarkerPosZ(float z) { setUInt32_3(floatAsUint(z)); }


/* plVaultAgeInfoNode */
plVaultAgeInfoNode::plVaultAgeInfoNode(): plVaultNode() {
    fNodeType = plVault::kNodeAgeInfo;
}

plVaultAgeInfoNode::plVaultAgeInfoNode(const plVaultNode& init) : plVaultNode() {
    fNodeType = plVault::kNodeAgeInfo;
    if (init.getNodeType() == plVault::kNodeAgeInfo)
        copy(init);
}


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
