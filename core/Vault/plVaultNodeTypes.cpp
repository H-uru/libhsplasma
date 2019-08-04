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

#include "plVaultNodeTypes.h"

static float uintAsFloat(unsigned int i)
{
    union
    {
        unsigned int ival;
        float fval;
    } conv;
    conv.ival = i;
    return conv.fval;
}

static unsigned int floatAsUint(float f)
{
    union
    {
        unsigned int ival;
        float fval;
    } conv;
    conv.fval = f;
    return conv.ival;
}


/* plVaultPlayerNode */
plVaultPlayerNode::plVaultPlayerNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodePlayer;
    if (init.getNodeType() == plVault::kNodePlayer)
        copy(init);
}


/* plVaultAgeNode */
plVaultAgeNode::plVaultAgeNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeAge;
    if (init.getNodeType() == plVault::kNodeAge)
        copy(init);
}


/* plVaultGameServerNode */
plVaultGameServerNode::plVaultGameServerNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeGameServer;
    if (init.getNodeType() == plVault::kNodeGameServer)
        copy(init);
}


/* plVaultAdminNode */
plVaultAdminNode::plVaultAdminNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeAdmin;
    if (init.getNodeType() == plVault::kNodeAdmin)
        copy(init);
}


/* plVaultServerNode */
plVaultServerNode::plVaultServerNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeVaultServer;
    if (init.getNodeType() == plVault::kNodeVaultServer)
        copy(init);
}


/* plVaultFolderNode */
plVaultFolderNode::plVaultFolderNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeFolder;
    if (init.getNodeType() == plVault::kNodeFolder ||
        init.getNodeType() == plVault::kNodePlayerInfoList ||
        init.getNodeType() == plVault::kNodeAgeInfoList ||
        init.getNodeType() == plVault::kNodeMarkerList)
        copy(init);
}


/* plVaultPlayerInfoNode */
plVaultPlayerInfoNode::plVaultPlayerInfoNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodePlayerInfo;
    if (init.getNodeType() == plVault::kNodePlayerInfo)
        copy(init);
}


/* plVaultSystemNode */
plVaultSystemNode::plVaultSystemNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeSystem;
    if (init.getNodeType() == plVault::kNodeSystem)
        copy(init);
}


/* plVaultImageNode */
plVaultImageNode::plVaultImageNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeImage;
    if (init.getNodeType() == plVault::kNodeImage)
        copy(init);
}


/* plVaultTextNoteNode */
plVaultTextNoteNode::plVaultTextNoteNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeTextNote;
    if (init.getNodeType() == plVault::kNodeTextNote)
        copy(init);
}


/* plVaultSDLNode */
plVaultSDLNode::plVaultSDLNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeSDL;
    if (init.getNodeType() == plVault::kNodeSDL)
        copy(init);
}


/* plVaultAgeLinkNode */
plVaultAgeLinkNode::plVaultAgeLinkNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeAgeLink;
    if (init.getNodeType() == plVault::kNodeAgeLink)
        copy(init);
}


/* plVaultChronicleNode */
plVaultChronicleNode::plVaultChronicleNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeChronicle;
    if (init.getNodeType() == plVault::kNodeChronicle)
        copy(init);
}


/* plVaultPlayerInfoListNode */
plVaultPlayerInfoListNode::plVaultPlayerInfoListNode(const plVaultNode& init) : plVaultFolderNode()
{
    fNodeType = plVault::kNodePlayerInfoList;
    if (init.getNodeType() == plVault::kNodePlayerInfoList)
        copy(init);
}


/* plVaultMarkerNode */
plVaultMarkerNode::plVaultMarkerNode(const plVaultNode& init) : plVaultNode()
{
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
plVaultAgeInfoNode::plVaultAgeInfoNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeAgeInfo;
    if (init.getNodeType() == plVault::kNodeAgeInfo)
        copy(init);
}


/* plVaultAgeInfoListNode */
plVaultAgeInfoListNode::plVaultAgeInfoListNode(const plVaultNode& init) : plVaultFolderNode()
{
    fNodeType = plVault::kNodeAgeInfoList;
    if (init.getNodeType() == plVault::kNodeAgeInfoList)
        copy(init);
}


/* plVaultMarkerListNode */
plVaultMarkerListNode::plVaultMarkerListNode(const plVaultNode& init) : plVaultNode()
{
    fNodeType = plVault::kNodeMarkerList;
    if (init.getNodeType() == plVault::kNodeMarkerList)
        copy(init);
}
