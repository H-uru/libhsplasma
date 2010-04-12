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

#ifndef _PNVAULTNODETYPES_H
#define _PNVAULTNODETYPES_H

#include "pnVaultNode.h"

#define DECLARE_NODE_1(type, nodeType) \
public: \
    type* Convert(pnVaultNode* node) { \
        return (node != NULL && node->getNodeType() == nodeType) \
               ? (type*)node : NULL; \
    }

#define DECLARE_NODE_2(type, nodeType, nodeType2) \
public: \
    type* Convert(pnVaultNode* node) { \
        return (node != NULL && (node->getNodeType() == nodeType || \
                                 node->getNodeType() == nodeType2)) \
               ? (type*)node : NULL; \
    }

#define DECLARE_NODE_3(type, nodeType, nodeType2, nodeType3) \
public: \
    type* Convert(pnVaultNode* node) { \
        return (node != NULL && (node->getNodeType() == nodeType || \
                                 node->getNodeType() == nodeType2 || \
                                 node->getNodeType() == nodeType3)) \
               ? (type*)node : NULL; \
    }

#define ACCESS_INT32(idx, name) \
    hsInt32 get##name() const \
    { return getInt32(idx); } \
    void set##name(hsInt32 value) \
    { setInt32(idx, value); }

#define ACCESS_UINT32(idx, name) \
    hsUint32 get##name() const \
    { return getUint32(idx); } \
    void set##name(hsUint32 value) \
    { setUint32(idx, value); }

#define ACCESS_UUID(idx, name) \
    plUuid get##name() const \
    { return getUuid(idx); } \
    void set##name(const plUuid& value) \
    { setUuid(idx, value); }

#define ACCESS_STRING64(idx, name) \
    plString get##name() const \
    { return getString64(idx); } \
    void set##name(const plString& value) \
    { setString64(idx, value); }

#define ACCESS_ISTRING64(idx, name) \
    plString get##name() const \
    { return getIString64(idx); } \
    void set##name(const plString& value) \
    { setIString64(idx, value); }

#define ACCESS_TEXT(idx, name) \
    plString get##name() const \
    { return getText(idx); } \
    void set##name(const plString& value) \
    { setText(idx, value); }

#define ACCESS_BLOB(idx, name) \
    plVaultBlob get##name() const \
    { return getBlob(idx); } \
    void set##name(const plVaultBlob& value) \
    { setBlob(idx, value); }

DllClass pnVaultAgeNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultAgeNode, plVault::kNodeAge)

    ACCESS_UUID(k_1, AgeInstanceGuid)
    ACCESS_UUID(k_2, ParentAgeInstanceGuid)
    ACCESS_STRING64(k_1, AgeName);
};

DllClass pnVaultAgeInfoNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultAgeInfoNode, plVault::kNodeAgeInfo)

    ACCESS_INT32(k_1, AgeSequenceNumber)
    ACCESS_INT32(k_2, IsPublic)
    ACCESS_INT32(k_3, AgeLanguage)
    ACCESS_UINT32(k_1, AgeId)
    ACCESS_UINT32(k_2, AgeCzarId)
    ACCESS_UINT32(k_3, AgeInfoFlags)
    ACCESS_UUID(k_1, AgeInstanceGuid)
    ACCESS_UUID(k_2, ParentAgeInstanceGuid)
    ACCESS_STRING64(k_2, AgeFilename)
    ACCESS_STRING64(k_3, AgeInstanceName)
    ACCESS_STRING64(k_4, AgeUserDefinedName)
    ACCESS_TEXT(k_1, AgeDescription)
};

DllClass pnVaultAgeLinkNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultAgeLinkNode, plVault::kNodeAgeLink)

    ACCESS_INT32(k_1, Unlocked)
    ACCESS_INT32(k_2, Volatile)
    ACCESS_BLOB(k_1, SpawnPoints)
};

DllClass pnVaultChronicleNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultChronicleNode, plVault::kNodeChronicle)

    ACCESS_INT32(k_1, EntryType)
    ACCESS_STRING64(k_1, EntryName)
    ACCESS_TEXT(k_1, EntryValue)
};

DllClass pnVaultFolderNode : public pnVaultNode {
    DECLARE_NODE_3(pnVaultFolderNode, plVault::kNodeFolder,
                   plVault::kNodeAgeInfoList, plVault::kNodePlayerInfoList)

    ACCESS_INT32(k_1, FolderType)
    ACCESS_STRING64(k_1, FolderName)
};

DllClass pnVaultAgeInfoListNode : public pnVaultFolderNode {
    DECLARE_NODE_1(pnVaultAgeInfoListNode, plVault::kNodeAgeInfoList)
};

DllClass pnVaultPlayerInfoListNode : public pnVaultFolderNode {
    DECLARE_NODE_1(pnVaultPlayerInfoListNode, plVault::kNodePlayerInfoList)
};

DllClass pnVaultImageNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultImageNode, plVault::kNodeImage)

    ACCESS_INT32(k_1, ImageType)
    ACCESS_STRING64(k_1, ImageTitle)
    ACCESS_BLOB(k_1, ImageData)
};

DllClass pnVaultMarkerGameNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultMarkerGameNode, plVault::kNodeMarkerList)

    ACCESS_UUID(k_1, GameGuid)
    ACCESS_STRING64(k_5, OwnerName)
};

DllClass pnVaultMarkerNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultMarkerNode, plVault::kNodeMarker)

    ACCESS_INT32(k_1, GPSTorans)
    ACCESS_INT32(k_2, GPSHSpans)
    ACCESS_INT32(k_3, GPSVSpans)
    ACCESS_UINT32(k_1, MarkerPosX)
    ACCESS_UINT32(k_2, MarkerPosY)
    ACCESS_UINT32(k_3, MarkerPosZ)
    ACCESS_TEXT(k_1, MarkerText)
};

DllClass pnVaultPlayerInfoNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultPlayerInfoNode, plVault::kNodePlayerInfo)

    ACCESS_INT32(k_1, Online)
    ACCESS_INT32(k_2, CCRLevel)
    ACCESS_UINT32(k_1, PlayerId)
    ACCESS_UUID(k_1, AgeInstUuid)
    ACCESS_STRING64(k_1, AgeInstName)
    ACCESS_ISTRING64(k_1, PlayerName)
};

DllClass pnVaultPlayerNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultPlayerNode, plVault::kNodePlayer)

    ACCESS_INT32(k_1, Disabled)
    ACCESS_INT32(k_2, Explorer)
    ACCESS_UINT32(k_1, OnlineTime)
    ACCESS_UUID(k_1, AccountUuid)
    ACCESS_UUID(k_2, InviteUuid)
    ACCESS_STRING64(k_1, AvatarShape)
    ACCESS_ISTRING64(k_1, PlayerName)
};

DllClass pnVaultSDLNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultSDLNode, plVault::kNodeSDL)

    ACCESS_INT32(k_1, SDLIdent)
    ACCESS_STRING64(k_1, SDLName)
    ACCESS_BLOB(k_1, SDLData)
};

DllClass pnVaultSystemNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultSystemNode, plVault::kNodeSystem)

    ACCESS_INT32(k_1, CCRStatus)
};

DllClass pnVaultTextNoteNode : public pnVaultNode {
    DECLARE_NODE_1(pnVaultTextNoteNode, plVault::kNodeTextNote)

    ACCESS_INT32(k_1, NoteType)
    ACCESS_INT32(k_2, NoteSubType)
    ACCESS_STRING64(k_1, NoteTitle)
    ACCESS_TEXT(k_1, NoteText)
};

#endif
